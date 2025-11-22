#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ====================== PROTOTYPES, MACROS & STRUCTS ==========================
// ---------------------- prototypes ------------------
void display_array(const char *prompt, const int size, const int array[]);
void array_merge(const int size1, const int size2, const int array1[], const int array2[], int *array3);
void sorted_array_merge(const int size1, const int size2, const int array1[], const int array2[], int *array3);
int* get_valid_array(const char* prompt, const int arr_size);
int get_valid_int(const char* prompt, const int min, const int max);
void clear_input_buffer(void);
void bubble_sort(int* arr, const int arr_size);

// ----------------------- macros -----------------------
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define RESET   "\033[0m"

// ========================= MAIN FUNCTION ========================================
int main(void)
{
    // --------------- declaration ------------------
    int arr1_size, arr2_size, arr_size;
    int *arr1 = NULL, *arr2 = NULL, *merged_sorted_arr = NULL, *merged_unsorted_arr = NULL;

    // --------------- Handling input ----------------
    printf(BLACK "\n========== [Getting Input] ==========\n\n----Array sizes----\n" RESET);
    arr1_size = get_valid_int(MAGENTA "What's the size of your first array" RESET, 1, 1000); // size of first array
    arr2_size = get_valid_int(MAGENTA "What's the size of your second array" RESET, 1, 1000); // size of second array
    arr_size = arr1_size + arr2_size;
    
    printf(BLACK "\n---Array elements---\n" RESET);
    arr1 = get_valid_array(BLUE "Reading the elements of your first array" BLUE, arr1_size); // first array
    arr2 = get_valid_array(BLUE "Reading the elements of your second array" BLUE, arr2_size); // second array
    merged_sorted_arr = (int*)malloc(arr_size * sizeof(int)); 
    merged_unsorted_arr = (int*)malloc(arr_size * sizeof(int));

    // check for failed allocation
    if (!arr1 || !arr2 || !merged_sorted_arr || !merged_unsorted_arr) {
        perror(RED "ERROR: One or more memory allocations failed.\n" RESET);
        // Clean up what we could allocate before exiting
        if (arr1) free(arr1);
        if (arr2) free(arr2);
        if (merged_sorted_arr) free(merged_sorted_arr);
        if (merged_unsorted_arr) free(merged_unsorted_arr);
        return 1;
    }

    // -------------------- output -----------------------
    printf(BLACK "\n========== [Display Results] ==========\n\n" RESET);
    // displaying the user's initial arrays...
    display_array(YELLOW "[INITIAL]: " RESET GREEN "Displaying the first array" RESET, arr1_size, arr1);
    display_array(YELLOW "[INITIAL]: " RESET GREEN "Displaying the second array" RESET, arr2_size, arr2);
    printf("\n");

    // sorting the user's initial arrays in ascending order (bubble sort)...
    bubble_sort(arr1, arr1_size);
    bubble_sort(arr2, arr2_size);

    // displaying the sorted arrays...
    display_array(YELLOW "[SORTED]: " RESET GREEN "Displaying the first array" RESET, arr1_size, arr1);
    display_array(YELLOW "[SORTED]: " RESET GREEN "Displaying the second array" RESET, arr2_size, arr2);
    printf("\n");

    // merging the sorted arrays into an unsorted/sorted array...
    array_merge(arr1_size, arr2_size, arr1, arr2, merged_unsorted_arr);
    display_array(YELLOW "[UNSORTED]: " RESET GREEN "Displaying the merged, first & second, array" RESET, arr_size, merged_unsorted_arr);
    sorted_array_merge(arr1_size, arr2_size, arr1, arr2, merged_sorted_arr);
    display_array(YELLOW "[SORTED]: " RESET GREEN "Displaying the merged, first & second, array" RESET, arr_size, merged_sorted_arr);

    // Freeing memory
    free(arr1);
    free(arr2);
    free(merged_sorted_arr); 
    free(merged_unsorted_arr);

    return 0;
}


// ============================== PROTOTYPE DEFINITION =================================
void display_array(const char* prompt, const int size, const int array[])
{
    if (size == 0)
    {
        printf("\n[]\n");
        return;
    }

    printf("%s: [", prompt);
    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}


void array_merge(const int size1, const int size2, const int array1[], const int array2[], int *array3)
{
    for (int i = 0; i < size1; i++)
    {
        array3[i] = array1[i];
    }
    
    for (int j = 0; j < size2; j++)
    {
        array3[size1 + j] = array2[j];
    }
}


void sorted_array_merge(const int size1, const int size2, const int array1[], const int array2[], int *array3)
{
    int i = 0, j = 0, count = 0;
    while (i < size1 && j < size2)
    {
        if (array1[i] <= array2[j])
        {
            array3[count++] = array1[i++];
        } else 
        {
            array3[count++] = array2[j++];
        }
    }

    // NOTE: only one loop would execute
    while (j < size2) // checks if there are any elements in arr2 left
    {
        array3[count++] = array2[j++];
    }
    
    while (i < size1) // checks if there are any elements in arr1 left
    {
        array3[count++] = array1[i++];
    }
    
}


void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int get_valid_int(const char* prompt, const int min, const int max)
{
    int result;
    printf("%s: ", prompt);
    while (scanf("%d", &result) != 1 || result < min || result > max)
    {
        printf(RED "ERROR: INVALID INPUT. MUST BE AN INTEGER\n" RESET);
        clear_input_buffer();
    }
    return result;
}


int* get_valid_array(const char* prompt, const int arr_size)
{
    printf("%s...\n", prompt);

    int* arr = (int*)malloc(arr_size * sizeof(int)); // allocating an n sized array
    if (arr == NULL)
    {
        perror(RED "ERROR: ARRAY MEMORY ALLOCATION FAILED!\n" RESET);
        return NULL;
    }

    for (int i = 0; i < arr_size; i++)
    {
        char buffer[50];
        snprintf(buffer, 50, MAGENTA "Enter element %d" RESET, i);
        arr[i] = get_valid_int(buffer, -10000, 10000);
    }

    return arr;
}


void bubble_sort(int* arr, const int arr_size)
{
    bool swapped = false;
    int temp;
    for (int i = 0; i < arr_size - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < arr_size - 1 - i; j++)
        {
            if (arr[j] >= arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}
