#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"
#include <map>
#include <queue>

class MyDataStore: public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::string username, Product* item);
    void viewCart(std::string username);
    void buyCart(std::string username);
    bool userExists (std::string username);
private:
    std::set<Product*> product_set_;
    std::map<std::string, std::set<Product*>> key_prod_map_;
    std::map<std::string, User*> user_map_;
    std::map<std::string, std::queue<Product*>> cart_;
};

#endif
