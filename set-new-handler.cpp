#include <iostream>
#include <new>

void customMemoryHandler()
{
    std::cerr << "Memory allocation failed. Custom memory handler called." << std::endl;
    abort();
}


int main()
{
    // Set custom memory handler
    std::set_new_handler(customMemoryHandler);

    int *ptr = new int[1000000000000000000]; // Attempt to allocate a huge array

    delete[] ptr;

    return 0;
}
