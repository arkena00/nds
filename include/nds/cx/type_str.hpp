#ifndef INCLUDE_NDS_CX_TYPE_STR_HPP_NDS
#define INCLUDE_NDS_CX_TYPE_STR_HPP_NDS

#ifdef __GNUC__
    #include <cxxabi.h>
#endif

namespace nds::cx
{
    template<class T>
    std::string type_str()
    {
        std::string output;
#ifdef __GNUC__
        output = abi::__cxa_demangle(typeid(T).name(), 0, 0, 0);
#else
        output = typeid(T).name();
#endif
        return output;
    }
} // nds::cx

#endif // INCLUDE_NDS_CX_TYPE_STR_HPP_NDS
