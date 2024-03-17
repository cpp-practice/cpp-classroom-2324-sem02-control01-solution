#include "maslenica.hpp"

int main() {
    const control_01::blin b {};
    const control_01::ikra i {};

    auto wrong = i + (i + b + b);
    (void)wrong;
}
