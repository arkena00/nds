#ifndef NDS_ENCODER_H_NDS
#define NDS_ENCODER_H_NDS

/*! usage
 * void nds::encoder<>::encode(input);
 * Return_type nds::encoder<>::encode<Return_type>(input);
 */

#include <nds/trait.hpp>

namespace nds
{
    namespace trait
    {
        template<class Encoder, class> struct delay_type_impl { using type = typename Encoder::linear_type; };
        template<class Encoder, class T> using delay_type = typename delay_type_impl<Encoder, T>::type;
    } //trait

    namespace encoders { class global{}; }

    template<class Encoder = encoders::global>
    class encoder
    {
    public:
        // encode
        template<class T>
        static trait::delay_type<Encoder, T> encode(const T& in);

        //template<class Scope = encoders::global, class T>
        //static void encode(T& in);

        // decode
        template<class T>
        static T decode(const typename trait::delay_type<Encoder, T>& in);

        // encode T with T::linear_type
        //template<class T>
        //static typename T::linear_type encode(const T& in);
    };

    template<>
    class encoder<encoders::global>
    {
    public:
        // encode
        template<class linear_type, class Scope = encoders::global, class T>
        static linear_type encode(const T& in);

        // encode directly the ref value
		template<class Scope = encoders::global, class T>
        static void encode_ref(T& in);

        // decode
        template<class T, class Scope = encoders::global, class linear_type>
        static T decode(const linear_type& in);

        template<class linear_type, class T>
        static void decode(const linear_type& in, T& out);

		template<class T>
        static void decode(T& t);
    };

    //// GLOBAL
    // encode
    /*
    template<class linear_type, class Scope = encoders::global, class T>
    inline linear_type encode(const T& in)
    {
        nds::encoder<>::encode<linear_type, Scope>(in);
    }

    // decode
    template<class T, class Class_Scope, class linear_type>
    T decode(const linear_type& in);

    template<class linear_type, class T>
    inline void decode(const linear_type& in, T& out)
    {
        nds::encoder<>::decode(in, out);
    }*/

} // nds

#include "encoder.tpp"

#endif // NDS_ENCODER_H_NDS