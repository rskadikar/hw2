#include <sstream>
#include <iomanip>
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore() {
    for (set<Product*>::iterator it = product_set_.begin() ; it != product_set_.end(); ++it) {
        delete *it;
    }
    for (map<string, User*>::iterator it = user_map_.begin(); it != user_map_.end(); ++it) {
        delete it->second;
    }

}
void MyDataStore::addProduct(Product* p) {
    product_set_.insert(p);
    set<string> keywords = p->keywords();
    for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        string lower = convToLower(*it);
        key_prod_map_[lower].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    if (user_map_.find(u->getName()) == user_map_.end()) {
        user_map_[u->getName()] = u;
    }
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    set<Product*> results_set = {};
    
    if (terms.size() == 1) {
        if (key_prod_map_.find(terms[0]) != key_prod_map_.end()) {
            results_set = key_prod_map_[terms[0]];
        }
        else {
            return {};
        }
    }
    else if (terms.size() > 1) {
        if (type == 0) { // and
            if (key_prod_map_.find(terms[0]) != key_prod_map_.end()) {
                results_set = key_prod_map_[terms[0]];
            }
            else {
                return {};
            }
            for (vector<string>::iterator it = terms.begin() + 1; it != terms.end(); ++it) {
                if (key_prod_map_.find(*it) != key_prod_map_.end()) {
                    results_set = setIntersection(results_set, key_prod_map_[*it]);
                    if (results_set.empty()) {
                        return {};
                    }
                }
                else {
                    return {};
                }
            }
        }
        
        if (type == 1) { // or
            if (key_prod_map_.find(terms[0]) != key_prod_map_.end()) {
                results_set = key_prod_map_[terms[0]];
            }

            for (vector<string>::iterator it = terms.begin() + 1; it != terms.end(); ++it) {
                if (key_prod_map_.find(*it) != key_prod_map_.end()) {
                    results_set = setUnion(results_set, key_prod_map_[*it]);
                }
            }
        }
    }
    vector<Product*> results_vector;
    for (set<Product*>::iterator it = results_set.begin(); it != results_set.end(); ++it) {
        results_vector.push_back(*it);
    }
    return results_vector;
}


void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    for (set<Product*>::iterator it = product_set_.begin(); it != product_set_.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>\n";
    
    ofile << "<users>\n";
    for (map<string, User*>::iterator it = user_map_.begin(); it != user_map_.end(); ++it) {
        (it->second)->dump(ofile);
    }
    ofile << "</users>\n";
}

void MyDataStore::addToCart(string username, Product* item) {
    if (user_map_.find(username) == user_map_.end()) {
        cout << "Invalid username" << endl;
        return;
    }
    cart_[username].push(item);
}

void MyDataStore::viewCart(string username) {
    if (userExists(username) == false) {
        cout << "Invalid username" << endl;
        return;
    }
    queue<Product*> iterator_temp = cart_[username];
    int index = 1;
    while (!iterator_temp.empty()) {
        Product* item = iterator_temp.front();
        cout << "Item " << index << endl;
        cout << item->displayString() << endl;
        iterator_temp.pop();
        index++;
    }
}

void MyDataStore::buyCart(string username) {
    if (user_map_.find(username) == user_map_.end()) {
        cout << "Invalid username" << endl;
        return;
    }
    User* user = user_map_[username];
    queue<Product*> remaining_items;
    while(!cart_[username].empty()) {
        Product* curr_item = cart_[username].front();
        if ((curr_item->getQty() >= 1) && (user->getBalance() > curr_item->getPrice())) {
            user->deductAmount(curr_item->getPrice());
            curr_item->subtractQty(1);
        }
        else {
            remaining_items.push(curr_item);
        }
        cart_[username].pop();
    }
    cart_[username] = remaining_items;
}

bool MyDataStore::userExists (string username) {
    if (user_map_.find(username) == user_map_.end()) {
        return false;
    }
    else {
        return true;
    }
}
