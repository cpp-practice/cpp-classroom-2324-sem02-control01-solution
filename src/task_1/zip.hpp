

// helpers

// refers to int, char, ...
// does not own any elements
template<typename ... Args>
class ZipTuple {
    // access with get
};


// main object-iterator
// contains current iterators to zipped containers
template<typename... Iterators>
class ZipIterator {
    // operator*() returns ZipTuple
    // operator++
    // operator==
    // ...
};


// main solution

// aware of containers
// does not own them
template<typename... Containters>
class zip {
    // type members:
    // iterator = 
    // const_iterator = 

    // methods:
    // begin()
    // end()
    // ...
};
