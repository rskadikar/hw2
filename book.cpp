#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(string name, double price, int qty, std::string isbn, std::string author)
: Product("book", name, price, qty), isbn_(isbn), author_(author)
{   }

set<string> Book::keywords() const {
    set<string> keyword_output;
    set<string> name_keywords = parseStringToWords(name_);
    for (set<string>::iterator it = name_keywords.begin(); it != name_keywords.end(); ++it) {
        keyword_output.insert(*it);
    }
    keyword_output.insert(isbn_);
    set<string> author_keywords = parseStringToWords(author_);
    for (set<string>::iterator it = author_keywords.begin(); it != author_keywords.end(); ++it) {
        keyword_output.insert(*it);
    }
    return keyword_output;
}

string Book::displayString() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << name_ << '\n' << "Author: " << author_ << " ISBN: " << isbn_ + '\n'
    << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(ostream& os) const {
    os << fixed << setprecision(2);
    os << "book\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n"
    << author_ << "\n";
}
