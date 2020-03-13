#ifndef INCLUDE_NDS_GRAPH_NODE_HPP_NDS
#define INCLUDE_NDS_GRAPH_NODE_HPP_NDS

#include <cstdint>
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
        virtual const T& get() const = 0;
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
        const T& get() const { return value_; }

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
        using nc_type = std::remove_const_t<T>;
        using node_type = std::conditional_t<std::is_const_v<T>, const nds::node<nc_type>*, nds::node<T>*>;

    public:
        node_ptr(node_type ptr = nullptr)
            : node_{ ptr }
        {}

        // construct const from non-const
        template<class U, std::enable_if_t<std::is_same_v<T, const U>>...>
        node_ptr(const node_ptr<U>& u) : node_{ u.get() } {  }

        operator bool() const { return node_ != nullptr; }

        auto id() const { return node_->id(); }
        node_type get() const { return node_; }
        void reset(nds::node<nc_type>* node = nullptr) {  node_ = node; }

        T& operator*() const { return node_->get(); }
        T* operator->() const { return &node_->get(); }

    private:
        node_type node_;
    };
} // nds

#endif // INCLUDE_NDS_GRAPH_NODE_HPP_NDS
