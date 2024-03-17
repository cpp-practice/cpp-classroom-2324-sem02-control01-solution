#include "maslenica.hpp"

#include <type_traits>

template<class X, class Y, class = void> struct can_add : std::false_type {};
template<class X, class Y> struct can_add<X, Y, std::void_t<decltype((std::declval<X>() + std::declval<Y>()))>> : std::true_type {};

template<class X, class Y> constexpr bool can_add_v = can_add<X, Y>::value;

namespace cc = control_01;
using B = cc::blin;
using I = cc::ikra;

template<class... Ss> using T = cc::tarelka<Ss...>;


// складываем два слоя
static_assert(std::is_same_v<decltype(B{} + B{}), T<B,B>>);
static_assert(std::is_same_v<decltype(B{} + I{}), T<B,I>>);
static_assert(std::is_same_v<decltype(I{} + B{}), T<I,B>>);
static_assert(!can_add_v<I,I>);

// складываем слой с тарелкой
static_assert(std::is_same_v<decltype(B{} + T<B,B,I,B,B>{}), T<B,B,B,I,B,B>>);
static_assert(std::is_same_v<decltype(I{} + T<B,B,I,B,B>{}), T<I,B,B,I,B,B>>);
static_assert(std::is_same_v<decltype(B{} + T<I,B,I,B,B>{}), T<B,I,B,I,B,B>>);
static_assert(!can_add_v<I, T<I,B,I,B,B>>);

static_assert(std::is_same_v<decltype(T<B,B,I,B,B>{} + B{}), T<B,B,I,B,B,B>>);
static_assert(std::is_same_v<decltype(T<B,B,I,B,B>{} + I{}), T<B,B,I,B,B,I>>);
static_assert(std::is_same_v<decltype(T<B,B,I,B,I>{} + B{}), T<B,B,I,B,I,B>>);
static_assert(!can_add_v<T<B,B,I,B,I>, I>);

// складываем две тарелки
static_assert(std::is_same_v<decltype(T<I,B,B>{} + T<B,B,I>{}), T<I,B,B,B,B,I>>);
static_assert(std::is_same_v<decltype(T<I,B,B>{} + T<I,B,I>{}), T<I,B,B,I,B,I>>);
static_assert(std::is_same_v<decltype(T<I,B,I>{} + T<B,B,I>{}), T<I,B,I,B,B,I>>);
static_assert(!can_add_v<T<B,B,I>, T<I,B,B>>);

int main() {}
