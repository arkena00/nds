#include <nds/graph.hpp>
#include <nds/encoder/graph.hpp>

#include <nds/graph/ndb_storage.hpp>

struct node { node(std::string n) : name{n}{} std::string name; virtual std::string info() {  return name + "\\n"; } };

struct page { page(std::string n) : name{n}{} std::string name; virtual std::string info() const {  return name + "\\n"; } };
struct web_page : public page { using page::page; std::string url; std::string info() const override {  return name + "\\n" + url; } };
struct explorer_page : public page { using page::page; std::string path; std::string info() const override {  return name + "\\n" + path; } };

namespace nds::encoders
{
    template<>
    template<>
    std::string dot<void>::node_name(const page& p)
    {
        return p.info();
    }
} // nds::encoders


int main()
{
    using Edges = nds::graph_edges<nds::edge<page, page>, nds::edge<::node, page>, nds::edge<page, ::node>>;
    using Types = nds::graph_types<page, node>;

    nds::graph<Types, Edges> g;

    ::web_page wp{"web_page"};
    wp.url = "neuroshok.com";

    ::explorer_page ep{"explorer_page"};
    ep.path = "/home";

    ::node n{ "web_node" };

    auto p0 = g.add(std::move(n));
    auto p1 = g.add<page>(std::move(wp), p0);
    auto p2 = g.add<page>(std::move(ep), p0);

    g.connect(p1, p2);
    g.connect(p2, p1);
/*
    g.connect(p0, p1);
    g.connect(p0, p2);
    g.connect(p1, p2);*/

    //g.nodes<nds::graph_types<page>>([](auto&& node){ std::cout << "\nnode " << node->get().name; });

    g.sources(p1, [](auto&& node) {std::cout << "\nnode " << node->get().name; });

    //nds::encoders::dot<>::encode<nds::console>(g);

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