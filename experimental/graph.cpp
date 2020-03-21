#include <nds/graph.hpp>
#include <nds/encoder/graph.hpp>

#include <nds/graph/ndb_storage.hpp>
#include <nds/algorithm/graph.hpp>

struct node_base { virtual std::string info() = 0; };
struct node : node_base { node(std::string n) : name{n}{} std::string name; virtual std::string info() {  return name + "\\n"; } };

struct page {  page(std::string n) : name{n}{} std::string name; virtual std::string info() const {  return name + "\\n"; } };
struct web_page : public page { web_page(web_page&&) = delete; using page::page; std::string url; std::string info() const override {  return name + "\\n" + url; } };
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

    nds::node_ptr<::node> p0 = g.add(std::move(n));
    nds::node_ptr<const ::node> cc { p0 };

    auto p1 = g.emplace<page, web_page>( p0, "test" );
    auto p2 = g.emplace<page, web_page>( p1, "test2" );

    //g.connect(p1, p2);
    //g.connect(p2, p1);

    //g.connect(p0, p1);
    g.connect(p0, p2);
    //g.connect(p1, p2);

    nds::algorithm::graph::for_each(g, [](auto&& node)
    {
        std::cout << "\n" << node->name;
    });

    nds::node_ptr<::page> source = nullptr;
    g.nodes<nds::graph_types<page, node>>([](auto&& node)
    {
        std::cout << "\n: " << node->name;
    });

    //nds::node_ptr<::page> source;

    /*
    nds::algorithm::graph::source_path(g, p2, [](auto&& node){ return node->get().name == "web_node"; });

    nds::algorithm::graph::find_if(g, [](auto&& node){ return node->get().name == "web_node"; }
    , [](auto&& node)
    {
        std::cout << node->get().name << "\n";
    });

    nds::algorithm::graph::for_each(g, [](auto&& node)
    {
        std::cout << "\n" << node->get().name;
    });*/


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