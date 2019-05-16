#include <benchmark/benchmark.h>

#include "graph_lambda.hpp"
#include <nds/algorithm/bfs.hpp>
#include <nds/encoder/graph.hpp>
#include <nds/graph.hpp>

template<class T>
T make_graph(int nodes);

template<>
nds::graph<int> make_graph<nds::graph<int>>(int nodes)
{
    nds::graph<int> g;
    for (auto i = 0; i != nodes; ++i)
    {
        g.add(i);
    }

    for (int i = 0; i != nodes; ++i)
    {
        g.connect<int>(i, (i + 1) % nodes);
        g.connect<int>((i + 2) % nodes, (i + 5) % nodes);
    }
    return g;
}

template<>
lambda_graph make_graph<lambda_graph>(int nodes)
{
    lambda_graph g(nodes);
    for (auto i = 0; i != nodes; ++i)
    {
        g.addEdge(i, (i + 1) % nodes);
        g.addEdge((i + 2) % nodes, (i + 5) % nodes);
    }
    return g;
}

auto graph_lambda = [](benchmark::State& state)
{
    auto g = make_graph<lambda_graph>(state.range(0));

    while (state.KeepRunning())
    {
        g.BFS(0);
    }
};

auto nds_graph = [](benchmark::State& state)
{
    const int nodes = state.range(0);

    auto g = make_graph<nds::graph<int>>(state.range(0));

    nds::algorithm::bfs bfs(g);

    while (state.KeepRunning())
    {
        bfs.process();
    }
};

auto nds_graph2 = [](benchmark::State& state)
{
    const int nodes = state.range(0);

    auto g = make_graph<nds::graph<int>>(state.range(0));

    nds::algorithm::bfs2 bfs(g);

    while (state.KeepRunning())
    {
        bfs.process();
    }
};

int main(int argc, char** argv)
{
/*
    auto g = make_graph<lambda_graph>(5);
    g.BFS(0);

    auto g2 = make_graph<nds::graph<int>>(5);
    nds::algorithm::bfs bfs(g2);
    bfs.process();
    //nds::encoders::dot<>::encode<nds::console>(g2);

    g2.edges([](auto&& edge){ std::cout << "\nedge " << edge.source->get() << " | " << edge.target->get(); });
    */


    auto unit = benchmark::kMicrosecond;

    benchmark::RegisterBenchmark("graph_lambda", graph_lambda)->Unit(unit)->RangeMultiplier(100)->Range(10, 100000);
    benchmark::RegisterBenchmark("nds_graph", nds_graph)->Unit(unit)->RangeMultiplier(100)->Range(10, 100000);
    benchmark::RegisterBenchmark("nds_graph2", nds_graph2)->Unit(unit)->RangeMultiplier(100)->Range(10, 100000);

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}
