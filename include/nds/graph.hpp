#include <iostream>
#include <variant>
#include <vector>

namespace nds
{
    template<class...> struct pack;

    template<class Source, class Target>
    struct edge
    {
        edge(Source* s, Target* t) : source{s}, target{t} {}

        Source* source;
        Target* target;
    };

    struct node_base
    {
        int id = 0;
    };

    template<class T>
    class node : public node_base
    {
        T value_;

    public:
        node(T&& v)
            : value_{ std::move(v) }
        {}

        auto get() { return value_; }
    };

    template<class T, class T2>
    struct graph
    {
        using types = nds::pack<T, T2>;

        template<class U>
        node<U>* add(U target, node_base* source = nullptr)
        {
            node<U> target_node = node<U>{ std::move(target) };
            nodes_.push_back(std::make_unique<node<U>>(std::move(target_node)));
            node_base* last_node = nodes_.back().get();
            //edges_.emplace_back(nds::edge<node_base, node_base>{ source, last_node });
            return static_cast<node<U>*>(last_node);
        }

        template<class Source, class Target>
        void connect(Source s, Target t)
        {
            edges_.push_back(nds::edge<Source, Target>(s, t));
        }

        const auto& nodes()
        {
            return nodes_;
        }

        template<class T>
        auto targets(node<T>* source = nullptr)
        {
            std::vector<node<T>*> res;
/*
            for (const nds::edge<node<T>, node<T>>& edge : edges_)
            {
                std::cout << "\n_" << edge.source << " " << edge.target;
                if (edge.source == source) res.push_back(edge.target);
            }*/

            return res;
        }


        auto root() { return root_; }

        node<T>* root_ = nullptr;
        std::tuple<>
        std::tuple<std::vector<std::unique_ptr<node<T>>>> nodes_;
        std::vector<nds::edge<node<T>, node<T>>> edges_;
    };
} // nds