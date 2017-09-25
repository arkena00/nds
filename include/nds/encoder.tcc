namespace nds
{
    // encode for Encoder class
    template<class Encoder>
    template<class T>
    trait::linear_type<Encoder, T> encoder<Encoder>::encode(const T& in)
    {
        return Encoder::encode(in);
    }

    // encode T with T::linear_type
    /*
    template<class Encoder>
    template<class T>
    typename T::linear_type encode(const T& in)
    {
        return encode<T::linear_type, encoders::global>(in);
    }*/

    // decode for Encoder class
    template<class Encoder>
    template<class T>
    T encoder<Encoder>::decode(const typename trait::linear_type<Encoder, T>& in)
    {
        return Encoder::template decode<T>(in);
    }
} // nds
