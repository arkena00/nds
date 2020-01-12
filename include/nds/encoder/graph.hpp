#ifndef INCLUDE_NDS_ENCODER_GRAPH_HPP_NDS
#define INCLUDE_NDS_ENCODER_GRAPH_HPP_NDS

#include <nds/encoder.hpp>

#include <cassert>
#include <iostream>
#include <sstream>

namespace nds
{
    struct console
    {
        template<class T>
        console& operator<<(T&& v) { std::cout << v; return *this; }
    };

    template<class Input, class... Ts>
    auto append(Input& input, Ts&&... vs)
    {
        (input += ... += vs);
    }

    template<class... Ts>
    auto append(nds::console& input, Ts&&... vs)
    {
        (input << ... << vs);
    }

    namespace encoders
    {

        template<class IO_system = void>
        class dot
        {
        public:
            template<class T>
            static std::string node_name(const T& v)
            {
                return "no_name";
            }

            template<class Output, class Input, class... Options> // Input concept : graph
            static auto encode(const Input& input)
            {
                Output output;
                nds::append(output, "digraph g {\n");

                input.edges([&output](auto&& edge)
                {
                    std::string source_id = std::to_string(reinterpret_cast<intptr_t>(edge.source));
                    std::string source_name = node_name(edge.source->get());
                    std::string source_data = source_id + " [label=\"" + source_name + "\"];\n";

                    std::string target_id = std::to_string(reinterpret_cast<intptr_t>(edge.target));
                    std::string target_name = node_name(edge.target->get());
                    std::string target_data = target_id + " [label=\"" + target_name + "\"];\n";

                    nds::append(output
                    , source_id
                    , " -> "
                    , target_id, ";\n");

                    nds::append(output, source_data, target_data);
                });

                nds::append(output, "}");

                return output;
            }

            template<class Output, class Input, class... Options>
            static auto decode(const Input& input)
            {


            }
        };

        class graph : encoder<graph>
        {
        public:
            using linear_type = std::string;

            template<class T> // concept
            static linear_type encode(const T& t)
            {

            }

            template<class T>
            static T decode(const linear_type& data)
            {

            }
        };
    } // encoders
} // nds

#endif // INCLUDE_NDS_ENCODER_GRAPH_HPP_NDS
