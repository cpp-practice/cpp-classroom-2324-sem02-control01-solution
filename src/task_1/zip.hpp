#pragma once

#include <tuple>
#include <algorithm>
#include <cstddef>

namespace control_01 {
    template<typename ... Args>
    class ZipTuple : public std::tuple<Args&...> {
    public:
        explicit ZipTuple(Args& ...args) : std::tuple<Args&...>(args...) {}

        template<std::size_t N>
        decltype(auto) get() {
            return std::get<N>(static_cast<std::tuple<Args&...>&>(*this));
        }

        template <std::size_t N>
        auto get() const {
          return std::get<N>(static_cast<const std::tuple< Args&...>&>(*this));
        }

        ZipTuple* operator->() {
            return this;
        }

        const ZipTuple* operator->() const {
            return this;
        }
    };


    namespace details{
        template <typename... T>
        struct is_const{
            static constexpr bool value = (... || std::is_const_v<std::remove_reference_t< typename std::iterator_traits<T>::reference> >);
        };

        template <typename... T>
        static constexpr bool is_const_v = is_const<T...>::value;  
      
    }


    template<typename... Iterators>
    class ZipIterator {
    public:
        explicit ZipIterator(Iterators... iterators) : iterators_tuple_(iterators...) {}

        // using iterator_category = std::forward_iterator_tag; //zip_1
        using iterator_category = std::bidirectional_iterator_tag; //zip_2

        using value_type = std::conditional_t<
            details::is_const_v<Iterators...>,
            const ZipTuple<typename std::iterator_traits<Iterators>::value_type...>,
            ZipTuple<typename std::iterator_traits<Iterators>::value_type...>
            >;
        //    using value_type = ZipTuple<typename Iterators::value_type...>; <-
        //    doesn't work for int* :(
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = ptrdiff_t;

        // `reference` will return reference to the locally created object >:(
        value_type operator*() const {
            return std::apply([](auto&... iterators) {
                return ZipTuple(*iterators...);
            }, iterators_tuple_);
        }

        

        value_type operator->() const {
            return *(*this);
        }

        // Prefix.
        ZipIterator& operator++() {
            std::apply([](auto&... iterators) {
                ((++iterators), ...);
            }, iterators_tuple_);
            return *this;
        }

        ZipIterator& operator--() {
            std::apply([](auto&... iterators) {
                ((--iterators), ...);
            }, iterators_tuple_);
            return *this;
        }

        // Postfix.
        ZipIterator operator++(int) {
            auto copy = ZipIterator(*this);
            ++(*this);
            return copy;
        }

        ZipIterator operator--(int) {
            auto copy = ZipIterator(*this);
            --(*this);
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

//       iterators:
//       |---|
//       |-------|
//       |-----|
//       ^   ^
//       |   |
//    begin  |
//          end

        // using iterator = ZipIterator<typename Containers::iterator...>; //deosn't work for construcrot from const containers
        using iterator = ZipIterator<decltype(std::declval<Containers>().begin())...>;
        using const_iterator = ZipIterator<typename Containers::const_iterator...>;

//       reverse_iterators:
//           |---|
//       |-------|
//         |-----|
//           ^   ^
//           |   |
//        rend   |
//             rbegin
//      iterating with reverse_iterator != iterating containers from common end() 
//      we visit different set ov elemnts (compare visited range of elements on illustraion above)

        // using reverse_iterator = ZipIterator<typename Containers::reverse_iterator...>;
        using reverse_iterator =
            ZipIterator<decltype(std::declval<Containers>().rbegin())...>;
        using const_reverse_iterator = ZipIterator<typename Containers::const_reverse_iterator...>;

        iterator begin() {
            return std::apply([](auto&... containers) {
                return ZipIterator(containers.begin()...);
            }, containers_tuple_);
        }

        const_iterator begin() const { return cbegin(); }

        const_iterator cbegin() const{
            return std::apply([](const auto&... containers) {
                return ZipIterator(containers.cbegin()...);
            }, containers_tuple_);
        }


        reverse_iterator rbegin() {
          return std::apply(
              [](auto&... containers) {
                return ZipIterator(containers.rbegin()...);
              },
              containers_tuple_);
        }

        const_reverse_iterator rbegin() const { return crbegin(); }
        const_reverse_iterator crbegin() const {
          return std::apply(
              [](const auto&... containers) {
                return ZipIterator(containers.crbegin()...);
              },
              containers_tuple_);
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

        const_iterator end() const { return cend(); }

        const_iterator cend() const {
          size_t size_ = size();

          return std::apply(
              [size_](const auto&... containers) {
                return const_iterator(std::next(containers.cbegin(), size_)...);
              },
              containers_tuple_);
        }
        reverse_iterator rend() {
          size_t size_ = size();

          return std::apply(
              [size_](auto&... containers) {
                return reverse_iterator(std::next(containers.rbegin(), size_)...);
              },
              containers_tuple_);
        }

        const_reverse_iterator rend() const {
          return crend();
        }

        const_reverse_iterator crend() const {
          size_t size_ = size();

          return std::apply(
              [size_](const auto&... containers) {
                return const_reverse_iterator(
                    std::next(containers.rbegin(), size_)...);
              },
              containers_tuple_);
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
