#ifndef INCLUDE_NDS_ALGORITHM_GRAPH_FIND_HPP_NDS
#define INCLUDE_NDS_ALGORITHM_GRAPH_FIND_HPP_NDS

#include <nds/graph.hpp>

namespace nds::algorithm::graph
{
    template<class Graph, class On_match, class Predicat>
    auto find(Graph& graph, On_match&& on_match, Predicat&& predicat)
    {
        bool found = false;
        nds::cx::for_each<Graph::nodes_type>([&graph, &predicat, &found, &on_match](auto&& nt)
        {
            using input_node_type = typename Graph::template node_type<typename std::decay_t<decltype(nt)>::type>;

            auto loop_graph_type = [&predicat, &found, &on_match](auto&& vector)
            {
                using graph_node_type = typename std::decay_t<decltype(vector)>::value_type::element_type; // node_type<T>
                if constexpr (std::is_same_v<input_node_type, graph_node_type>)
                {
                    if (found) return;
                    for (auto&& node : vector)
                    {
                        if (predicat(node.get()))
                        {
                            found = true;
                            on_match(node.get());
                            return;
                        }
                    }
                }
            };

            std::apply([&](auto&&... vectors) { (loop_graph_type(vectors), ...); }, graph.nodes_);
        });

        //return found_node;
    }
} // nds::algorithm::graph


#endif // INCLUDE_NDS_ALGORITHM_GRAPH_FIND_HPP_NDS