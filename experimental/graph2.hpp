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

            struct internal
            {
                template<class Base, class T>
                struct base_type { using type = Base; };

                template< class T>
                struct base_type<void, T> { using type = T; };
            };


            //! T type to store as node<T>, T must exists in the graph
            //! Base base type of T to store as node<Base> if T is not in the graph
            template<class B = void, class T>
            auto add(T v)
            {
                using Base = typename internal::base_type<B, T>::type;

                constexpr int index = cx::index_of<std::vector<node_ptr<Base>>, node_container_type>::value;

                auto target_node = basic_node<T, Base>{ std::move(v) };
                auto ptr = std::make_unique<basic_node<T, Base>>(std::move(target_node));
                auto last_node = ptr.get();

                std::get<index>(nodes_).emplace_back(std::move(ptr));

                return last_node;
            }

            
            template<class T, class U>
            void connect(node<T>* source, node<U>* target)
            {

            }


        public:
            //graph_storage<graph_storage_matrix> storage_;

            node_container_type nodes_;
            edge_container_type edges_;
        };
    } // internal

    template<class... Ts>
    using graph = typename internal::graph_trait<Ts...>::type;
} // nds



#endif // INCLUDE_NDS_GRAPH2_HPP_NDS