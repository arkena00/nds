#ifndef INCLUDE_NDS_GRAPH_HPP_NDS
#define INCLUDE_NDS_GRAPH_HPP_NDS

#include <nds/graph/trait.hpp>
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
    namespace internal
    {

        template<class... Ts, class... Us, class... Vs>
        struct graph<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>, graph_storages::tuple_vector> //: nds::concept<nds::concepts::graph>
        {
        public:
            template<class T>
            using node_type = node<T>;

            template<class T>
            using node_ptr = std::unique_ptr<node_type<T>>;

            using nodes_type = nds::graph_types<Ts...>;
            using edges_type = nds::graph_edges<edge<Us, Vs>...>;

            using node_container_type = std::tuple<std::vector<node_ptr<Ts>>...>;
            using edge_container_type = std::tuple<std::vector<nds::edge<node_type<Us>, node_type<Vs>>>...>;

            template<class B = void, class T>
            auto add(T v);
            template<class B = void, class T, class Source>
            auto add(T v, node_type<Source>*);

            template<class Source, class Target>
            void connect(node_type<Source>* source, node_type<Target>* target);

            template<class F>
            void nodes(F&& f) const;
            template<class Nodes, class F>
            void nodes(F&& f) const;

            template<class F>
            void edges(F&& f) const;
            template<class Edges, class F>
            void edges(F&& f) const;

            template<class Target, class F>
            void sources(node_type<Target>* target, F&& f);

            template<class Source, class F>
            void targets(node_type<Source>* source, F&& f);

            static constexpr std::size_t count_nodes_type();
            static constexpr std::size_t count_edges_type();

            std::size_t count_nodes() const;
            std::size_t count_edges() const;
            /*

            template<class Source, class Target>
            void connect(Source* s, Target* t);
            template<class T>
            void connect(int s, int t);
             */

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