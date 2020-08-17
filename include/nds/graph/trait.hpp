#ifndef INCLUDE_NDS_GRAPH_TRAIT_HPP_NDS
#define INCLUDE_NDS_GRAPH_TRAIT_HPP_NDS

#include <nds/graph/edge.hpp>

namespace nds
{
    template<class... Edges>
    struct graph_rules{};

    template<class... Edge_types>
    struct graph_edges{};

    template<class... Types>
    struct graph_nodes{};


    template<class... Params>
    struct graph_params{};

    namespace graph_storages
    {
        struct tuple_vector;
        struct ndb;
        struct lemon;

        using default_storage = tuple_vector;
    } // graph_storages

    namespace internal
    {
        template<class...>
        class graph;

        // graph<type1, type2, ...>
        template<class... Ts>
        struct graph_trait
        {
            // todo: generate all rules
            using type = graph<nds::graph_nodes<Ts...>, nds::graph_edges<void>, nds::graph_rules<nds::edge<Ts, Ts>...>, graph_storages::default_storage>;
        };

        // graph<T>
        template<class T>
        struct graph_trait<T>
        {
            using type = graph<nds::graph_nodes<T>, nds::graph_edges<void>, nds::graph_rules<nds::edge<T, T>>, graph_storages::default_storage>;
        };

        // graph<graph_nodes>
        template<class... Ts>
        struct graph_trait<nds::graph_nodes<Ts...>>
        {
            using type = graph<nds::graph_nodes<Ts...>, nds::graph_edges<void>, nds::graph_rules<nds::edge<Ts, Ts>...>, graph_storages::default_storage>;
        };

        // graph<graph_nodes, graph_edges>
        template<class... Ts, class... Es>
        struct graph_trait<nds::graph_nodes<Ts...>, nds::graph_edges<Es...>>
        {
            using type = graph<nds::graph_nodes<Ts...>, nds::graph_edges<Es...>, nds::graph_rules<nds::edge<Ts, Ts>...>, graph_storages::default_storage>;
        };

        // graph<graph_nodes, graph_edges, storage>
        template<class... Ts, class... Es, class Storage>
        struct graph_trait<nds::graph_nodes<Ts...>, nds::graph_edges<Es...>, Storage>
        {
            using type = graph<nds::graph_nodes<Ts...>, nds::graph_edges<Es...>, nds::graph_rules<nds::edge<Ts, Ts>...>, Storage>;
        };

        // graph<graph_nodes, graph_rules>
        template<class... Ts, class... Us, class... Vs>
        struct graph_trait<nds::graph_nodes<Ts...>, nds::graph_rules<nds::edge<Us, Vs>...>>
        {
            using type = graph<nds::graph_nodes<Ts...>, nds::graph_edges<void>, nds::graph_rules<nds::edge<Us, Vs>...>, graph_storages::default_storage>;
        };

        // graph<Storage, graph_nodes, graph_rules>
        template<class Storage, class... Ts, class... Us, class... Vs>
        struct graph_trait<nds::graph_nodes<Ts...>, nds::graph_rules<nds::edge<Us, Vs>...>, Storage>
        {
            using type = graph<nds::graph_nodes<Ts...>, nds::graph_edges<void>, nds::graph_rules<nds::edge<Us, Vs>...>, Storage>;
        };
    } // internal
} // nds

#endif // INCLUDE_NDS_GRAPH_TRAIT_HPP_NDS
