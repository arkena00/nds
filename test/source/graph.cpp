#include "../test.hpp"

#include <nds/graph.hpp>

struct node { node(std::string n) : name{n}{} std::string name; virtual std::string info() {  return name + "\\n"; } };

struct page {  page(std::string n) : name{n}{} std::string name; virtual std::string info() const {  return name + "\\n"; } };
struct web_page : public page { web_page(web_page&&) = delete; using page::page; std::string url; std::string info() const override {  return name + "\\n" + url; } };
struct explorer_page : public page { using page::page; std::string path; std::string info() const override {  return name + "\\n" + path; } };


TEST(graph, base)
{
    ASSERT_TRUE( true == true );

    using Edges = nds::graph_edges<nds::edge<page, page>, nds::edge<::node, page>, nds::edge<page, ::node>>;
    using Types = nds::graph_types<page, node>;

    nds::graph<Types, Edges> g;

    ::web_page wp{"web_page"};
    wp.url = "neuroshok.com";

    ::explorer_page ep{"explorer_page"};
    ep.path = "/home";

    ::node n{ "web_node" };

    nds::node_ptr<::node> p0 = g.add(std::move(n));

    // add
    g.add(::node{"test"});
    g.add(::page{"test"});

    g.add<::node>(::node{"test"});
    g.add<::page>(::explorer_page{"test"});
    g.add<::page, ::explorer_page>(::explorer_page{"test"});


    auto p1 = g.emplace<page, web_page>( p0, "test" );
    auto p2 = g.emplace<page, web_page>( p1, "test2" );


    g.connect(p0, p2);

    nds::node_ptr<::page> source = nullptr;
    g.targets(p0, [](auto&& node){ std::cout << "\nnode " << node->name; });
}