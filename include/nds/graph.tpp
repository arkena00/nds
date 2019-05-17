#include <nds/graph/node.hpp>
#include <iostream>

namespace nds::internal
{
    template<class... Ts, class... Us, class... Vs>
    template<class T>
    graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>::node_type<T>*
    graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::add(T v)
    {

        node_type<T> target_node = node_type<T>{ std::move(v) };

        constexpr int index = cx::index_of<std::vector<node_ptr<T>>, node_container_type>::value;
        std::get<index>(nodes_).emplace_back(std::make_unique<node<T>>(std::move(target_node)));

        node_type<T>* last_node = std::get<index>(nodes_).back().get();

        return last_node;
    }

    template<class... Ts, class... Us, class... Vs>
    template<class T>
    node_type<T>* graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::add(T v, node_type<T>* source)
    {
        node_type<T>* added_node = add(std::move(v));
        connect(source, added_node);
        return added_node;
    }

    template<class... Ts, class... Us, class... Vs>
    template<class F>
    void graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::nodes(F&& f) const
    {
        nodes<nodes_type>(std::forward<F>(f));
    }

    template<class... Ts, class... Us, class... Vs>
    template<class Nodes, class F>
    void graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::nodes(F&& f) const
    {
        nds::cx::for_each<Nodes>([&f, this](auto&& nt)
        {
            using input_node_type = node_type<typename std::decay_t<decltype(nt)>::type>;

            auto loop_graph_type = [&f](auto&& vector)
            {
                using graph_node_type = typename std::decay_t<decltype(vector)>::value_type::element_type; // node_type<T>
                if constexpr (std::is_same_v<input_node_type, graph_node_type>)
                {
                    for (auto&& node : vector) f(node);
                }
            };

            std::apply([&](auto&&... vectors) { (loop_graph_type(vectors), ...); }, nodes_);
        });
    }

    template<class... Ts, class... Us, class... Vs>
    template<class F>
    void graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::edges(F&& f) const
    {
        edges<edges_type>(std::forward<F>(f));
    }

    template<class... Ts, class... Us, class... Vs>
    template<class Edges, class F>
    void graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::edges(F&& f) const
    {
        nds::cx::for_each<Edges>([&f, this](auto&& et)
        {
            using input_raw_edge_type = typename std::decay_t<decltype(et)>::type; // nds::edge<U, V>
            using input_edge_type = nds::edge<nds::node_type<typename input_raw_edge_type::source_type>, nds::node_type<typename input_raw_edge_type::target_type>>;

            auto loop_edge_type = [&f](auto&& vector) {
                using graph_edge_type = typename std::decay_t<decltype(vector)>::value_type; // edge<node_type<U>, node_type<V>>
                if constexpr (std::is_same_v<input_edge_type, graph_edge_type>)
                {
                    for (auto&& edge : vector) f(edge);
                }
            };

            std::apply([&](auto&&... vectors) { (loop_edge_type(vectors), ...); }, edges_);
        });
    }

    template<class... Ts, class... Us, class... Vs>
    template<class Source, class Target>
    void graph<graph_types<Ts...>, nds::graph_edges<edge<Us, Vs>...>>
    ::connect(Source* source, Target* target)
    {
        // check edges
        constexpr int index = cx::index_of<std::vector<edge<Source, Target>>, edge_container_type>::value;
        // static_assert(index >= 0, "connection between U and V not allowed");

        source->targets_count++;

        std::get<index>(edges_).emplace_back(edge<Source, Target>{ source, target });
    }

    template<class... Ts, class... Us, class... Vs>
    template<class T>
    void graph<graph_types<Ts...>, nds::graph_edges<edge<Us, Vs>...>>
    ::connect(int s, int t)
    {
        // check edges
        constexpr int index = cx::index_of<std::vector<edge<node_type<T>, node_type<T>>>, edge_container_type>::value;
        // static_assert(index >= 0, "connection between U and V not allowed");
        node_type<T>* source = std::get<0>(nodes_)[s].get();
        node_type<T>* target = std::get<0>(nodes_)[t].get();
        std::get<index>(edges_).emplace_back(edge<node_type<T>, node_type<T>>{ source, target });
    }

    template<class... Ts, class... Us, class... Vs>
    template<class Source, class F>
    void graph<graph_types<Ts...>, nds::graph_edges<edge<Us, Vs>...>>
    ::targets(Source* source, F&& f)
    {
        auto loop_graph_edge = [&](auto&& vector)
        {
            using graph_edge_type = typename std::decay_t<decltype(vector)>::value_type::source_type; // node_type<T>
            if constexpr (std::is_same_v<graph_edge_type, Source>)
            {
                for (auto&& node : vector)
                {
                    if (source->get() == node.source->get()) f(node.target);
                }
            }
        };

        std::apply([&](auto&&... vectors) { (loop_graph_edge(vectors), ...); }, edges_);
    }

    template<class... Ts, class... Us, class... Vs>
    std::size_t graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::count_nodes()
    {
        return std::apply([&](auto&&... vectors) { return (vectors.size() + ...); }, nodes_);
    }
    template<class... Ts, class... Us, class... Vs>
    std::size_t graph<graph_types<Ts...>, graph_edges<edge<Us, Vs>...>>
    ::count_edges()
    {
        return std::apply([&](auto&&... vectors) { return (vectors.size() + ...); }, edges_);
    }
} // nds::internal