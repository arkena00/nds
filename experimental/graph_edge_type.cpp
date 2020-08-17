#include <nds/graph.hpp>
#include <nds/encoder/graph.hpp>


#include <nds/algorithm/graph.hpp>

struct edges
{
    struct has;
    struct is;
};

int main()
{
    using Nodes = nds::graph_nodes<int>;
    using Edges = nds::graph_edges<edges::has, edges::is>;

    nds::graph<Nodes, Edges> g;

    auto n0 = g.emplace(0);
    auto n1 = g.emplace(1);

    //g.add_arc<edges::has>(n0, n1);
    //g.add_arc<edges::is>(n0, n1);

    //g.targets<edges::has>(n0, [](auto&& node) { });
}