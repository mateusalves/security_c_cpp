#include <iostream>

class MyClass
{
public:
    MyClass()
    {
        std::cout << "MyClass constructor called!" << std::endl;
        data = 0;
    }
    explicit MyClass(int value) : data(value)
    {
        std::cout << "Constructing MyClass object with value: " << value << std::endl;
    }

    ~MyClass()
    {
        std::cout << "MyClass destructor called!" << std::endl;
    }
private:
    int data;
};

int main()
{
    // Single object allocation and initialization
    std::cout << "Allocating memory for a single object with value ... " << std::endl;
    MyClass *objWithValue = new MyClass(42); // Constructor with parameter called


    std::cout << "Allocating memory for a single object... " << std::endl;
    MyClass *obj = new MyClass; // Default ctor called

    // Don't forget to release the memory to avoid memory leaks
    std::cout << "Releasing allocated memory..." << std::endl;
    delete obj;
    delete objWithValue;

    std::cout << "---------------------------------------------------------\n";

    // Allocating memory and initializing built-in types
    int *i = new int; //uninitialized
    int *j = new int(); // calling empty new iniializer -> guaranteed to be initialized to 0

    std::cout << "i: " << *i << std::endl;
    std::cout << "j: " << *j << std::endl;


    std::cout << "---------------------------------------------------------\n";

    // Plain Old Data Type
    struct MyStruct
    {
        int i;
        double d;
    };

    // Not initialized
    MyStruct *s1 = new MyStruct;
    std::cout << "s1->i: " << s1->i << std::endl; // not initialized
    std::cout << "s1->d: " << s1->d << std::endl; // not initialized

    // Initialized to 0
    MyStruct *s2 = new MyStruct();
    std::cout << "s2->i: " << s2->i << std::endl; // not initialized
    std::cout << "s2->d: " << s2->d << std::endl; // not initialized

    delete s1;
    delete s2;

    std::cout << "---------------------------------------------------------\n";
    // Placement new operator (allocate memory without constructing the object)
    // Allocate memory
    int *ptr = new int;
    void *memory = operator new (sizeof(MyClass), ptr); // let us construct the object in a arbitrary memory location

    // Construct object in the pre-allocated memory
    // No additional memory allocation is performed
    MyClass *inst = new (memory) MyClass(42);

    // print address of the instance
    std::cout << "Address of the instance: " << inst << std::endl;
    // print address of ptr
    std::cout << "Address of ptr: " << ptr << std::endl;

    // Use the object
    // ...

    // Destruct the object without deallocating memory
    inst->~MyClass();

    // Deallocate memory
    operator delete(memory);
    return 0;
}
