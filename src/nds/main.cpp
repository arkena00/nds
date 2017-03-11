#include <iostream>
#include <nds/encoder/boost_text.hpp>

using namespace std;

int main()
{
    zeta s;
    nds::encoder<nds::encoders::boost_text>::encode(s);

    return 0;
}
