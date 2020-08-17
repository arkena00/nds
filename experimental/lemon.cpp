#include <lemon/list_graph.h>
#include <lemon/maps.h>
#include <lemon/graph_to_eps.h>

#include <nds/graph/lemon.hpp>

struct expression
{

};

struct id_expression : expression
{
    id_expression(std::string name) : name_{ std::move(name) } {}
    std::string name_ = "default";
};


class idmap : public lemon::MapBase<lemon::ListDigraph::Node, id_expression>
{
  const lemon::ListDigraph &g;
  const id_expression &pot;

public:
  auto operator[](int e) const {
    return 0;
  }

  idmap(const lemon::ListDigraph &_g, id_expression&_p)
    : g(_g), pot(_p) {};
};



struct edge
{
};

int main()
{
    using Edges = nds::graph_edges<nds::edge<id_expression, id_expression>>;
    using Types = nds::graph_nodes<id_expression>;

    nds::graph<Types, Edges, nds::graph_storages::lemon> gg;

    auto n00 = gg.add(id_expression("ngl"));
    auto n01 = gg.add(id_expression("ngl01"));
    auto n02 = gg.add(id_expression("ngl02"));

    gg.add_arc(n00, n01);
    gg.add_arc(n00, n02);

    gg.targets(n00, [](auto&& n) { std::cout << "\n__" << n->name_; } );


    lemon::ListDigraph g;

    lemon::ListDigraph::ArcMap<edge> edge_logic(g);

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



    for (lemon::ListDigraph::OutArcIt i(g, n0); i != lemon::INVALID; ++i)
    {
        std::cout << "\n" << n0_map[g.target(i)]->name_;
    }



    /*
    lemon::graphToEps(g,"descriptor_map_demo.eps").scaleToA4().
    title("Generated graph").
    copyright("(C) 2003-2007 LEMON Project").
    nodeScale(1.0).
    drawArrows().arrowWidth(1).arrowLength(1).
    run();
*/

}