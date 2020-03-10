#include "../test.hpp"

#include <nds/graph.hpp>
#include <nds/algorithm/graph.hpp>

struct node { node(std::string n) : name{n}{} std::string name; virtual std::string info() {  return name + "\\n"; } };

struct page {  page(std::string n) : name{n}{} std::string name; virtual std::string info() const {  return name + "\\n"; } };
struct web_page : public page { web_page(web_page&&) = delete; using page::page; std::string url; std::string info() const override {  return name + "\\n" + url; } };
struct explorer_page : public page { using page::page; std::string path; std::string info() const override {  return name + "\\n" + path; } };


TEST(graph, algo)
{
    ASSERT_TRUE( true == true );

    using Edges = nds::graph_edges<nds::edge<page, page>, nds::edge<::node, page>, nds::edge<page, ::node>>;
    using Types = nds::graph_types<node, page>;

    nds::graph<Types, Edges> graph;

    ::web_page wp{"web_page"};
    ::explorer_page ep{"explorer_page"};
    ::node n{ "web_node" };

    nds::node_ptr<::node> p0 = graph.add(std::move(n));
    auto p1 = graph.emplace<page, web_page>( p0, "web_page1" );
    auto p2 = graph.emplace<page, web_page>( p1, "web_page2" );

    std::vector<std::string> check_foreach;
    nds::algorithm::graph::for_each(graph, [&check_foreach](auto&& node)
    {
        check_foreach.push_back(node->name);
    });
    ASSERT_TRUE(check_foreach.size() == 3);
    ASSERT_TRUE(check_foreach[0] == "web_node");

    std::string check;
    nds::algorithm::graph::find_first_if(graph
    , [&](auto&& node){ return node->name == "web_node"; }
    , [&](auto&& found_node){ check += found_node->name; });
    ASSERT_TRUE( check == "web_node" );
}