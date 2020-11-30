#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int read_array(int *arr, size_t *array_size){
    int x;
    char check = ' ';
    scanf("%d%c", &x, &check);
    arr[0] = x;
    int count = 1;
    while (check != '\n'){
        scanf("%d%c", &x, &check);
        arr[count++] = x;
    }
    *array_size = count;
    return 0;
}
int read_parameters(int argc, char **argv, int *to, int *from){
    int from_count = 0;
    int to_count = 0;
    char *check1 = "--to=";
    char *check2 = "--from=";
    if (argc < 2){
        fprintf(stderr, "You should enter 1 or 2 parameters");
        return -1;
    }
    if (argc > 3){
        fprintf(stderr, "You should enter 1 or 2 parameters");
        return -2;
    }
    for (int i = 1; i < argc; ++i){
        if (strncmp(check1, argv[i], 5) == 0){
            to_count++;
            *to = (int)strtoll(argv[i] + 5, NULL, 10);
        }
        if (strncmp(check2, argv[i], 7) == 0){
            from_count++;
            *from = (int)strtoll(argv[i] + 7, NULL, 10);
        }
    }
    if (to_count > 1 || from_count > 1) {
        fprintf(stderr, "You should enter 1 parameter \"to\" or \"from\"");
        return -3;
    }
    if (to_count == 0 && from_count == 0){
        fprintf(stderr, "You should enter parameters \"to\" or \"from\"");
        return -4;
    }
    return 0;
}
int array_filtration(const int *arr, size_t array_size, int to, int from, int *filtered_array, size_t *filtered_array_size){
    int filtered_array_size_count = 0;
    for (size_t i = 0; i < array_size; i++){
        if (arr[i] > from && arr[i] < to){
            filtered_array[filtered_array_size_count++] = arr[i];
        } else if (arr[i] <= from){
            if (fprintf(stdout, "%d", arr[i]) < 0){
                fprintf(stderr, "Cannot be write in stdout");
                return -5;
            }
            if (arr[i] >= to){
                if (fprintf(stderr, "%d", arr[i]) < 0){
                    fprintf(stderr, "Cannot be write in stderr");
                    return -5;
                }
            }
        } else if (arr[i] >= to){
            if (fprintf(stderr, "%d", arr[i]) < 0){
                fprintf(stderr, "Cannot be write in stderr");
                return -5;
            }
            if (arr[i] <= from) {
                if (fprintf(stdout, "%d", arr[i]) < 0) {
                    fprintf(stderr, "Cannot be write in stdout");
                    return -5;
                }
            }
        }
    }
    *filtered_array_size = filtered_array_size_count;
    return 0;
}
int recording_filtered_array(const int *filtered_array, size_t filtered_array_size, int *array_for_compare){
    for (size_t i = 0; i < filtered_array_size; ++i){
        array_for_compare[i] = filtered_array[i];
    }
    return 0;
}
int sorting_filtered_array(int *filtered_array, size_t filtered_array_size);
int comparing_arrays(const int *filtered_array, size_t filtered_array_size, const int *array_for_compare){
    int permutation_counter = 0;
    for (size_t i = 0; i < filtered_array_size; ++i){
        if (filtered_array[i] != array_for_compare[i]){
            permutation_counter++;
        }
    }
    return permutation_counter;
}

int main(int argc, char **argv) {
    int from = INT_MIN;
    int to = INT_MAX;
    int arr[100];
    int *filtered_array = malloc(sizeof(int) * 100);
    int *array_for_compare = malloc(sizeof(int) * 100);
    size_t filtered_array_size;
    size_t array_size;
    int reading_results = read_parameters(argc, argv, &to, &from);
    if (reading_results != 0){
        return reading_results;
    }
    read_array(arr, &array_size);
    array_filtration(arr, array_size, to, from, filtered_array, &filtered_array_size);
    recording_filtered_array(filtered_array, filtered_array_size, array_for_compare);
    sorting_filtered_array(filtered_array, filtered_array_size);

    return comparing_arrays(filtered_array, filtered_array_size, array_for_compare);
}
