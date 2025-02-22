//
//  clothing.hpp
//  
//
//  Created by Rachana Kadikar on 2/20/25.
//

#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Clothing : public Product {
public:
    Clothing(std::string name, double price, int qty, std::string size, std::string brand);
    std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;
private:
    std::string size_;
    std::string brand_;
};

#endif
