#include "zip.hpp"
#include "zip.hpp"

#include <iterator>
#include <vector>
#include <string>

#include "../simple_test.h"


TEST(zip, empty) {
    std::vector<int> v;
    std::string s;

    control_01::zip empty_zip(v, s);

    EXPECT_EQ(empty_zip.end(), empty_zip.begin());
}

template<class C1, class C2>
void check_simple(C1 &c1, C2 &c2, control_01::zip <C1, C2> &zipper) {
    typename control_01::zip<C1, C2>::iterator iter = zipper.begin();
    size_t i = 0;
    while (iter != zipper.end()) {
        EXPECT_EQ(c1[i], (*iter).template get<0>());
        EXPECT_EQ(c2[i], iter->template get<1>());
        ++iter;
        ++i;
    }
    EXPECT_EQ(std::min(c1.size(), c2.size()), i);
}

TEST(zip, basic) {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    control_01::zip zipper(v, s);
    check_simple(v, s, zipper);
}


TEST(zip, make)  {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    auto zipper = control_01::make_zip(v, s);
    check_simple(v, s, zipper);
}

TEST(zip, can_change_through) {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    control_01::zip zipper(v, s);
    std::next(zipper.begin())->get<0>() = 0;
    std::next(zipper.begin(), 2)->get<1>() = 'L';
    EXPECT_EQ('L', s[2]);
    EXPECT_EQ(0, v[1]);
    check_simple(v, s, zipper);
}

TEST(zip, doesnt_save_state) {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    control_01::zip zipper(v, s);
    v.clear();
    EXPECT_EQ(zipper.end(), zipper.begin());
}

TEST(zip, arrow_op) {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    control_01::zip zipper(v, s);
    auto it = std::next(zipper.begin());
    it->get<0>();

    v.clear();
    EXPECT_EQ(zipper.end(), zipper.begin());
}

template<class... C>
[[nodiscard]] size_t check_simple(control_01::zip<C...> &&zipper, const C &... containers) {
    typename control_01::zip<C...>::iterator iter = zipper.begin();
    size_t i = 0;
    while (iter != zipper.end()) {
        EXPECT_EQ(std::make_tuple(containers.at(i)...), *iter);
        ++iter;
        ++i;
    }
    return i;
}

TEST(zip, many_containers) {
    std::vector<int> v{1, 2, 3};
    std::string s = "hello";

    size_t sz = check_simple(control_01::zip(v, s, v), v, s, v);
    EXPECT_EQ(3, sz);
}


TESTING_MAIN()
