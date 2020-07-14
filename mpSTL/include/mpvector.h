#ifndef MPVECTOR_H
#define MPVECTOR_H

#include <vector>
#include <memory>

class MpVector {
public:
    //typedef
    typedef std::size_t size_type;
    typedef int value_type;
    typedef ptrdiff_t difference_type;


    //constructor ....
    MpVector():m_begin(nullptr), m_end(nullptr), m_cap(nullptr) {}
    MpVector(const MpVector &rhs);
    MpVector(MpVector &&rhs) noexcept;
    MpVector& operator=(const MpVector &rhs);
    MpVector& operator=(MpVector &&rhs);
    ~MpVector() { free(); }


    //Capacity member function
    bool empty() const { return m_begin == m_end; }
    size_type size() const { return m_end - m_begin; }
    size_type capacity() const { return m_cap - m_begin; }
    size_type max_size() const noexcept { return static_cast<size_type>(-1) / sizeof(value_type); }

    //...need more

    //modifiers member function
    void push_back(const value_type& val);
    // void push_back(value_type&& val);
    
    


private:
    //static member
    static std::allocator<value_type> m_alloctor;

    //member
    value_type *m_begin;
    value_type *m_end;
    value_type *m_cap;

    //static function

    //normal function
    void free();

    //util function
    std::pair<value_type*, value_type*> alloc_n_copy(const value_type *b, const value_type *e);
    void check_n_alloc();
    void reallocate();

};

std::allocator<MpVector::value_type> MpVector::m_alloctor;

inline
MpVector::MpVector(const MpVector& rhs) {
    auto newData = alloc_n_copy(rhs.m_begin, rhs.m_end);
    m_begin = newData.first;
    m_end = newData.second;
    m_cap = newData.second;
}

inline
MpVector& MpVector::operator=(const MpVector& rhs) {
    
    auto newData = alloc_n_copy(rhs.m_begin, rhs.m_end);
    //avoid copy self, need alloc copy array first
    free();
    m_begin = newData.first;
    m_end = newData.second;
    m_cap = newData.second;
    return *this;
    
}

inline
MpVector::MpVector(MpVector&& rhs) noexcept : 
    m_begin(rhs.m_begin), m_end(rhs.m_end), m_cap(rhs.m_cap) {
    //because of move constructor, so we *must* set source object's member to null pointer.
    //we need sure source object not resource owner any more.
    //note: set member to null pointer, destructor will not release memory.
    rhs.m_begin = rhs.m_end = rhs.m_cap = nullptr;
}

inline
MpVector& MpVector::operator=(MpVector&& rhs) {
    if (&rhs == this) {
        free();

        m_begin = rhs.m_begin;
        m_end = rhs.m_end;
        m_cap = rhs.m_cap;

        rhs.m_begin = rhs.m_end = rhs.m_cap = nullptr;
    }
    return *this;
}

inline
void MpVector::free() {
    if (m_begin) {
        for (auto p = m_end; p != m_begin; p--) {
            m_alloctor.destroy(p);
        }
        m_alloctor.deallocate(m_begin, m_cap - m_begin);
    }
}

inline
std::pair<MpVector::value_type*, MpVector::value_type*> MpVector::alloc_n_copy(const value_type *b, const value_type *e) {
    auto first = m_alloctor.allocate(e - b);
    auto last = std::uninitialized_copy(b, e, first);
    return {first, last};
}

inline
void MpVector::check_n_alloc() {
    if (size() == capacity()) {
        reallocate();
    }
}

//TODO: need more op
inline
void MpVector::reallocate() {
    size_type newCap = size() == 0 ? 1 : size() * 2;
    value_type* newBegin = m_alloctor.allocate(newCap);

    value_type* newBeginTemp = newBegin;
    value_type* oldBegin = m_begin;

    for (size_type i = 0; i < size(); i++) {
        m_alloctor.construct(newBeginTemp++, std::move(*oldBegin++));
    }
    free();
    m_begin = newBegin;
    m_end = newBeginTemp;
    m_cap = newBegin + newCap;
}

inline
void MpVector::push_back(const MpVector::value_type& val) {
    check_n_alloc();
    m_alloctor.construct(m_end++, val);
}

#endif