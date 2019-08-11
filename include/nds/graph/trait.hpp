#ifndef INCLUDE_NDS_GRAPH_TRAIT_HPP_NDS
#define INCLUDE_NDS_GRAPH_TRAIT_HPP_NDS

#include <nds/graph/edge.hpp>

namespace nds
{
    template<class... Edges>
    struct graph_edges{};

    template<class... Types>
    struct graph_types{};

    template<class... Params>
    struct graph_params{};

    namespace graph_storages
    {
        struct tuple_vector;
        struct ndb;

        using default_storage = tuple_vector;
    } // graph_storages

    namespace internal
    {
        template<class...>
        struct graph;

        // graph<type1, type2, ...>
        template<class... Ts>
        struct graph_trait
        {
            // todo: generate all edges
            using type = graph<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Ts, Ts>...>, graph_storages::default_storage>;
        };

        // graph<T>
        template<class T>
        struct graph_trait<T>
        {
            using type = graph<nds::graph_types<T>, nds::graph_edges<nds::edge<T, T>>, graph_storages::default_storage>;
        };

        // graph<Graph_types, Graph_edges>
        template<class... Ts, class... Us, class... Vs>
        struct graph_trait<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>>
        {
            using type = graph<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>, graph_storages::default_storage>;
        };

        // graph<Storage, Graph_types, Graph_edges>
        template<class Storage, class... Ts, class... Us, class... Vs>
        struct graph_trait<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>, Storage>
        {
            using type = graph<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>, Storage>;
        };
    } // internal
} // nds

#endif // INCLUDE_NDS_GRAPH_TRAIT_HPP_NDS
