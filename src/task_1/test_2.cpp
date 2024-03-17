#include "zip.hpp"
#include "zip.hpp"

#include <cassert>
#include <vector>
#include <string>

#include "../simple_test.h"


TEST(zip, const_container) {
    const std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    control_01::zip zipper(v, s);
    static_assert(!std::is_assignable_v < decltype(std::next(zipper.begin())->get<0>()), int > );
    static_assert(!std::is_assignable_v < decltype(std::next(zipper.begin())->get<1>()), char > );
}

TEST(zip, const_zipper) {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    const control_01::zip zipper(v, s);
    static_assert(!std::is_assignable_v < decltype(std::next(zipper.begin())->get<0>()), int > );
    static_assert(!std::is_assignable_v < decltype(std::next(zipper.begin())->get<1>()), char > );
}

TEST(zip, iterator_decrement) {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    control_01::zip zipper(v, s);
    EXPECT_EQ(zipper.begin(), --(std::next(zipper.begin())));
}

TEST(zip, reverse_iterators) {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    control_01::zip zipper(v, s);
    size_t idx = 0;
    for (auto it = zipper.rbegin(); it != zipper.rend(); ++it) {
        EXPECT_EQ(v[2 - idx], it->get<0>());
        EXPECT_EQ(s[4 - idx], it->get<1>());
        idx++;
    }
}


TESTING_MAIN()
