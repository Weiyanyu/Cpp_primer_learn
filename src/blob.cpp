#include "blob.h"

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) 
{

}

StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il))
{

}

StrBlob::size_type StrBlob::size() const {
    return data->size();
}

bool StrBlob::empty() const {
    return data->empty();
}

void StrBlob::push_back(const std::string &val) {
    data->push_back(val);
}

void StrBlob::pop_back() {
    check(0, "pop back on empty StrBlob");
    data->pop_back();
}

std::string& StrBlob::front() {
    check(0, "back on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

const std::string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string& StrBlob::back() const {
    check(0, "front on empty StrBlob");
    return data->back();
}

void StrBlob::check(StrBlob::size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}