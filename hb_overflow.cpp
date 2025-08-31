// g++ hb_overflow.cpp -o hb_overflow -fno-stack-protector -z execstack -no-pie

#include <iostream>
#include <cstring>

class Base {
public:
    virtual void greet() { std::cout << "Hello from Base!" << std::endl; }
};

class Evil {
public:
    static void hacked() { std::cout << ">>> HACKED via heap overflow! <<<" << std::endl; }
};

int main() {
    // Allocate two adjacent heap objects
    char *buffer = new char[32];
    Base *obj = new Base();

    std::cout << "Buffer at " << (void*)buffer << std::endl;
    std::cout << "Obj at " << obj << std::endl;

    std::cout << "Normal call: ";
    obj->greet();

    std::cout << "Enter input to overflow buffer: ";
    std::cin.getline(buffer, 128);  // overflow buffer -> overwrite obj->vptr

    std::cout << "After overflow call: ";
    obj->greet();   // if vtable is smashed, may crash or redirect

    delete[] buffer;
    delete obj;
}

