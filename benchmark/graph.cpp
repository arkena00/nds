#include <benchmark/benchmark.h>

#include <nds/graph.hpp>
#include "graph_lambda.hpp"

auto graph_lambda = [](benchmark::State& state)
{
  const int nodes = 20000;
  Graph g(nodes);
  for (auto i = 0; i != nodes; ++i)
  {
      g.addEdge(i, (i + 1) % nodes);
      g.addEdge((i + 2) % nodes, (i + 5) % nodes);
  }

  while(state.KeepRunning())
  {
      g.BFS(2);
  }
};

auto nds_graph = [](benchmark::State& state)
{
    const int nodes = 20000;

    using Edges = nds::graph_edges<
    nds::edge<int, int>
    >;

    using Types = nds::graph_types<int>;

    nds::graph<Types, Edges> g;

    for (auto i = 0; i != nodes; ++i)
    {
        g.add(0);
    }

    for (int i = 0; i != nodes; ++i)
    {
        g.connect<int>(i, (i + 1) % nodes);
        g.connect<int>((i + 2) % nodes, (i + 5) % nodes);
    }


    while (state.KeepRunning())
    {
        g.nodes<int>();
    }
};

int main(int argc, char** argv)
{
    auto unit = benchmark::kMicrosecond;

    benchmark::RegisterBenchmark("graph_lambda", graph_lambda)->Unit(unit);
    benchmark::RegisterBenchmark("nds_graph", nds_graph)->Unit(unit);

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}
