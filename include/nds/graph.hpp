#ifndef INCLUDE_NDS_GRAPH_HPP_NDS
#define INCLUDE_NDS_GRAPH_HPP_NDS

#include <nds/graph/edge.hpp>
#include <nds/graph/node.hpp>

#include <nds/cx/for_each.hpp>
#include <nds/cx/index_of.hpp>
#include <nds/cx/type_str.hpp>

#include <memory>
#include <tuple>
#include <vector>

namespace nds
{
    template<class... Edges>
    struct graph_edges{};

    template<class... Types>
    struct graph_types{};

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
            using node_ptr = std::unique_ptr<node<T>>;

            using edges_type = nds::graph_edges<nds::edge<Us, Vs>...>;
            using nodes_type = nds::graph_types<Ts...>;

            using node_container_type = std::tuple<std::vector<node_ptr<Ts>>...>;
            using edge_container_type = std::tuple<std::vector<nds::edge<nds::node<Us>, nds::node<Vs>>>...>;

            template<class T>
            node<T>* add(T v);

            template<class F>
            void nodes(F&& f) const;
            template<class Nodes, class F>
            void nodes(F&& f) const;

            template<class F>
            void edges(F&& f) const;
            template<class Edges, class F>
            void edges(F&& f) const;
            
            template<class Source, class Target>
            void connect(Source* s, Target* t);
            template<class T>
            void connect(int s, int t);

            template<class Source, class F>
            void targets(Source* source, F&& f);
            
            std::size_t count_nodes();
            std::size_t count_edges();

        public:
            node_container_type nodes_;
            edge_container_type edges_;
        };
    } // internal

    template<class... Ts>
    using graph = typename internal::graph_trait<Ts...>::type;
} // nds

#include "graph.tpp"

#endif // INCLUDE_NDS_GRAPH_HPP_NDS