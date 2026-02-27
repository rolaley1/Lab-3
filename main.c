#include <stdio.h>
#include <stdlib.h>

int sum_array(const int *arr, long n);  // arr in %rdi, n in %rsi, return in %eax

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <datafile>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    long n = 0;
    if (fscanf(fp, "%ld", &n) != 1 || n < 0) {
        fprintf(stderr, "Bad first line (count)\n");
        fclose(fp);
        return 1;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (!arr) {
        perror("malloc");
        fclose(fp);
        return 1;
    }

    for (long i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            fprintf(stderr, "Bad data at index %ld\n", i);
            free(arr);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    int sum = sum_array(arr, n);
    printf("Sum: %d\n", sum);

    free(arr);
    return 0;
}