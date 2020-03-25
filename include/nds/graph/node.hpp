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
        template<class... Us>
        basic_node(Us&&... us);

        uintptr_t id() const;
        T& get();
        const T& get() const;

    private:
        // node constructor
        template<class... Us>
        basic_node(std::true_type, Us&&... us);

        // default constructor
        template<class... Us>
        basic_node(std::false_type, Us&&... us);

    private:
        T value_;
    };

    class node_ptr_base{};

    template<class T>
    class node_ptr : node_ptr_base
    {
        using nc_type = std::remove_const_t<T>;
        using node_type = std::conditional_t<std::is_const_v<T>, const nds::node<nc_type>*, nds::node<T>*>;

    public:
        using type = T;

    public:
        node_ptr(node_type ptr = nullptr);

        // construct const from non-const
        template<class U, std::enable_if_t<std::is_same_v<T, const U>>...>
        node_ptr(const node_ptr<U>& u);

        explicit operator bool() const;

        auto id() const;
        node_type get() const;
        void reset(nds::node<nc_type>* node = nullptr);
        T& value() const;

        T& operator*() const;
        T* operator->() const;

    private:
        node_type node_;
    };
} // nds

#include <nds/graph/node.tpp>

#endif // INCLUDE_NDS_GRAPH_NODE_HPP_NDS
