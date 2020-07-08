#ifndef BLOB_H
#define BLOB_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;

    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const;
    bool empty() const;
    void push_back(const std::string &val);
    void pop_back();

    std::string& front();
    std::string& back();
    const std::string& front() const;
    const std::string& back() const;

private:
    std::shared_ptr<std::vector<std::string>> data;

    void check(size_type i, const std::string &msg) const;
};

#endif