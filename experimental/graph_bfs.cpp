#include <algorithm>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

#include <nds/encoder/graph.hpp>
#include <nds/graph.hpp>
#include <nds/algorithm/bfs.hpp>

int main()
{
    using Edges = nds::graph_rules<
        nds::edge<int, int>
        >;

    using Types = nds::graph_nodes<int>;


    nds::graph<int> g;


    auto n0 = g.add(0);
    auto n1 = g.add(1);
    auto n2 = g.add(2);
    auto n3 = g.add(3);
    auto n4 = g.add(4);
    auto n5 = g.add(5);

    g.connect(n3, n5);
    g.connect(n2, n4);
    g.connect(n1, n3);
    g.connect(n0, n1);
    g.connect(n0, n2);
    g.connect(n3, n4);
    g.connect(n4, n5);
    g.connect(n1, n4);

    g.connect(n0, n4);

    /*
    std::random_device rd;
    std::mt19937 rng(rd());

    std::shuffle(std::get<0>(g.edges_).begin(), std::get<0>(g.edges_).end(), rng);*/

    //nds::encoders::dot<>::encode<nds::console>(g);

    g.edges([](auto&& edge){ std::cout << "\nedge " << edge.source->get() << " | " << edge.target->get(); });

    nds::algorithm::bfs2 bfs(g);
    bfs.process();


    //g.process<nds::algorithm::bfs>
    // nds::process<algo>(data);

}