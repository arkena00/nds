#include <nds/graph.hpp>
#include <nds/encoder/graph.hpp>

#include <nds/graph/ndb_storage.hpp>

struct page : ndb::object<dbs::graph, ndb::objects::page>
{
    page(std::string n) {} virtual std::string info() { return name + "\\n"; }
};
struct web_page : public page { using page::page; std::string url; std::string info() override {  return name + "\\n" + url; } };
struct explorer_page : public page { using page::page; std::string path; std::string info() override {  return name + "\\n" + path; } };


int main()
{
    ndb::initializer<ndb::sqlite> init;
    ndb::connect<dbs::graph>();

    nds::graph<nds::graph_storage::tuple_vector, page> g;

    nds::graph<nds::graph_storage::ndb, page> gd;

    ::web_page wp{"web_page"};
    wp.url = "neuroshok.com";

    ::explorer_page ep{"explorer_page"};
    ep.path = "/home";

    auto p1 = g.add<page>(std::move(wp));
    auto p2 = g.add<page>(std::move(ep));

    auto nd1 = gd.add(page{ "test" });

    g.connect(p1, p2);

    //g.nodes([](auto&& node){ std::cout << "\nnode " << node->get()->info() << " | " << node->get()->info(); });

    nds::encoders::dot<>::encode<nds::console>(g);

}