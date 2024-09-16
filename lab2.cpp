#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <locale>
#include <cstdlib>
#include <chrono>
#include <time.h>

using namespace std;

void calc(int* a, int n);
void shell(int* items, int count);
void output(int* items, int count);
void qs(int* items, int left, int right);
int cmp(const void* x1, const void* x2);

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int N;
    cout << "Введите размер массива: ";
    cin >> N;

    int* A = new int[N];

    for (int i = 0; i < N; i++) {
        A[i] = rand() % 200 - 100;
    }

    cout << "\nДля массива из случайных чисел\n\n";
    calc(A, N);
    cout << "\n";

    // По возрастанию
    for (int i = 0; i < N; i++) {
        A[i] = i * 2 - N;
    }
    cout << "Для возрастающей последовательности\n\n";
    calc(A, N);
    cout << "\n";

    // По убыванию
    for (int i = 0; i < N; i++) {
        A[i] = -(i * 2 - N);
    }
    cout << "Для убывающей последовательности\n\n";
    calc(A, N);
    cout << "\n";

    // Половина убывает, половина возрастает
    for (int i = 0; i < N; i++) {
        A[i] = abs(i * 2 - N);
    }
    cout << "Для смешанной последовательности\n\n";
    calc(A, N);

    delete[] A;
    return 0;
}

void calc(int* a, int n) {
    clock_t start, end;
    double time;

    int* B = new int[n];

    memcpy(B, a, sizeof(int) * n);
    start = clock();
    shell(B, n);
    end = clock();
    time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Сортировка Шелла: " << time << " секунд\n";

    memcpy(B, a, sizeof(int) * n);
    start = clock();
    qs(B, 0, n - 1);
    end = clock();
    time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Быстрая сортировка: " << time << " секунд\n";

    memcpy(B, a, sizeof(int) * n);
    start = clock();
    qsort(B, n, sizeof(int), cmp);
    end = clock();
    time = double(end - start) / CLOCKS_PER_SEC;
    cout << "qsort: " << time << " секунд\n";

    delete[] B;
}

void output(int* items, int count) {
    for (int i = 0; i < count; i++) {
        cout << items[i] << " ";
    }
    cout << endl;
}

void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5] = { 9, 5, 3, 2, 1 };

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap) {
                items[j + gap] = items[j];
            }
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) {
    int i, j;
    int x, y;

    i = left; j = right;

    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int cmp (const void* x1, const void* x2) {
    return (*(int*)x1 - *(int*)x2);
}
