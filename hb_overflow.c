//gcc hb_overflow.c -o hp_overflow -fno-stack-protector -z execstack -no-pie
//Answer: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAOVERWRITE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer = (char*) malloc(32);   // small heap buffer
    char *secret = (char*) malloc(32);   // another heap buffer

    strcpy(secret, "TOP_SECRET_KEY");    // sensitive data

    printf("Buffer at %p\n", (void*)buffer);
    printf("Secret at %p\n", (void*)secret);
    printf("Enter some text: ");

    // UNSAFE: allows heap overflow into "secret"
    gets(buffer);

    printf("You typed: %s\n", buffer);
    printf("Secret is still: %s\n", secret);

    free(buffer);
    free(secret);
    return 0;
}

