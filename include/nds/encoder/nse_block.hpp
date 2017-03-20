#ifndef NDS_ENCODER_NSE_BLOCK_H_NDS
#define NDS_ENCODER_NSE_BLOCK_H_NDS

#include <nds/encoder.hpp>

namespace nds
{
    namespace encoders
    {
        class nse_block : encoder<nse_block>
        {
        public:
            using linear_type = std::string;

            template<class T>
            static linear_type encode(T& t)
            {


                return linear_type{};
            }
            static linear_type encode(const char* t) { return t; }

            template<class T>
            static T decode(const linear_type& data)
            {
                T res;
                return res;
            }
        };
    } // encoders
} // nds

#endif // NDS_ENCODER_NSE_BLOCK_H_NDS
