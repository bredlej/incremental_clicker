#include <clicker_app.hpp>
#include <kernel/bignum.hpp>

int main() {
    BigNum num1(1234.56, 3);
    BigNum num2(78.9, 6);
    num1.add(num2);

    std::cout << "Result: " << num1.toString() << std::endl;
    ClickerApp::run();
    return 0;
}
