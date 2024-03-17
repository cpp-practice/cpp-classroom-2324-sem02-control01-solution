#include "maslenica.hpp"

int main() {
    const control_01::blin b {};
    const control_01::ikra i {};

    auto wrong = (b + b + i) + i;
    (void)wrong;
}
