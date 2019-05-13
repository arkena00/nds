#ifndef INCLUDE_NDS_ENCODER_GRAPH_HPP_NDS
#define INCLUDE_NDS_ENCODER_GRAPH_HPP_NDS

#include <nds/encoder.hpp>

namespace nds
{
    namespace encoders
    {

        template<class IO_system = void>
        class dot
        {
        public:

            template<class Output, class Input, class... Options> // Input concept : graph
            static auto encode(const Input& input)
            {
                // nds::has_concept<Output, concepts::io_system>
                // nds::io_system::write<Output>(data);

                Output o;
                o += "test";

                return o;
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
