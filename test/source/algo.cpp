#include "../test.hpp"

#include <nds/graph.hpp>
#include <nds/algorithm/graph.hpp>

struct graph_algorithm : ::testing::Test
{
    graph_algorithm()
    {
        auto n0 = g.add(1);
        auto n1 = g.add(2, n0);
        auto n2 = g.add(3, n0);
    }

     graphs::basic g;
};

TEST_F(graph_algorithm, find_first_if)
{
    bool found = false;
    int it = 0;
    nds::algorithm::graph::find_first_if(g
    , [&it](auto&& node){ ++it; return *node == 2; }
    , [&found](auto&& found_node){ found = true; });

    EXPECT_TRUE( it != g.count_nodes() ); // check if algo stop
    EXPECT_TRUE( found );
}
