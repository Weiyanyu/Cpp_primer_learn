#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>

// ----- class Quote -----
class Quote {
public:
    Quote() = default;
    Quote(const std::string &bN, double sales_price):
            bookNo(bN), price(sales_price) { }

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const { return n * price; }
    virtual ~Quote() = default;

    //for debug
    virtual void debug() const;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};
// ----- class Disc_quote -----

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : 
        Quote(book, price), quantity(qty), discount(disc) {}

    double net_price(std::size_t) const = 0;
protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

// ----- class Bulk_quote -----

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &bN, double p, std::size_t qty, double disc) : 
                Disc_quote(bN, p, qty, disc) {}

    double net_price(std::size_t) const override;
    void debug() const override;
};


#endif