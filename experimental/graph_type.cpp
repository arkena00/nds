#include <tuple>
#include <iostream>
#include <vector>

// index_of
struct cx_err_type_not_found;

template<class T, class Container>
struct index_of;

template<class T, template<class...> class Container>
struct index_of<T, Container<>>
{
    constexpr static auto value = -1000000000;
};

template<class T, template<class...> class Container, class... Ts>
struct index_of<T, Container<T, Ts...>>
{
    constexpr static auto value = 0;
};

template<class T, template<class...> class Container, class T_test, class... Ts>
struct index_of<T, Container<T_test, Ts...>>
{
    constexpr static auto value = 1 + index_of<T, Container<Ts...>>::value;
};

template<class...> struct pack;


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


template<class Source, class Target>
struct edge
{
    using source_type = Source;
    using target_type = Target;

    edge(Source& s, Target& t) : source{s}, target{t} {}

    Source& source;
    Target& target;
};






template<class Edges, class... Ts>
struct graph
{
    using storage_type = std::tuple<std::vector<node<Ts>>...>;

    storage_type data_;
    Edges edges_;

    template<class U>
    node<U>& add(U u)
    {
        node<U> target_node = node<U>{ std::move(u) };

        constexpr int index = index_of<std::vector<node<U>>, storage_type>::value;
        std::get<index>(data_).emplace_back(target_node);

        node<U>& last_node = std::get<index>(data_).back();

        return last_node;
    }

    template<class... Us>
    auto& nodes()
    {
        auto loop_input_type = [this](auto&& nt)
        {
            using input_node_type = node<std::decay_t<decltype(nt)>>;

            auto loop_graph_type = [](auto&& vector)
            {
                using graph_node_type = typename std::decay_t<decltype(vector)>::value_type; // node<T>
                if constexpr (std::is_same_v<input_node_type, graph_node_type>)
                {
                    for (auto node : vector) std::cout << "\n_" << node.get();
                }
            };

            std::apply([&](auto&&... vectors) { (loop_graph_type(vectors), ...); }, data_);
        };

        (loop_input_type(Us{}), ...);

        return data_;
    }


    template<class Source, class Target>
    void connect(Source& s, Target& t)
    {
        // check edges
        constexpr int index = index_of<std::vector<edge<Source, Target>>, Edges>::value;
        static_assert(index >= 0, "connection between U and V not allowed");

        std::get<index>(edges_).emplace_back(edge<Source, Target>{s, t});
    }


    template<class Source>
    void targets(Source& source)
    {
        auto loop_graph_edge = [&](auto&& vector)
        {
          using graph_edge_type = typename std::decay_t<decltype(vector)>::value_type::source_type; // node<T>
          if constexpr (std::is_same_v<graph_edge_type, Source>)
          {
              for (auto node : vector) if (source.get() == node.source.get()) std::cout << "\n_edge " << node.source.get() << " - " << node.target.get();
          }
        };

        std::apply([&](auto&&... vectors) { (loop_graph_edge(vectors), ...); }, edges_);

    }

};

int main()
{
    using Edges = std::tuple<
    std::vector<edge<node<int>, node<char>>>,
    std::vector<edge<node<int>, node<int>>>
    >;

    graph<Edges, int, char> g;

    auto n1 = g.add<int>(12);
    auto n2 = g.add<int>(15);
    auto n3 = g.add<char>(97);
    auto n4 = g.add<char>(98);

    g.connect(n1, n4); // int char
    g.connect(n1, n2); // int int
    g.connect(n2, n3); // int int
    // g.connect(n3, n4); // char char // error

    g.nodes<int, char>();

    g.targets(n1);
}