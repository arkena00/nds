#ifndef INCLUDE_NDS_GRAPH_STORAGE_HPP_NDS
#define INCLUDE_NDS_GRAPH_STORAGE_HPP_NDS

#include <nds/graph/trait.hpp>
#include <nds/graph/node.hpp>

#include <memory>
#include <vector>

namespace nds
{
    namespace graph_storages
    {
        struct tuple_vector;
        struct ndb;
    } // graph_storages

    template<class Storage_type, class...>
    struct graph_storage;

    template<class... Ts, class... Us, class... Vs>
    struct graph_storage<graph_storages::tuple_vector, nds::graph_nodes<Ts...>, nds::graph_edges<nds::edge<Us, Vs>...>>
    {
        template<class T>
        using node_type = node<T>;

        template<class T>
        using node_ptr = std::unique_ptr<node_type<T>>;

        using node_container_type = std::tuple<std::vector<node_ptr<Ts>>...>;
        using edge_container_type = std::tuple<std::vector<nds::edge<node_type<Us>, node_type<Vs>>>...>;


    };
} // nds

#endif // INCLUDE_NDS_GRAPH_STORAGE_HPP_NDS
