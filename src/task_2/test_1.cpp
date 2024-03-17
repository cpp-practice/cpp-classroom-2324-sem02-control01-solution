#include "maslenica.hpp"

namespace cc = control_01;

static_assert(cc::pravilno_v<cc::tarelka<cc::blin>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::ikra>>);

static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::blin>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::ikra>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::ikra, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::ikra, cc::ikra>>);

static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::blin, cc::blin>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::blin, cc::ikra>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::ikra, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::blin, cc::ikra, cc::ikra>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::ikra, cc::blin, cc::blin>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::ikra, cc::blin, cc::ikra>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::ikra, cc::ikra, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::ikra, cc::ikra, cc::ikra>>);

static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::blin, cc::blin, cc::blin>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::blin, cc::blin, cc::ikra>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::blin, cc::ikra, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::blin, cc::blin, cc::ikra, cc::ikra>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::ikra, cc::blin, cc::blin>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::ikra, cc::blin, cc::ikra>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::blin, cc::ikra, cc::ikra, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::blin, cc::ikra, cc::ikra, cc::ikra>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::ikra, cc::blin, cc::blin, cc::blin>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::ikra, cc::blin, cc::blin, cc::ikra>>);
static_assert(cc::pravilno_v<cc::tarelka<cc::ikra, cc::blin, cc::ikra, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::ikra, cc::blin, cc::ikra, cc::ikra>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::ikra, cc::ikra, cc::blin, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::ikra, cc::ikra, cc::blin, cc::ikra>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::ikra, cc::ikra, cc::ikra, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::ikra, cc::ikra, cc::ikra, cc::ikra>>);

static_assert(cc::pravilno_v<cc::tarelka<cc::blin, cc::blin, cc::ikra, cc::blin, cc::ikra, cc::blin>>);
static_assert(!cc::pravilno_v<cc::tarelka<cc::blin, cc::ikra, cc::ikra, cc::blin, cc::ikra, cc::blin>>);

int main() {}
