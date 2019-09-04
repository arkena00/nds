#ifndef INCLUDE_NDS_ALGORITHM_GRAPH_FIND_HPP_NDS
#define INCLUDE_NDS_ALGORITHM_GRAPH_FIND_HPP_NDS

#include <nds/graph.hpp>

namespace nds::algorithm::graph
{
    //! Callback is called while predicate is true
    //! Return when predicate is false
    template<class Graph, class Callback, class Predicate>
    auto find(Graph& graph, Callback&& callback, Predicate&& predicate)
    {
        bool predicate_value = true;
        nds::cx::for_each<typename Graph::nodes_type>([&graph, &predicate, &predicate_value, &callback](auto&& nt)
        {
            using input_node_type = typename Graph::template node_type<typename std::decay_t<decltype(nt)>::type>;

            auto loop_graph_type = [&predicate, &predicate_value, &callback](auto&& vector)
            {
                using graph_node_type = typename std::decay_t<decltype(vector)>::value_type::element_type; // node_type<T>
                if constexpr (std::is_same_v<input_node_type, graph_node_type>)
                {
                    for (auto&& node : vector)
                    {
                        if (!predicate(node.get())) return;
                        callback(node.get());
                    }
                }
            };

            std::apply([&](auto&&... vectors) { (loop_graph_type(vectors), ...); }, graph.nodes_);
        });

        //return found_node;
    }
} // nds::algorithm::graph


#endif // INCLUDE_NDS_ALGORITHM_GRAPH_FIND_HPP_NDS