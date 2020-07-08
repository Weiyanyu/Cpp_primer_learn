#include "Quote.h"

//----- class Quote -----


// ----- class Bulk_quote -----

double Bulk_quote::net_price(std::size_t cnt) const 
{

    if (cnt >= this->quantity) {
        return cnt * (1 - this->discount) * this->price;
    } else {
        return cnt * this->price;
    }

}

void Bulk_quote::debug() const 
{
    std::cout << this->quantity << this->discount;
}

