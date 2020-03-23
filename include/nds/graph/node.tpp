namespace nds
{
    template<class T, class Base>
    template<class... Us>
    basic_node<T, Base>::basic_node(Us&&... us)
        : basic_node( typename std::is_constructible<T, basic_node<T>*, Us...>::type{}, std::forward<Us>(us)...)
    {}

    // node constructor
    template<class T, class Base>
    template<class... Us>
    basic_node<T, Base>::basic_node(std::true_type, Us&&... us)
        : value_{ this , std::forward<Us>(us)... }
    {}

    // default constructor
    template<class T, class Base>
    template<class... Us>
    basic_node<T, Base>::basic_node(std::false_type, Us&&... us)
        : value_{ std::forward<Us>(us)... }
    {}

    template<class T, class Base>
    uintptr_t basic_node<T, Base>::id() const
    {
        return reinterpret_cast<uintptr_t>(& value_);
    }

    template<class T, class Base>
    T& basic_node<T, Base>::get()
    {
        return value_;
    }

    template<class T, class Base>
    const T& basic_node<T, Base>::get() const
    {
        return value_;
    }

    //

    template<class T>
    node_ptr<T>::node_ptr(node_type ptr)
        : node_{ ptr }
    {}

    // construct const from non-const
    template<class T>
    template<class U, std::enable_if_t<std::is_same_v<T, const U>>...>
    node_ptr<T>::node_ptr(const node_ptr<U>& u)
        : node_{ u.get() }
    {}

    template<class T>
    node_ptr<T>::operator bool() const
    {
        return node_ != nullptr;
    }

    template<class T>
    auto node_ptr<T>::id() const
    {
        return node_->id();
    }

    template<class T>
    typename node_ptr<T>::node_type node_ptr<T>::get() const
    {
        return node_;
    }

    template<class T>
    void node_ptr<T>::reset(nds::node<nc_type>* node)
    {
        node_ = node;
    }

    template<class T>
    T& node_ptr<T>::operator*() const
    {
        return node_->get();
    }

    template<class T>
    T *node_ptr<T>::operator->() const
    {
        return &node_->get();
    }
} // nds