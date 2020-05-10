#ifndef TEST_H_NDB
#define TEST_H_NDB

#include "gtest/gtest.h"

#include <nds/graph.hpp>

namespace structs
{
    struct node { node(std::string n) : name{n}{} std::string name; virtual std::string info() {  return name + "\\n"; } };

    struct page {  page(std::string n) : name{n}{} std::string name; };
    struct web_page : public page { using page::page; std::string url; };
    struct explorer_page : public page { using page::page; std::string path; };
} // structs

namespace graphs
{
    using basic = nds::graph<int>;

    using multi_type = nds::graph<
        nds::graph_types<int, char>
        , nds::graph_edges<nds::edge<int, int>, nds::edge<int, char>, nds::edge<char, int>>
    >;

    using complex = nds::graph<
            nds::graph_types<structs::page, structs::node, int>
            , nds::graph_edges<
                nds::edge<structs::page, structs::page>
                , nds::edge<structs::node, structs::page>
                , nds::edge<structs::page, structs::node>
                , nds::edge<structs::page, int>
            >
        >;
} // graphs
#endif // TEST_H_NDB