#include "Product.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << p.toString();
    return os;
}
