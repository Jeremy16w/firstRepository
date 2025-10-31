#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//=========================== FUNCTION PROTOTYPES =============================
// --------------- action functions ---------------
void bubble_sort(int arr[], int arr_size);
int binary_search(const int arr[], int arr_size, int target);
void print_arr(const char *prompt, const int arr[], int arr_size);

//--------------------- input helpers ------------------------
int get_valid_int(const char *prompt, int min, int max);
int* get_valid_array(int arr_size);
void clear_input_buffer(void);

// ====================== MAIN FUNCTION =====================================
int main() 
{
    int *arr = NULL, arr_size = 0;

    arr_size = get_valid_int("How many elements in your array: ", 1, 1000);
    arr = get_valid_array(arr_size);
    if (!arr)
    {
        perror("ERROR: MEMORY ALLOCATION FAILED\n");
        return EXIT_FAILURE;
    }

    print_arr("Your unsorted array: ", arr, arr_size);
    bubble_sort(arr, arr_size);
    print_arr("Your sorted array: ", arr, arr_size);
    
    int target = get_valid_int("Which element do you want to search for: ", -1000000, 1000000);
    int result = binary_search(arr, arr_size, target);

    if (result != -1)
    {
        printf("Target %d is at index %d", target, result);
    } else 
    {
        printf("ERROR: ELEMENT %d doesn't exist within your array!\n", target);
    }

    
    free(arr);

    return EXIT_SUCCESS;
}


// =============================== action functions ======================
void bubble_sort(int arr[], int arr_size)
{
    bool isSwapped = false;
    int temp;
    do 
    {
        isSwapped = false;
        for (int i = 0; i < arr_size - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                isSwapped = true;
            }
        }
    } while (isSwapped);
}


void print_arr(const char *prompt, const int arr[], int arr_size)
{
    printf("%s\n", prompt);
    for (int i = 0; i < arr_size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int binary_search(const int arr[], int arr_size, int target)
{
    int max = arr_size - 1, min = 0, index;
    while (min <= max)
    {
        index = (min + max) / 2;

        if (arr[index] == target)
        {
            return index;
        } else if (target > arr[index])
        {
            min = index + 1;
        } else
        {
            max = index - 1;
        }
    }

    return -1;
}


// =========================== helper functions =========================
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int* get_valid_array(int arr_size)
{
    int *arr = (int *)malloc(arr_size * sizeof(int));
    if (!arr)
        return NULL;

    for (int i = 0; i < arr_size; i++)
    {
        char prompt[50];
        snprintf(prompt, sizeof(prompt), "Element %d: ", i + 1); // writes inside the string buffer "prompt"
        arr[i] = get_valid_int(prompt, -1000000, 1000000);
    }
    return arr;
}


int get_valid_int(const char *prompt, int min, int max)
{
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1 || (value < min || value > max))
    {
        printf("ERROR: INVALID INPUT\n");
        clear_input_buffer();
    }
    return value;
}
