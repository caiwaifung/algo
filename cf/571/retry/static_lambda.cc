#include <functional>
#include <iostream>

void f(int x) {
    static auto g = [x]() mutable { std::cout << x << std::endl; };
    x=9;
    g();
}

int main() {
    f(5);
    f(8);
    return 0;
}
