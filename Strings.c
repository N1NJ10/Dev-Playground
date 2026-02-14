#include <stdio.h>
#include <string.h> // for strcmp



int main(int argc, char **argv) {

    // this is a string
    char *str = "hehe";

    // create the same string
    // as a character array
    char otherstr[] = {'h', 'e', 'h', 'e', 0} ; // The 0 for the end of the list

    if (!strcmp(str, otherstr)) {
        printf("Yay!\n");
    } else {
        printf("Nay!\n");
    }

    return 0;
}

