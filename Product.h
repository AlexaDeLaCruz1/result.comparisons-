#ifndef SEARCH_LAB_PRODUCT_H
#define SEARCH_LAB_PRODUCT_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip> 

class Product {
public:
    Product(const std::string& productId, const std::string& name, double price, bool inStock)
        : productId_(productId), name_(name), price_(price), inStock_(inStock) {}

    Product(const Product& other) = delete;
    Product& operator=(const Product& other) = delete;
    ~Product() = default;
    std::string getProductId() const { return productId_; }
  
    std::string getName() const { return name_; }
  
    double getPrice() const { return price_; }

    bool getInStock() const { return inStock_; }

   
    std::string toString() const {
        std::stringstream ss;
        ss << "ID: " << productId_
           << ", Name: " << name_
           << ", Price: $" << std::fixed << std::setprecision(2) << price_
           << ", In Stock: " << (inStock_ ? "Yes" : "No");
        return ss.str();
    }


private:
    std::string productId_;
    
    std::string name_;
    
    double price_;
    bool inStock_;
};


std::ostream& operator<<(std::ostream& os, const Product& p);

#endif // SEARCH_LAB_PRODUCT_HRODUCT_H
