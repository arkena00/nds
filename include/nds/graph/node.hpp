#ifndef INCLUDE_NDS_GRAPH_NODE_HPP_NDS
#define INCLUDE_NDS_GRAPH_NODE_HPP_NDS

namespace nds
{
    template<class T>
    class node
    {
    public:
        node(T&& v)
            : value_{ std::move(v) }
        {}

        auto get() { return value_; }

    private:
        T value_;
    };
} // nds

#endif // INCLUDE_NDS_GRAPH_NODE_HPP_NDS
