#ifndef INCLUDE_NDS_GRAPH2_HPP_NDS
#define INCLUDE_NDS_GRAPH2_HPP_NDS

#include <nds/graph/edge.hpp>

#include <nds/cx/for_each.hpp>
#include <nds/cx/index_of.hpp>
#include <nds/cx/type_str.hpp>

#include <memory>
#include <tuple>
#include <vector>

namespace nds
{
    template<class T>
    struct node
    {
        virtual T& get() = 0;
    };

    template<class T, class Base = T>
    struct basic_node : node<Base>
    {
        template<class... Us>
        basic_node(Us&&... us) : value_{ std::forward<Us>(us)... } {}

        T& get() { return value_; }
        T value_;
    };

    template<class... Edges>
    struct graph_edges{};

    template<class... Types>
    struct graph_types{};

    template<class... Params>
    struct graph_params{};



    namespace internal
    {
        template<class...>
        struct graph;

        template<class...>
        struct graph_trait;

        // graph<T>
        template<class T>
        struct graph_trait<T>
        {
            using type = graph<nds::graph_types<T>, nds::graph_edges<nds::edge<T, T>>>;
        };

        // graph<Graph_types, Graph_edges>
        template<class... Ts, class... Us, class... Vs>
        struct graph_trait<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>>
        {
            using type = graph<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>>;
        };


        template<class... Ts, class... Us, class... Vs>
        struct graph<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>> //: nds::concept<nds::concepts::graph>
        {
        public:
            template<class T>
            using node_type = node<T>;

            template<class T>
            using node_ptr = std::unique_ptr<node_type<T>>;

            using edges_type = nds::graph_edges<edge<Us, Vs>...>;
            using nodes_type = nds::graph_types<Ts...>;

            using node_container_type = std::tuple<std::vector<node_ptr<Ts>>...>;
            using edge_container_type = std::tuple<std::vector<nds::edge<node_type<Us>, node_type<Vs>>>...>;

            //! T type to store as node<T>, T must exists in the graph
            //! Base base type of T to store as node<Base> if T is not in the graph
            template<class B = void, class T>
            auto add(T v)
            {
                // Base = T if Base is not specified
                using Base = std::conditional_t<std::is_same_v<B, void>, T, B>;

                constexpr int type_index = cx::index_of<std::vector<node_ptr<Base>>, node_container_type>::value;

                auto target_node = basic_node<T, Base>{ std::move(v) };
                auto ptr = std::make_unique<basic_node<T, Base>>(std::move(target_node));
                auto last_node = nds::node_ptr<Base>(ptr.get());

                std::get<type_index>(nodes_).emplace_back(std::move(ptr));

                storage_.add_node<type_index>(std::move(ptr));

                return last_node;
            }

            template<class F>
            void nodes(F&& f) const
            {
                nodes<nodes_type>(std::forward<F>(f));
            }

            template<class Nodes, class F>
            void nodes(F&& f) const
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

            
            template<class Source, class Target>
            void connect(node<Source>* source, node<Target>* target)
            {
                // check edges
                constexpr int index = cx::index_of<std::vector<edge<node<Source>, node<Target>>>, edge_container_type>::value;
                // static_assert(index >= 0, "connection between U and V not allowed");

                std::get<index>(edges_).emplace_back(edge<node<Source>, node<Target>>{ source, target });
            }


        public:
            //graph_storage<Types, Edges, storage_type> storage_; // vector, ndb_storage, matrix



            node_container_type nodes_;
            edge_container_type edges_;
        };
    } // internal

    template<class... Ts>
    using graph = typename internal::graph_trait<Ts...>::type;
} // nds

#endif // INCLUDE_NDS_GRAPH2_HPP_NDS


