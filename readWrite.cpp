#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>

int main() {
    FILE *fptr;
    char filename[100];
    char line[256];
    clock_t start, end;
    double cpu_time_used;

    printf("Enter filename: ");
    scanf("%s", filename);

    start = clock();

    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("Enter text (enter 'exit' to stop):\n");
    while (1) {
        fgets(line, 256, stdin);
        if (strcmp(line, "exit\n") == 0) {
            break;
        }
        fprintf(fptr, "%s", line);
    }

    fclose(fptr);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Writing time: %f seconds\n", cpu_time_used);

    start = clock();

    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("\nContents of %s:\n", filename);
    while (fgets(line, 256, fptr) != NULL) {
        printf("%s", line);
    }


    fclose(fptr);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Reading time: %f seconds\n", cpu_time_used);

    return 0;
}