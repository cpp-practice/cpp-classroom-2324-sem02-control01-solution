#pragma once

#include <tuple>
#include <algorithm>

namespace control_01 {
    template<typename ... Args>
    class ZipTuple : public std::tuple<Args&...> {
    public:
        explicit ZipTuple(Args& ...args) : std::tuple<Args&...>(args...) {}

        template<std::size_t N>
        decltype(auto) get() {
            return std::get<N>(static_cast<std::tuple<Args&...>&>(*this));
        }

        ZipTuple* operator->() {
            return this;
        }

        const ZipTuple* operator->() const {
            return this;
        }
    };


    template<typename... Iterators>
    class ZipIterator {
    public:
        explicit ZipIterator(Iterators... iterators) : iterators_tuple_(iterators...) {}

        using iterator_category = std::forward_iterator_tag;
        using value_type = ZipTuple<typename std::iterator_traits<Iterators>::value_type...>;
//    using value_type = ZipTuple<typename Iterators::value_type...>; <- doesn't work for int* :(
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = ptrdiff_t;

        // `reference` will return reference to the locally created object >:(
        value_type operator*() {
            return std::apply([](auto&... iterators) {
                return ZipTuple(*iterators...);
            }, iterators_tuple_);
        }

        value_type operator->() {
            return *(*this);
        }

        // Prefix.
        ZipIterator& operator++() {
            std::apply([](auto&... iterators) {
                ((++iterators), ...);
            }, iterators_tuple_);
            return *this;
        }

        // Postfix.
        ZipIterator operator++(int) {
            auto copy = ZipIterator(*this);
            ++(*this);
            return copy;
        }

        bool operator==(const ZipIterator& other) const {
            auto f = []<class OurTuple, class OtherTuple, size_t... Idx>(
                    OurTuple&& our, OtherTuple&& other,
                    std::index_sequence<Idx...>) {
                return (... && (std::get<Idx>(our) == std::get<Idx>(other)));
            };
            return f(iterators_tuple_, other.iterators_tuple_,
                     std::make_index_sequence<sizeof...(Iterators)>());
        }

        bool operator!=(const ZipIterator& other) const {
            return !(*this == other);
        }
    private:
        std::tuple<Iterators...> iterators_tuple_;
    };


    template<typename... Containers>
    class zip {
    public:
        explicit zip(Containers&... containers) : containers_tuple_(containers...) {}

//    using iterator = ZipIterator<decltype(std::declval<Containers>().begin())...>;
        using iterator = ZipIterator<typename Containers::iterator...>;
        using const_iterator = ZipIterator<typename Containers::const_iterator...>;

        iterator begin() {
            return std::apply([](auto&... containers) {
                return ZipIterator(containers.begin()...);
            }, containers_tuple_);
        }

        [[nodiscard]] size_t size() const {
            return std::apply([](const auto &...containers) {
                return std::min({containers.size()...});
            }, containers_tuple_);
        }

        iterator end() {
            size_t size_ = size();

            return std::apply([size_](auto &...containers) {
                return iterator(std::next(containers.begin(), size_)...);
            }, containers_tuple_);
        }

//    Old invalid implementation.
//    iterator end() {
//        return std::apply([](auto&... containers) {
//            return ZipIterator(containers.end()...);
//        }, containers_tuple_);
//    }
    private:
        std::tuple<Containers&...> containers_tuple_;
    };

    template<typename ...Containers>
    decltype(auto) make_zip(Containers&... containers) {
        return zip(containers...);
    }
}
