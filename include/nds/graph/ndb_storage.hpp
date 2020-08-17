#ifndef INCLUDE_NDS_GRAPH_NDB_STORAGE_HPP_NDS
#define INCLUDE_NDS_GRAPH_NDB_STORAGE_HPP_NDS

#include <nds/graph/trait.hpp>
#include <nds/graph/node.hpp>

#include <ndb/initializer.hpp>
#include <ndb/engine/sqlite/sqlite.hpp>
#include <ndb/preprocessor.hpp>
#include <ndb/query.hpp>

ndb_object(page
    , ndb_field(name, std::string, ndb::size<255>)
)

ndb_table(page_arcs
, ndb_field(source_id, int)
, ndb_field(target_id, int)
)

ndb_model(graph, page, page_arcs)

ndb_project(exp_graph,
            ndb_database(graph, graph, ndb::sqlite)
)

namespace dbs
{
    using graph = ndb::databases::exp_graph::graph_;
} // dbs

namespace nds::internal
{
        template<class... Ts, class... Us, class... Vs>
        class graph<nds::graph_nodes<Ts...>, nds::graph_rules<nds::edge<Us, Vs>...>, graph_storages::ndb> //: nds::concept<nds::concepts::graph>
        {
        public:
            template<class T>
            using node_type = node<T>;


            template<class B = void, class T>
            auto add(T v)
            {
                ndb::store(v);
                return 0;
            }

            template<class Source, class Target>
            void connect(node<Source>* source, node<Target>* target)
            {

            }



        public:

        };
} // nds

#endif // INCLUDE_NDS_GRAPH_NDB_STORAGE_HPP_NDS