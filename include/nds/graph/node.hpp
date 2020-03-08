#ifndef INCLUDE_NDS_GRAPH_NODE_HPP_NDS
#define INCLUDE_NDS_GRAPH_NODE_HPP_NDS

#include <utility>

namespace nds
{
    class node_base{};

    template<class T>
    class node : node_base
    {
    public:
        using base_type = T;

        virtual ~node() = default;
        virtual uintptr_t id() const = 0;
        virtual T& get() = 0;
    };

    template<class T, class Base = T>
    class basic_node : public node<Base>
    {
    public:
        using type = T;

        template<class... Us>
        basic_node(Us&&... us) : basic_node( typename std::is_constructible<T, basic_node<T>*, Us...>::type{}, std::forward<Us>(us)...) {}

        uintptr_t id() const { return reinterpret_cast<uintptr_t>(&value_); }
        T& get() { return value_; }

    private:
        // node constructor
        template<class... Us>
        basic_node(std::true_type, Us&&... us) : value_{ this, std::forward<Us>(us)... } {}

        // default constructor
        template<class... Us>
        basic_node(std::false_type, Us&&... us) : value_{ std::forward<Us>(us)... } {}

    private:
        T value_;
    };

    template<class T>
    class node_ptr
    {
    public:
        node_ptr(nds::node<T>* ptr = nullptr)
            : node_{ ptr }
        {}

        auto id() const { return node_->id(); }

        operator bool() { return node_ != nullptr; }
        T* operator->() { return &node_->get(); }

    private:
        nds::node<T>* node_;
    };
} // nds

#endif // INCLUDE_NDS_GRAPH_NODE_HPP_NDS
