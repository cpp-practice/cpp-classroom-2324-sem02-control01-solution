#include "zip.hpp"
#include "zip.hpp"

#include <cassert>
#include <vector>

#include "../simple_test.h"


TEST(zip, test_many_containers_structured_binding) {
    std::vector<int> v{1, 2, 3};

    size_t i = 0;
    for (auto&&[x, y, z]: control_01::zip(v, v, v)) {
        assert(x == v[i]);
        assert(y == v[i]);
        assert(z == v[i]);
        i++;
    }
}

TESTING_MAIN()
