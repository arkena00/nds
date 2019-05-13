#include <nds/graph.hpp>

#include <string>


struct movie { std::string title; };
struct serie { std::string name; };

struct movie_interface {  };

struct page { std::string name; };
struct web_page : page { std::string url; };
struct explorer_page : page { std::string path; };



int main()
{
    nds::graph<::page, int> g;

    ::web_page wp;
    wp.name = "web_page";
    wp.url = "aze";

    ::explorer_page ep;
    ep.name = "explorer_page";

    auto root = g.add(web_page{"root_page"});
    g.add(web_page{"web_child"}, root);
    g.add(explorer_page{"explorer_child"}, root);
    g.add(5, root);


    for (auto&& node : g.nodes())
    {
        std::cout << "\n__" << node->id;
    }


    /*
    using Types = std::tuple<movie, serie, page>;
    using Properties = std::tuple<std::string>;
    using Interfaces = std::tuple<movie_interface>;

    using Node = std::tuple<Types, Properties, Interfaces>;*/
    //nds::variadic_graph<Node> vg;

    //vg.add_node<movie>();
    //vg.add_node<movie>();
}

// graph<page, node>
// add, del, connect, move

/*
page1, 23
page1, page3
21, 23

edge<page, int>

vector<edge<page, int>>
vector<edge<int, int>>

g.add<page>(source)

g.targets<node_types<page, int, string>>(source)

node<page>, node<int>*/



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