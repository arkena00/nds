#ifndef INCLUDE_NDS_GRAPH_LEMON_HPP_NDS
#define INCLUDE_NDS_GRAPH_LEMON_HPP_NDS

#include <nds/graph.hpp>

#include <lemon/list_graph.h>

namespace nds
{
    namespace lemon
    {
        template<class T>
        class node_ptr : node_ptr_base
        {
            using nc_type = std::remove_const_t<T>;
            using node_type = std::conditional_t<std::is_const_v<T>, const nc_type*, T*>;

        public:
            using type = T;

        public:
            explicit node_ptr(::lemon::ListDigraph::Node lnode, node_type ptr = nullptr)
                : lnode_{ lnode }
                , node_{ ptr }
            {}

            node_ptr()
                : lnode_{}
                , node_{ nullptr }
            {}

            const auto& id() const { return lnode_; }

            node_type get() const { return node_; }

            operator bool() const { return node_ != nullptr; }
            bool operator==(std::nullptr_t) const { return node_ == nullptr; }
            bool operator==(const node_ptr<T>& other) const { return node_ == other.node_; }
            bool operator!=(std::nullptr_t) const { return node_ != nullptr; }
            bool operator!=(const node_ptr<T>& other) const { return node_ != other.node_; }


            T& operator*() const { return *node_; }
            T* operator->() const { return node_; }

        private:
            ::lemon::ListDigraph::Node lnode_;
            node_type node_;
        };

        //

        template<class Source, class Target>
        class edge
        {
        public:
            using source_type = Source;
            using target_type = Target;

            edge(Source s, Target t)
                : source{ std::move(s) }
                , target{ std::move(t) }
            {}

            Source source;
            Target target;
        };



    } // lemon


    //


    namespace algorithm { class graph; }

    namespace internal
    {
        template<class... Ts, class... Es, class... Us, class... Vs>
        class graph<nds::graph_nodes<Ts...>, nds::graph_edges<Es...>, nds::graph_rules<nds::edge<Us, Vs>...>, graph_storages::lemon>
        {
            friend struct nds::algorithm::graph;

        public:
            template<class U> const auto& init() { return graph_; }

            template<class T>
            using node_ptr = nds::node_ptr<T>;
            template<class T>
            using node_type = T;

            template<class T>
            using internal_node_ptr = T*;

            using nodes_type = nds::graph_nodes<Ts...>;
            using edges_type = nds::graph_edges<Es...>;

            using node_container_type = std::tuple<::lemon::ListDigraph::NodeMap<internal_node_ptr<Ts>>...>;
            using edge_container_type = std::tuple<::lemon::ListDigraph::ArcMap<internal_node_ptr<Es>>...>;

            graph()
                : graph_{}
                , nodes_{ init<Ts>()... }
                , edges_{ init<Es>()... }
            {}

            template<class B = void, class T>
            auto add(T v)
            {
                // Base = T if Base is not specified
                using Base = std::conditional_t<std::is_same_v<B, void>, T, B>;

                constexpr int node_type_index = cx::index_of<::lemon::ListDigraph::NodeMap<internal_node_ptr<Base>>, node_container_type>::value;

                auto last_node_id = graph_.addNode();

                std::unique_ptr<T> ptr = std::make_unique<T>(std::move(v));
                auto last_node = ptr.release();

                std::get<node_type_index>(nodes_)[last_node_id] = last_node;

                return lemon::node_ptr<Base>(last_node_id, last_node);
            }

            template<class B = void, class T, class Source>
            auto add(T v, lemon::node_ptr<Source> source)
            {
                auto last_node = add(std::move(v));
                add_arc(source, last_node);
                return last_node;
            }

            template<class Edge_type, class Source_type, class Target_type>
            void add_arc(lemon::node_ptr<Source_type> source, lemon::node_ptr<Target_type> target, Edge_type&& edge)
            {
                auto last_arc_id =graph_.addArc(source.id(), target.id());

                std::unique_ptr<Edge_type> ptr = std::make_unique<Edge_type>(std::move(edge));
                auto e = ptr.release();

                constexpr int edge_index = cx::index_of<::lemon::ListDigraph::ArcMap<internal_node_ptr<Edge_type>>, edge_container_type>::value;
                std::get<edge_index>(edges_)[last_arc_id] = e;
            }

            template<class Source_type, class Target_type>
            void add_arc(lemon::node_ptr<Source_type> source, lemon::node_ptr<Target_type> target)
            {
                auto last_arc_id =graph_.addArc(source.id(), target.id());
            }

            template<class Edge_type, class Source_type, class F>
            void targets(lemon::node_ptr<Source_type> source_, F&& f) const
            {
                if (!source_) return;
                using Source = std::remove_const_t<Source_type>;
                lemon::node_ptr<Source> source{ source_.id(), const_cast<node_type<Source>*>(source_.get()) };

                nds::cx::for_each<edges_type>([&, this](auto&& et)
                {
                    using graph_edge_type = typename std::decay_t<decltype(et)>::type;
                    constexpr int edge_index = cx::index_of<graph_edge_type, edges_type>::value;

                     if constexpr (std::is_same_v<Edge_type, graph_edge_type>)
                     {
                         for (::lemon::ListDigraph::OutArcIt i(graph_, source.id()); i != ::lemon::INVALID; ++i)
                            {
                                auto node_data = std::get<0>(nodes_)[graph_.baseNode(i)];
                                auto edge_data = std::get<edge_index>(edges_)[i];
                                if (edge_data)
                                {
                                    nds::lemon::node_ptr<std::remove_pointer_t<decltype(node_data)>> ptr(graph_.baseNode(i), node_data);
                                    f(std::move(ptr), edge_data);
                                }
                            }
                     }
                });
            }

            template<class Source_type, class F>
            void targets(lemon::node_ptr<Source_type> source_, F&& f) const
            {
                if (!source_) return;
                using Source = std::remove_const_t<Source_type>;
                lemon::node_ptr<Source> source{ source_.id(), const_cast<node_type<Source>*>(source_.get()) };

                for (::lemon::ListDigraph::OutArcIt i(graph_, source.id()); i != ::lemon::INVALID; ++i)
                {
                    auto node_data = std::get<0>(nodes_)[graph_.baseNode(i)];
                    nds::lemon::node_ptr<std::remove_pointer_t<decltype(node_data)>> ptr(graph_.baseNode(i), node_data);
                    f(std::move(ptr));
                }
            }

            template<class F>
            void edges(F&& f) const
            {
                auto loop_edge_type = [&f, this](auto&& et)
                {
                    //using graph_edge_type = typename std::decay_t<decltype(et)>::type;
                    //if constexpr (std::is_same_v<input_edge_type, graph_edge_type>)
                    {
                        //for (auto&& edge : vector) f(edge);

                        for (::lemon::ListDigraph::ArcIt i(graph_); i != ::lemon::INVALID; ++i)
                        {
                            auto source_node_data = std::get<0>(nodes_)[graph_.source(i)];
                            nds::lemon::node_ptr<std::remove_pointer_t<decltype(source_node_data)>> source_ptr(graph_.source(i), source_node_data);
                            auto target_node_data = std::get<0>(nodes_)[graph_.target(i)];
                            nds::lemon::node_ptr<std::remove_pointer_t<decltype(target_node_data)>> target_ptr(graph_.target(i), target_node_data);

                            nds::lemon::edge e{ source_ptr, target_ptr };
                            f(e);
                        }
                    }
                };

                std::apply([&, this](auto&&... maps) { (loop_edge_type(maps), ...); }, edges_);
            }

            template<class B = void, class T = B, class... Args>
            auto emplace(Args&&... args)
            {
                using T0 = typename internal::argn<0, Ts...>::type;
                using Type = std::conditional_t<std::is_same_v<T, void>, T0, T>;
                using Base = std::conditional_t<std::is_same_v<B, void>, Type, B>;

                constexpr int node_type_index = cx::index_of<::lemon::ListDigraph::NodeMap<internal_node_ptr<Base>>, node_container_type>::value;

                auto last_node_id = graph_.addNode();

                auto ptr = std::make_unique<Base>( std::forward<Args>(args)... );
                auto last_node = ptr.release();

                std::get<node_type_index>(nodes_)[last_node_id] = last_node;

                return lemon::node_ptr<Base>(last_node_id, last_node);
            }

        private:
            ::lemon::ListDigraph graph_;

            node_container_type nodes_;
            edge_container_type edges_;
        };

    } // internal

    template<class... Ts>
    using graph = typename internal::graph_trait<Ts...>::type;
} // nds

#endif // INCLUDE_NDS_GRAPH_LEMON_HPP_NDS
