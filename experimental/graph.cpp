#include <nds/graph.hpp>

#include <string>
#include <nds/encoder/graph.hpp>

struct movie { std::string title; };
struct serie { std::string name; };

struct movie_interface {  };

struct page { page(std::string n) : name{n}{} std::string name; virtual std::string info() {  return name + "\\n"; } };
struct web_page : public page { using page::page; std::string url; std::string info() override {  return name + "\\n" + url; } };
struct explorer_page : public page { using page::page; std::string path; std::string info() override {  return name + "\\n" + path; } };

namespace std
{
    std::string to_string(page& p)
    {
        return p.info();
    }
}

int main()
{
    //nds::graph<::page, graph_params<wrapping_type<std::unique_ptr>>> g;
    nds::graph<::page> g;

    //graph<page, nds::graph_params::unique>


    ::web_page wp{"a"};
    wp.name = "web_page";
    wp.url = "neuroshok.com";



    ::explorer_page ep{"r"};
    ep.name = "explorer_page";

    g.add(page("a"));

    /*
    auto root = g.add<::page>(web_page{"root_page"});
    auto wc = g.add<::page>(web_page{"web_child"}, root);
    g.add<::page>(explorer_page{"explorer_child"}, root);
    g.add<page>(wp, wc);*/
    //g.add(5, root);


    //g.nodes([](auto&& node){ std::cout << "\nnode " << node->get()->info() << " | " << node->get()->info(); });

    nds::encoders::dot<>::encode<nds::console>(g);




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