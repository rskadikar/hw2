#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(string name, double price, int qty, std::string genre, string rating)
: Product("movie", name, price, qty), genre_(genre), rating_(rating)
{   }

set<string> Movie::keywords() const {
    set<string> keyword_output;
    set<string> name_keywords = parseStringToWords(name_);
    for (set<string>::iterator it = name_keywords.begin(); it != name_keywords.end(); ++it) {
        keyword_output.insert(*it);
    }
    keyword_output.insert(genre_);
    return keyword_output;
}

string Movie::displayString() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << name_ << '\n' << "Genre: " << genre_ << " Rating: " << rating_ << '\n'
    << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(ostream& os) const {
    os << fixed << setprecision(2);
    os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n"
    << rating_ << "\n";
}
