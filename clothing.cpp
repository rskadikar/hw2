#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(string name, double price, int qty, std::string size, std::string brand)
: Product("clothing", name, price, qty), size_(size), brand_(brand)
{   }

set<string> Clothing::keywords() const {
    set<string> keyword_output;
    set<string> name_keywords = parseStringToWords(name_);
    for (set<string>::iterator it = name_keywords.begin(); it != name_keywords.end(); ++it) {
        keyword_output.insert(*it);
    }
    set<string> brand_keywords = parseStringToWords(brand_);
    for (set<string>::iterator it = brand_keywords.begin(); it != brand_keywords.end(); ++it) {
        keyword_output.insert(*it);
    }
    return keyword_output;
}

string Clothing::displayString() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << name_ << '\n' << "Size: " << size_ << " Brand: " << brand_ << '\n'
    << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(ostream& os) const {
    os << fixed << setprecision(2);
    os << "clothing\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n"
    << brand_ << "\n";
}
