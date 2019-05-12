#ifndef INCLUDE_NDS_GRAPH_EDGE_HPP_NDS
#define INCLUDE_NDS_GRAPH_EDGE_HPP_NDS
namespace nds {struct access;}
namespace nds
{
    template<class Source, class Target>
    class edge
    {
    public:
        using source_type = Source;
        using target_type = Target;

        edge(Source* s, Target* t) : source{ s }, target{ t } {}

        Source* source;
        Target* target;
    };
} // nds

#endif // INCLUDE_NDS_GRAPH_EDGE_HPP_NDS
