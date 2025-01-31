#include<iostream>
using namespace std;

int main() {
    FILE *fptr;
    fptr = fopen("new.txt", "r");
    char str[100];
    fgets(str, 100, fptr);
    printf("%s", str);
    return 0;
}

