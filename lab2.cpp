#include <iostream>
#include <ctime>
#include <locale>

int main() {
    setlocale(LC_ALL, "Russian");

    int N;
    std::cout << "Введите размер массива: ";
    std::cin >> N;

    int** a = new int* [N];
    for (int i = 0; i < N; i++) a[i] = new int[N];

    int** b = new int* [N];
    for (int i = 0; i < N; i++) b[i] = new int[N];

    int** c = new int* [N];
    for (int i = 0; i < N; i++) c[i] = new int[N];

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 100 + 1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            b[i][j] = rand() % 100 + 1;
        }
    }

    clock_t start = clock();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int elem_c = 0;
            for (int r = 0; r < N; r++) {
                elem_c += a[i][r] * b[r][j];
            }
            c[i][j] = elem_c;
        }
    }

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Время выполнения: " << time_spent << " секунд" << std::endl;

    for (int i = 0; i < N; i++) {
        delete[] a[i];
        delete[] b[i];
        delete[] c[i];
    }
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}
