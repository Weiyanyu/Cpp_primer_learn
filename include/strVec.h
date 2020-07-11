#ifndef STRVEC_H
#define STRVEC_H

#include <string>
#include <memory>

class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const StrVec &rhs);
    StrVec(StrVec &&rhs) noexcept : 
        elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap) 
    {
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    StrVec& operator=(const StrVec &rhs);
    StrVec& operator=(StrVec &&rhs);
    ~StrVec() {
        free();
    }

    void push_back(const std::string &v);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

private:
    static std::allocator<std::string> alloc;

    void chk_n_alloc();
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);

    void free();
    void reallocate();
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

inline
StrVec::StrVec(const StrVec &rhs) {
    auto newData = alloc_n_copy(rhs.begin(), rhs.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

inline
StrVec& StrVec::operator=(const StrVec &rhs) {
    auto newData = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = newData.first;
    first_free = cap = newData.second;
    return *this;
}

inline
StrVec& StrVec::operator=(StrVec &&rhs) {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

inline 
void StrVec::push_back(const std::string &v) {
    chk_n_alloc();
    alloc.construct(first_free++, v);
}

inline
void StrVec::chk_n_alloc() {
    if (size() == capacity()) {
        reallocate();
    }
}

inline
std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* b, const std::string* e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

inline 
void StrVec::reallocate() {
    auto newCap = size() ? 2 * size() : 1;
    auto newData = alloc.allocate(newCap);

    auto dest = newData;
    auto elem = elements;

    for (size_t i = 0; i != size(); i++) {
        alloc.construct(dest++, std::move(*elem++));
    }

    free();
    elements = newData;
    first_free = dest;
    cap = elements + newCap;
}

inline 
void StrVec::free() {
    if (elements) {
        for (auto p = first_free; p != elements; ) {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}


#endif