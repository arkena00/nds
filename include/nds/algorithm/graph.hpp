#ifndef INCLUDE_NDS_ALGORITHM_GRAPH_HPP_NDS
#define INCLUDE_NDS_ALGORITHM_GRAPH_HPP_NDS

#include <nds/graph.hpp>

namespace nds::algorithm
{
    struct graph
    {
        //! \brief Find the first element for which predicate is true then return
        //! Callback is called while predicate is true
        //! Return when predicate is true
        template<class Graph, class Predicate, class Callback>
        static void find_first_if(Graph& graph, Predicate&& predicate, Callback&& callback)
        {
            bool stop = false;
            nds::cx::for_each<typename Graph::nodes_type>([&graph, &stop, &predicate, &callback](auto&& nt)
            {
                using input_node_type = typename Graph::template node_type<typename std::decay_t<decltype(nt)>::type>;

                auto loop_graph_type = [&stop, &predicate, &callback](auto&& vector)
                {
                    using graph_node_type = typename std::decay_t<decltype(vector)>::value_type::element_type; // node_type<T>
                    if constexpr (std::is_same_v<input_node_type, graph_node_type>)
                    {
                        if (stop) return;
                        for (auto&& uptr : vector)
                        {
                            nds::node_ptr<typename graph_node_type::base_type> nptr{ uptr.get() };
                            if (predicate(nptr))
                            {
                                callback(nptr);
                                stop = true;
                                return;
                            }
                        }
                    }
                };

                std::apply([&](auto&&... vectors) { (loop_graph_type(vectors), ...); }, graph.nodes_);
            });
        }

        template<class Graph, class Callback>
        static void for_each(Graph& graph, Callback&& callback)
        {
            nds::cx::for_each<typename Graph::nodes_type>([&graph, &callback](auto&& nt)
            {
                using input_node_type = typename Graph::template node_type<typename std::decay_t<decltype(nt)>::type>;

                auto loop_graph_type = [&callback](auto&& vector)
                {
                    using graph_node_type = typename std::decay_t<decltype(vector)>::value_type::element_type; // node_type<T>
                    if constexpr (std::is_same_v<input_node_type, graph_node_type>)
                    {
                        for (auto&& uptr : vector) callback(node_ptr<typename graph_node_type::base_type>{ uptr.get() });
                    }
                };
                std::apply([&](auto&&... vectors) { (loop_graph_type(vectors), ...); }, graph.nodes_);
            });
        }

        template<class Graph, class T, class Callback>
        static void source_path(Graph& g, nds::node_ptr<T> origin_node, Callback&& callback)
        {
            bool has_source = false;
            auto test_node = origin_node;

            auto f = [&](auto&& node)
            {
                has_source = false;
                g.template sources<nds::graph_nodes<T>>(node, [&](auto path_node)
                {
                    if constexpr(std::is_same_v<decltype(path_node), nds::node_ptr<T>>)
                    {
                        has_source = true;
                        callback(path_node);
                        test_node = path_node;
                    }
                });
            };

            while (has_source)
            {
                f(test_node);
            }
        }
    };
} // nds::algorithm::graph

#endif // INCLUDE_NDS_ALGORITHM_GRAPH_HPP_NDS