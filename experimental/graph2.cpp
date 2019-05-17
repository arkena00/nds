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


    nds::graph<int> g2;
    g2.add(5);
    g2.add<int>(5);

    nds::graph<page> g;
    auto p = g.add<page>(std::move(wp));

    std::cout << "\n_" << p->get().name;
    std::cout << "\n_" << p->get().url;

    nds::node<page>* np = p;
    std::cout << "\n_" << np->get().name;
    std::cout << "\n_" << np->get().url;

    g.connect(p, p);

}