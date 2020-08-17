#include <nds/graph.hpp>
#include <nds/encoder/graph.hpp>


#include <nds/algorithm/graph.hpp>

struct node_base { virtual std::string info() = 0; };
struct node : node_base
{
    node(std::string n) : name{n}{  }

    node(nds::node_ptr<const ::node> nn, std::string n) : name{n}
    {

    }

    std::string name; virtual std::string info() {  return name + "\\n"; }
};

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
    using Types = nds::graph_nodes<page, node>;

    nds::graph<Types, Edges> g;

    auto n0 = g.emplace<::page, ::page>("web_node");

    auto p1 = g.emplace<page, web_page>( n0, "web_page1" );
    auto p2 = g.emplace<page, web_page>( n0, "web_page2" );
    auto p3 = g.emplace<page, web_page>( n0, "web_page3" );

    auto n1 = g.emplace<::page, ::page>("dev_node");

    auto d1 = g.emplace<page, web_page>( n1, "web_page1" );
    auto d2 = g.emplace<page, web_page>( n1, "web_page2" );
    auto d3 = g.emplace<page, web_page>( n1, "web_page3" );

    auto n00 = g.emplace<::page, ::page>("main_node");
    g.connect(n00, n0);
    g.connect(n00, n1);

    g.targets(n0, [](auto&& node) { std::cout << "\n" << node->name; });
    g.erase(p3);
    std::cout << "\n_______________";
    g.targets(n0, [](auto&& node) { std::cout << "\n" << node->name; });
    /*
    main -> web_node
         -> dev_node

        web_page
        web_page*/


    //std::cout << "/" << d1->name;
    //nds::algorithm::graph::source_path(g, d1, [](auto&& node) { std::cout << "/" + node->name; });



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