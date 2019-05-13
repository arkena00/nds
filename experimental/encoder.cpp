#include <nds/graph.hpp>
#include <nds/encoder/graph.hpp>

namespace nds
{
    struct stdio
    {
        template<class T>
        static void write(T data)
        {
            std::cout << data;
        }
    };
}

int main()
{
    using Edges = nds::graph_edges<
    nds::edge<int, int>
    >;

    using Types = nds::graph_types<int>;

    nds::graph<Types, Edges> g;

    nds::stdio::write("azeazeaze");

    auto res = nds::encoders::dot<>::encode<std::string>(g);
    //nds::encoders::dot<>::encode<nds::file>(g, "file");
    //nds::encoders::dot<>::encode<nds::stdio>(g);

    std::cout << res;

    /*
    nds::encoders::dot<nds::io_systems::container<std::string>> dot;
    auto str = dot.encode(g);

     nds::encoder<>::encode<std::string>()

    nds::encoders::dot<nds::io_systems::file>> dot{ "path" };
    dot.encode(g);

    nds::encoders::dot<nds::io_systems::std>> dot;
    dot.encode(g);

    nds::graph_encoder<nds::io_systems::std>::encode(g);

    nds::graph_encoder<nds::io_systems::container<>, nds::encoders::dot<>>::encode(g); // dot use graph_encoder params
    nds::graph_encoder<>::encode(g); // container<string> + encoers::dot

    nds::encoder<
    nds::graph_encoder<io_systems::container<vector>>
    , nds::encoders::zip<io_systems::file, encoder_option>
    >::encode(g, "file", encoder_option{ 12, 54, 10 });
    // input g -> encode graph with dot encoder -> output vector
    // input vector -> encoder zip -> output file "file"

    nds::graph_encoder<io_systems::container<vector>> g_enc;
    nds::encoders::zip<io_systems::file, encoder_option> zip_enc{"file", options};

    nds::encoder enc{ g_enc, zip_enc };
    enc.encode(g);
    enc.decode("file");

    g >> g_enc >> zip_enc;

    nds::graph<int> read_g{} << g_enc << zip_enc;

    nds::encoder<nds::graph_encoder<io_systems::container<vector>>
    , nds::encoders::zip<io_systems::file, encoder_option>
      >::encode(g, "file", encoder_option{ 12, 54, 10 });
      */
}

