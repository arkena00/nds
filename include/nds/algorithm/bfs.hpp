#ifndef INCLUDE_NDS_ALGORITHM_BFS_HPP_NDS
#define INCLUDE_NDS_ALGORITHM_BFS_HPP_NDS

#include <nds/graph.hpp>

#include <iostream>

namespace nds::algorithm
{
    template<class Graph>
    struct bfs
    {
        bfs(Graph& g) : g_{ g }
        {
            //process();

            auto edges_count = g_.count_edges();
            nodes_count = g_.count_nodes();

            output_.reserve(nodes_count);
            visited_.resize(nodes_count);
        }

        void process()
        {
            std::vector<std::vector<int>> n;
            n.resize(nodes_count);

            g_.edges([&n](auto&& e)
            {
                //std::cout << "\n_" << e.source->get();

                n[e.source->get()].push_back(e.target->get());
            });

            int current = 0;

            for (int i = 0; i != nodes_count; ++i)
            {
                //std::cout << "\n_" << "i: " << i << " : { ";

                if (!visited_[i])
                {
                    visited_[i] = true;
                    output_.push_back(i);
                }

                for (auto target : n[i])
                {
                    //std::cout << target << " ";
                    if (!visited_[target])
                    {
                        visited_[target] = true;
                        output_.push_back(target);
                    }
                }
                //std::cout << "}";
            }

            /*std::cout<< "\noutput :\n";
            for (auto item : output)
            {
                std::cout << "_" << item;
            }*/
        }

        Graph& g_;

        int nodes_count;


        std::vector<int> output_;
        std::vector<bool> visited_;
    };
} // nds


namespace nds::algorithm
{
    template<class Graph>
    struct bfs2
    {
        bfs2(Graph& g) : g_{ g }
        {
            edges_count = g_.count_edges();
            nodes_count = g_.count_nodes();

        }

        void process()
        {
            std::vector<int> n;
            n.resize(nodes_count * nodes_count);
            visited_.resize(nodes_count * nodes_count);


            int index = 0;
            g_.edges([&n, &index](auto&& e)
            {
                int index = e.source->get() + e.source->targets_count - e.source->counter++;

                std::cout << "\n_" << e.source->get() << " index: " << index << " source: " << " : " << e.source->targets_count;

                n[index] = e.target->get();

            });

            int current = 0;

            for (int i = 0; i != nodes_count; ++i)
            {
                //std::cout << "\n_" << "i: " << i << " : { ";

                if (!visited_[i])
                {
                    visited_[i] = true;
                }

                /*
                for (auto target : n[i])
                {
                    std::cout << target << " ";
                    if (!visited_[target])
                    {
                        visited_[target] = true;
                        //output_.push_back(target);
                    }
                }*/
                //std::cout << "}";
            }

            /*std::cout<< "\noutput :\n";
            for (auto item : output)
            {
                std::cout << "_" << item;
            }*/
        }

        Graph& g_;

        size_t nodes_count;
        size_t edges_count;

        std::vector<bool> visited_;
    };
} // nds

#endif // INCLUDE_NDS_ALGORITHM_BFS_HPP_NDS

/*
_3 index: 5 source:  : 2
_2 index: 3 source:  : 1
_1 index: 3 source:  : 2
_0 index: 3 source:  : 3
_0 index: 2 source:  : 3
_3 index: 4 source:  : 2
_4 index: 5 source:  : 1
_1 index: 2 source:  : 2
_0 index: 1 source:  : 3
 */