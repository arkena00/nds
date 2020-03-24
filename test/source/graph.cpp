#include "../test.hpp"

#include <nds/graph.hpp>
#include <nds/cx/index_of.hpp>

TEST(graph, construction)
{
    struct ctor
    {
        ctor(int ) : node_ctor { false } {}
        ctor(nds::node_ptr<ctor>, int) : node_ctor { true }{ }
        bool node_ctor = false;
    };

    nds::graph<ctor> g;

    auto n0 = g.add(ctor{0});

    auto n1 = g.emplace(n0, 0);
    EXPECT_TRUE( n1->node_ctor == true );

    auto n2 = g.emplace(0);
    EXPECT_TRUE( n2->node_ctor == true );
}

TEST(graph, adding_basic)
{
    graphs::basic g;

    auto i0 = g.add(9);
    EXPECT_TRUE( *i0 == 9 );

    auto i1 = g.emplace(8);
    EXPECT_TRUE( *i1 == 8 );
}

TEST(graph, adding_multi)
{
    graphs::multi_type g;

    auto i0 = g.add(9);
    EXPECT_TRUE( *i0 == 9 );

    auto i1= g.add('A');
    EXPECT_TRUE( *i1 == 'A' );

    auto i2 = g.emplace(8);
    EXPECT_TRUE( *i2 == 8 );

    auto i3 = g.emplace<char>('B');
    EXPECT_TRUE( *i3 == 'B' );
}

TEST(graph, adding_complex)
{
    graphs::complex g;

    auto i0 = g.add(structs::page{ "page" });
    EXPECT_TRUE( i0->name == "page" );

    auto i1 = g.add<structs::page>(structs::web_page{ "web_page" });
    EXPECT_TRUE( i1->name == "web_page" );

    auto move_p = structs::explorer_page{ "explorer_page" };
    auto i2 = g.add<structs::page>(std::move(move_p));
    EXPECT_TRUE( i2->name == "explorer_page" );

    auto i3 = g.emplace<structs::page>( "emplace_page" );
    EXPECT_TRUE( i3->name == "emplace_page" );

    auto i4 = g.emplace<structs::page, structs::web_page>( "web_page" );
    EXPECT_TRUE( i4->name == "web_page" );
}

TEST(graph, edging_basic)
{
    graphs::basic g;

    nds::node_ptr<int> n0 = g.add(1);
    auto n1 = g.add(2);
    auto n2 = g.add(3);
    auto n3 = g.add(4, n1);

    g.connect(n0, n1);
    g.connect(n0, n2);
    g.connect(n3, n1);

    std::vector<int> v_nodes;
    g.nodes([&v_nodes](auto&& node) { v_nodes.push_back(*node); });
    EXPECT_TRUE( v_nodes.size() == g.count_nodes() );
    EXPECT_TRUE( v_nodes[0] == 1 && v_nodes[1] == 2 && v_nodes[2] == 3 );

    std::vector<int> v_targets;
    g.targets(n0, [&v_targets](auto&& node) { v_targets.push_back(*node); });
    EXPECT_TRUE( v_targets.size() == 2 );
    EXPECT_TRUE( v_targets[0] == 2 && v_targets[1] == 3 );

    std::vector<int> v_sources;
    g.sources(n1, [&v_sources](auto&& node) { v_sources.push_back(*node); });
    ASSERT_TRUE( v_sources.size() == 2 );
    EXPECT_TRUE( v_sources[0] == *n0 && v_sources[1] == *n3 );
}

TEST(graph, edging_multi)
{
    graphs::multi_type g;

    nds::node_ptr<int> n0 = g.add(1);
    nds::node_ptr<char> n1 = g.add('A');
    nds::node_ptr<char> n2 = g.add('B');
    nds::node_ptr<int> n3 = g.add(2);

    g.connect(n0, n1);
    g.connect(n0, n2);
    g.connect(n0, n3);

    std::vector<int> v_nodes;
    g.nodes([&v_nodes](auto&& node) { v_nodes.push_back(*node); });
    ASSERT_TRUE( v_nodes.size() == g.count_nodes() );
    EXPECT_TRUE( v_nodes[0] == 1 && v_nodes[1] == 2 && v_nodes[2] == 'A' );

    std::vector<char> v_char_nodes;
    g.nodes<nds::graph_types<char>>([&v_char_nodes](auto&& node) { v_char_nodes.push_back(*node); });
    EXPECT_TRUE( v_char_nodes[0] == 'A' && v_char_nodes[1] == 'B' );

    std::vector<int> v_targets;
    g.targets(n0, [&v_targets](auto&& node) { v_targets.push_back(*node); });
    ASSERT_TRUE( v_targets.size() == 3 );
    EXPECT_TRUE( v_targets[0] == 2 && v_targets[1] == 'A' );

    std::vector<char> v_char_targets;
    g.targets<nds::graph_types<char>>(n0, [&v_char_targets](auto&& node) { v_char_targets.push_back(*node); });
    ASSERT_TRUE( v_char_targets.size() == 2 );
    EXPECT_TRUE( v_char_targets[0] == 'A' && v_char_targets[1] == 'B' );

    std::vector<char> v_int_targets;
    g.targets<nds::graph_types<int>>(n0, [&v_int_targets](auto&& node) { v_int_targets.push_back(*node); });
    ASSERT_TRUE( v_int_targets.size() == 1 );
    EXPECT_TRUE( v_int_targets[0] == 2  );

    std::vector<int> v_sources;
    g.sources(n1, [&v_sources](auto&& node) { v_sources.push_back(*node); });
    ASSERT_TRUE( v_sources.size() == 1 );
    EXPECT_TRUE( v_sources[0] == *n0  );
}

TEST(graph, edging_complex)
{
    graphs::complex g;

    auto n0 = g.add(structs::page{ "page" });
    auto n1 = g.add(0);

    // g.connect(n1, n0); // compile time error
}