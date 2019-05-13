#ifndef INCLUDE_NDS_GRAPH_HPP_NDS
#define INCLUDE_NDS_GRAPH_HPP_NDS

#include <nds/graph/edge.hpp>
#include <nds/graph/node.hpp>

#include <nds/cx/for_each.hpp>
#include <nds/cx/index_of.hpp>
#include <nds/cx/type_str.hpp>

#include <tuple>
#include <vector>

namespace nds
{
    template<class... Edges>
    struct graph_edges{};

    template<class... Types>
    struct graph_types{};

    template<class GT, class GE>
    struct graph{};

    template<class... Ts, class... Us, class... Vs>
    struct graph<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>>
    {
    public:
        template<class T>
        using node_ptr = std::unique_ptr<node<T>>;

        using edges_type = nds::graph_edges<nds::edge<Us, Vs>...>;

        using node_container_type = std::tuple<std::vector<node_ptr<Ts>>...>;
        using edge_container_type = std::tuple<std::vector<nds::edge<nds::node<Us>, nds::node<Vs>>>...>;

        template<class T>
        node<T>* add(T v);

        template<class... Node_types>
        auto& nodes();

        template<class F>
        auto edges(F&& f);
        template<class Edges, class F>
        auto edges(F&& f);

        template<class Source, class Target>
        void connect(Source* s, Target* t);
        template<class T>
        void connect(int s, int t);

        template<class Source>
        void targets(Source* source);

    private:
        node_container_type data_;
        edge_container_type edges_;
    };
} // nds

#include "graph.tpp"

#endif // INCLUDE_NDS_GRAPH_HPP_NDS