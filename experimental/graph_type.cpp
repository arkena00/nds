#include <tuple>
#include <iostream>
#include <vector>

#include <nds/graph.hpp>
#include <nds/encoder/graph.hpp>

int main()
{
    using Edges = nds::graph_edges<
        nds::edge<int, char>,
        nds::edge<int, int>
        >;

    using Types = nds::graph_types<int, char, std::string>;


    nds::graph<Types, Edges> g;


    auto n1 = g.add<int>(12);
    auto n2 = g.add<int>(15);
    auto n3 = g.add<char>(97);
    auto n4 = g.add<char>(98);

    g.connect(n1, n4); // int char
    g.connect(n1, n2); // int int
    g.connect(n2, n3); // int char
    // g.connect(n3, n4); // char char // error

    g.nodes<int, char>();

    g.targets(n1);

    using Edges_filter = nds::graph_edges<nds::edge<int, char>>;

    g.edges([](auto&& edge){ std::cout << "\nedge " << edge.source->get() << " | " << edge.target->get(); });

}

/*
g.add(n)
g.del(n)
g.connect(s, t)
g.disconnect(s, t)
g.move(ns, nt)
g.sources(n)
g.targets(n)*/