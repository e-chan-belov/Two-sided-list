#include "Header.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    List<int> a(3);
    
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    
    List<int> b(a);
    
    std::cout << a[2] << std::endl;
    
    return 0;
}
