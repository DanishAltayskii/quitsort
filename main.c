#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void setConsoleEncoding() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int arr[], int left, int right) {
    if (left >= right) return;

    int i = left;
    int j = right;
    int pivot = arr[(left + right) / 2]; // ������� �������

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

int main() {
    setConsoleEncoding();

    int num_elements;
    printf("������� ���������� ���������: ");
    scanf("%d", &num_elements);

    if (num_elements <= 0) {
        printf("������� ������������� �����.\n");
        return 1;
    }

    const char* input_filename = "input.txt";
    const char* output_filename = "output.txt";

    // ��������� ��������� ����� � ������ � ����
    FILE* input_file = fopen(input_filename, "w");
    if (input_file == NULL) {
        printf("������ �������� ����� ��� ������\n");
        return 1;
    }

    srand(time(NULL));

    printf("��������� ����� '%s' � %d ���������� �������...\n", input_filename, num_elements);
    for (int i = 0; i < num_elements; i++) {
        fprintf(input_file, "%d\n", rand() % 10000);
    }
    fclose(input_file);

    // ������ ������ �� �����
    int* numbers = malloc(num_elements * sizeof(int));
    if (numbers == NULL) {
        printf("������ ��������� ������\n");
        return 1;
    }

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("������ �������� ����� ��� ������\n");
        free(numbers);
        return 1;
    }

    for (int i = 0; i < num_elements; i++) {
        fscanf(input_file, "%d", &numbers[i]);
    }
    fclose(input_file);

    printf("������ ���������. �������� ����������...\n");

    clock_t start_time = clock();
    quickSort(numbers, 0, num_elements - 1);
    clock_t end_time = clock();

    double sorting_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // ������ ����������
    FILE* output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("������ �������� ����� ��� ������\n");
        free(numbers);
        return 1;
    }

    for (int i = 0; i < num_elements; i++) {
        fprintf(output_file, "%d\n", numbers[i]);
    }
    fclose(output_file);

    printf("��������������� ������ ��������� � ���� '%s'\n", output_filename);
    printf("����� ����������: %.4f ������\n", sorting_time);

    free(numbers);
    return 0;
}