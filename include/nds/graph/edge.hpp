#ifndef INCLUDE_NDS_GRAPH_EDGE_HPP_NDS
#define INCLUDE_NDS_GRAPH_EDGE_HPP_NDS

#include <nds/graph/node.hpp>

namespace nds
{
    template<class...>
    class edge;

    template<class Source, class Target>
    class edge<Source, Target>
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

    template<class Type>
    class edge<Type>
    {
    public:
        edge(Type&& type)
            : type{ std::forward(type) }
        {}

        Type type;
    };
} // nds


#endif // INCLUDE_NDS_GRAPH_EDGE_HPP_NDS