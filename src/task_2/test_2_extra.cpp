
#include "maslenica.hpp"

#include <type_traits>

template<class Expected, class Arg> void check(Arg) {
    static_assert(std::is_same_v<Expected, Arg>);
}

using B = control_01::blin;
using I = control_01::ikra;
template<class...Ss> using T = control_01::tarelka<Ss...>;

int main() {
    B b {};
    I i {};

    // left assoc
    check<T<I,B,B,I,B,I,B>>(i + b + b + i + b + i + b);

    // mixed
    check<T<I,B,B,I,B,I,B>>((i + b) + (b + i + b) + (i + b));

    // primitive
    check<T<B,B>>(b + b);
    check<T<B,I>>(b + i);
    check<T<I,B>>(i + b);

    // right assoc
    check<T<I,B,B,I,B,I,B>>(i + (b + (b + (i + (b + (i + b))))));
}