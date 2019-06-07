#include <iostream>
#include <vector>

#include "graph2.hpp"

struct page { int name = -1; };
struct web_page : page { int url = -1; };

int main()
{
    web_page wp;
    wp.name = 3;
    wp.url = 10;

    web_page wp2;
    wp2.name = 99;


    nds::graph<int> g2;
    g2.add(5);
    g2.add<int>(5);

    nds::graph<page> g;
    auto p = g.add<page>(std::move(wp));
    g.add<page>(std::move(wp2));

    std::cout << "\n_" << p->get().name;
    std::cout << "\n_" << p->get().url;

    g.connect(p, p);

    g.nodes([](auto&& node){ std::cout << node->get().name; });

}
