#include <lemon/list_graph.h>
#include <lemon/maps.h>
#include <lemon/graph_to_eps.h>

#include <nds/graph/lemon.hpp>

struct expression
{

};

struct id_expression : expression
{
    id_expression(std::string n) : name{ std::move(n) } {}
    std::string name = "default";
};



struct edges
{
    struct has{int id = 8;};
    struct is{int id = 9; std::string truc; };
};


int main()
{

    using Nodes = nds::graph_nodes<id_expression>;
    using Edges = nds::graph_edges<edges::is, edges::has>;

    nds::graph<Nodes, Edges, nds::graph_storages::lemon> gg;

    auto n00 = gg.emplace("ngl");


    auto n01 = gg.add(id_expression("ngl01"));
    auto n02 = gg.add(id_expression("ngl02"));
    auto n03 = gg.add(id_expression("ngl03"));

    gg.add_arc(n00, n01, edges::has{});
    gg.add_arc(n00, n02, edges::is{ 7, "aze" });
    gg.add_arc(n00, n03, edges::is{ 6, "pouet" });

    //nds::edge<edges::has> e{  };

    gg.targets<edges::is>(n00, [](auto&& n, auto&& e) { std::cout << "\n__" << n->name <<  " " << e->truc; } );


/*
    lemon::ListDigraph g;
    lemon::ListDigraph::ArcMap<edgemap<int>> e_map(g);

    auto id = new id_expression("ngl");
    auto id1 = new id_expression("ngl1");
    auto id2 = new id_expression("ngl2");

    //idmap n0_map (g, std::move(id));
    lemon::ListDigraph::NodeMap<id_expression*> n0_map(g, id);

    //lemon::ListDigraph::NodeMap<id_expression> n1_map (g, id_expression("concept"));


    auto n0 = g.addNode();
    auto n1 = g.addNode();
    auto n2 = g.addNode();

    n0_map[n0] = id;
    n0_map[n1] = id1;
    n0_map[n2] = id2;


    auto a = g.addArc(n0, n1);
    auto b = g.addArc(n0, n2);
    e_map[a] = 0;


    for (lemon::ListDigraph::OutArcIt i(g, n0); i != lemon::INVALID; ++i)
    {
        std::cout << "\n" << n0_map[g.target(i)]->name_;
    }

*/

    /*
    lemon::graphToEps(g,"descriptor_map_demo.eps").scaleToA4().
    title("Generated graph").
    copyright("(C) 2003-2007 LEMON Project").
    nodeScale(1.0).
    drawArrows().arrowWidth(1).arrowLength(1).
    run();
*/

}