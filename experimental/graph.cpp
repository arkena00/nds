#include <nds/graph.hpp>
#include <nds/encoder/graph.hpp>

#include <nds/graph/ndb_storage.hpp>


struct page { page(std::string n) : name{n}{} std::string name; virtual std::string info() {  return name + "\\n"; } };
struct web_page : public page { using page::page; std::string url; std::string info() override {  return name + "\\n" + url; } };
struct explorer_page : public page { using page::page; std::string path; std::string info() override {  return name + "\\n" + path; } };

int main()
{


    nds::graph<page> g;

        using Edges = nds::graph_edges<
        nds::edge<page, page>
        >;

    using Types = nds::graph_types<page>;

    nds::graph<Types, Edges, nds::graph_storages::ndb> gd;

    nds::graph<int, char, bool> gg;

    ::web_page wp{"web_page"};
    wp.url = "neuroshok.com";

    ::explorer_page ep{"explorer_page"};
    ep.path = "/home";

    auto p1 = g.add<page>(std::move(wp));
    auto p2 = g.add<page>(std::move(ep));

    g.connect(p1, p2);

    //g.nodes([](auto&& node){ std::cout << "\nnode " << node->get()->info() << " | " << node->get()->info(); });

    nds::encoders::dot<>::encode<nds::console>(g);

}

/*
node: N
node with value: N : value(type)
edge: --
named edge: -[name]-
arc: --> or <--
name arc: -[name]-> or <-[name]-

G --> N : neuroshok.com (web_page : page)
G --> N : /home/ads (explorer_page : page)
      |
      o --> N: 5 (int) ---------------- o --------- o
      |                                 |           |
      o --> N: 7 (int) o <-[zeta arc]-- o           |
      |                                             |
      o -[custom arc]-> N: 9(int) o -[custom edge]- o

*/