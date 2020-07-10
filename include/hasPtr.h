#ifndef HASPTR_H
#define HASPTR_H

#include <string>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : 
        ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    
    HasPtr(const HasPtr& p) : 
        ps(p.ps), i(p.i), use(p.use) 
    {
        ++*use;
    }
    
    HasPtr& operator=(const HasPtr& p) {
        ++*p.use; //防止自赋值，需要先递增
        if (--*use == 0) {
            delete ps;
            delete use;
        }
        ps = p.ps;
        use = p.use;
        i = p.i;
        return *this;
    }

    ~HasPtr() {
        *use--;
        if (*use == 0) {
            delete ps;
            delete use;
        }
    }

private:
    std::string *ps;
    int i;
    std::size_t *use;
};

#endif