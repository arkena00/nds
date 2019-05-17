#ifndef INCLUDE_NDS_GRAPH_NODE_HPP_NDS
#define INCLUDE_NDS_GRAPH_NODE_HPP_NDS

#include <utility>

namespace nds
{
    template<class T>
    class node
    {
    public:
        node(T&& v)
            : value_{ std::move(v) }
        {}

        T& get() { return value_; }

    private:
        T value_;

    public:
        int targets_count = 0;
        int counter = 0;

    };
} // nds

#endif // INCLUDE_NDS_GRAPH_NODE_HPP_NDS
