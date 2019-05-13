#include <nds/graph/node.hpp>
#include <iostream>

namespace nds
{
    template<class... Ts, class... Us, class... Vs>
    template<class T>
    node<T>* graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::add(T v)
    {
        node<T> target_node = node<T>{ std::move(v) };

        constexpr int index = cx::index_of<std::vector<node_ptr<T>>, node_container_type>::value;
        std::get<index>(data_).emplace_back(std::make_unique<node<T>>(std::move(target_node)));

        node<T>* last_node = std::get<index>(data_).back().get();

        return last_node;
    }

    template<class... Ts, class... Us, class... Vs>
    template<class... Node_types>
    auto& graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::nodes()
    {
        auto loop_input_type = [this](auto&& nt)
        {
            using input_node_type = node<std::decay_t<decltype(nt)>>;

            auto loop_graph_type = [](auto&& vector)
            {
                using graph_node_type = typename std::decay_t<decltype(vector)>::value_type::element_type; // node<T>
                if constexpr (std::is_same_v<input_node_type, graph_node_type>)
                {
                    for (auto&& node : vector)
                    {
                    } // std::cout << "\n_node " << node->get();
                }
            };

            std::apply([&](auto&&... vectors) { (loop_graph_type(vectors), ...); }, data_);
        };

        (loop_input_type(Node_types{}), ...);

        return data_;
    }

    template<class... Ts, class... Us, class... Vs>
    template<class F>
    auto graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::edges(F&& f)
    {
        return edges<edges_type>(std::forward<F>(f));
    }

    template<class... Ts, class... Us, class... Vs>
    template<class Edges, class F>
    auto graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::edges(F&& f)
    {
        nds::cx::for_each<Edges>([f, this](auto&& et) {
            using input_raw_edge_type = typename std::decay_t<decltype(et)>::type; // nds::edge<U, V>
            using input_edge_type =
            nds::edge<nds::node<typename input_raw_edge_type::source_type>, nds::node<typename input_raw_edge_type::target_type>>;

            auto loop_edge_type = [f](auto&& vector) {
                using graph_edge_type = typename std::decay_t<decltype(vector)>::value_type; // edge<node<U>, node<V>>
                if constexpr (std::is_same_v<input_edge_type, graph_edge_type>)
                {
                    for (auto&& edge : vector)
                        f(edge);
                }
            };

            std::apply([&](auto&&... vectors) { (loop_edge_type(vectors), ...); }, edges_);
        });
    }

    template<class... Ts, class... Us, class... Vs>
    template<class Source, class Target>
    void graph<graph_types<Ts...>, nds::graph_edges<edge<Us, Vs>...>>
    ::connect(Source* s, Target* t)
    {
        // check edges
        constexpr int index = cx::index_of<std::vector<edge<Source, Target>>, edge_container_type>::value;
        // static_assert(index >= 0, "connection between U and V not allowed");

        std::get<index>(edges_).emplace_back(edge<Source, Target>{ s, t });
    }

    template<class... Ts, class... Us, class... Vs>
    template<class T>
    void graph<graph_types<Ts...>, nds::graph_edges<edge<Us, Vs>...>>
    ::connect(int s, int t)
    {
        // check edges
        constexpr int index = cx::index_of<std::vector<edge<node<T>, node<T>>>, edge_container_type>::value;
        // static_assert(index >= 0, "connection between U and V not allowed");
        node<T>* source = std::get<0>(data_)[s].get();
        node<T>* target = std::get<0>(data_)[t].get();
        std::get<index>(edges_).emplace_back(edge<node<T>, node<T>>{ source, target });
    }

    template<class... Ts, class... Us, class... Vs>
    template<class Source>
    void graph<graph_types<Ts...>, nds::graph_edges<edge<Us, Vs>...>>
    ::targets(Source* source)
    {
        auto loop_graph_edge = [&](auto&& vector)
        {
            using graph_edge_type = typename std::decay_t<decltype(vector)>::value_type::source_type; // node<T>
            if constexpr (std::is_same_v<graph_edge_type, Source>)
            {
                for (auto node : vector)
                    if (source->get() == node.source->get())
                        std::cout << "\n_edge " << node.source->get() << " - " << node.target->get();
            }
        };

        std::apply([&](auto&&... vectors) { (loop_graph_edge(vectors), ...); }, edges_);
    }
} // nds