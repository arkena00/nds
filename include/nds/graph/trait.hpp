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

    namespace graph_storage
    {
        struct tuple_vector;
        struct ndb;
    } // graph_storages

    namespace internal
    {
        template<class...>
        struct graph;

        template<class Storage, class...>
        struct graph_trait;

        // graph<T>
        template<class Storage, class T>
        struct graph_trait<Storage, T>
        {
            using type = graph<nds::graph_types<T>, nds::graph_edges<nds::edge<T, T>>, Storage>;
        };

        // graph<Graph_types, Graph_edges>
        template<class Storage, class... Ts, class... Us, class... Vs>
        struct graph_trait<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>, Storage>
        {
            using type = graph<nds::graph_types<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>, Storage>;
        };
    } // internal
} // nds

#endif // INCLUDE_NDS_GRAPH_TRAIT_HPP_NDS
