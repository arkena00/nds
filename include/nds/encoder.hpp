#ifndef NDS_ENCODER_H_NDS
#define NDS_ENCODER_H_NDS

#include <nds/trait.hpp>

namespace nds
{
    namespace trait
    {
        template<class Encoder, class> struct linear_type_impl { using type = typename Encoder::linear_type; };
        template<class Encoder, class T> using linear_type = typename linear_type_impl<Encoder, T>::type;
    } //trait

    namespace encoders { class global{}; }

    template<class Encoder = encoders::global>
    class encoder
    {
    public:
        // encode
        template<class T>
        static trait::linear_type<Encoder, T> encode(const T& in);

        // decode
        template<class T>
        static T decode(const typename trait::linear_type<Encoder, T>& in);

        // encode T with T::Linear_Type
        //template<class T>
        //static typename T::linear_type encode(const T& in);
    };

    template<>
    struct encoder<encoders::global>
    {
        // encode
        template<class Linear_Type, class Scope = encoders::global, class T>
        static Linear_Type encode(const T& in);

        // decode
        template<class T, class Scope = encoders::global, class Linear_Type>
        static T decode(const Linear_Type& in);

        template<class Linear_Type, class T>
        static void decode(const Linear_Type& in, T& out);
    };

    //// GLOBAL
    // encode
    /*
    template<class Linear_Type, class Scope = encoders::global, class T>
    inline Linear_Type encode(const T& in)
    {
        nds::encoder<>::encode<Linear_Type, Scope>(in);
    }

    // decode
    template<class T, class Class_Scope, class Linear_Type>
    T decode(const Linear_Type& in);

    template<class Linear_Type, class T>
    inline void decode(const Linear_Type& in, T& out)
    {
        nds::encoder<>::decode(in, out);
    }*/

} // nds

#include "encoder.tpp"

#endif // NDS_ENCODER_H_NDS