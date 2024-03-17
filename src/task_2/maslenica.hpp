#pragma once

namespace control_01 {

    struct blin {};
    struct ikra {};

    template<class Sloy1, class... Sloi> struct tarelka {};

    // Подзадача 1
    template<class Tarelka> constexpr bool pravilno_v = false;  // TODO!

    // Подзадача 2
    template<class Sleva, class Sprava> auto operator + (Sleva, Sprava) { }  // TODO!
    // Sleva, Sprava - blin, ikra, tarelka<.....>

}  // namespace control_01
