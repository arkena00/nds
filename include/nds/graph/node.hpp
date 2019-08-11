#ifndef INCLUDE_NDS_GRAPH_NODE_HPP_NDS
#define INCLUDE_NDS_GRAPH_NODE_HPP_NDS

#include <utility>

namespace nds
{
    template<class T>
    class node
    {
    public:
        virtual unsigned int id() const = 0;
        virtual T& get() = 0;
    };

    template<class T, class Base = T>
    class basic_node : public node<Base>
    {
    public:
        template<class... Us>
        basic_node(Us&&... us) : value_{ std::forward<Us>(us)... } {}

        unsigned int id() const { return reinterpret_cast<uintptr_t>(&value_); }
        T& get() { return value_; }

    private:
        T value_;
    };
} // nds

#endif // INCLUDE_NDS_GRAPH_NODE_HPP_NDS
