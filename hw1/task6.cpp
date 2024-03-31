/*Дано множество целых чисел из [0..10^9] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти 10%  перцентиль
Требования: к дополнительной памяти: O(n).
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition.
Рекурсия запрещена.
Решение должно поддерживать передачу функции сравнения снаружи.
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении
Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/
#include <iostream>

using namespace std;

int partition(int* arr, int l, int r) {
    int pivot = arr[r - 1];
    int i = l;

    for (int j = l; j < r - 1; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[r - 1]);
    return i;
}

int medianOfThreePartition(int* arr, int l, int r) {
    int mid = arr[r / 2];
    int first = arr[l];
    int last = arr[r - 1];

    int maxElem = max(max(first, last), mid);
    int minElem = min(min(first, last), mid);
    int medianElem = mid + first + last - maxElem - minElem;

    if (medianElem == mid) {
        swap(arr[r / 2], arr[r - 1]);
    } else if (medianElem == first) {
        swap(arr[l], arr[r - 1]);
    }

    return partition(arr, l, r);
}

int findKStat(int* arr, int n, int k) {
    int l = 0;
    int r = n;
    int pivotPos = medianOfThreePartition(arr, l, r);
    while (l < r) {
        if (pivotPos == k) {
            return arr[k];
        }
        if (pivotPos < k) {
            l = pivotPos + 1;
        } else {
            r = pivotPos;
        }
        pivotPos = medianOfThreePartition(arr, l, r);
    }
    return arr[k];
}

int main() {
    int n;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        int elem;
        cin >> elem;
        arr[i] = elem;
    }
    int tenPercentile;
    tenPercentile = n / 10;
    cout << findKStat(arr, n, tenPercentile) << endl;

    int median;
    median = n / 2;
    cout << findKStat(arr, n, median) << endl;

    int ninetyPercentile;
    ninetyPercentile = n * 9 / 10;
    cout << findKStat(arr, n, ninetyPercentile);
    delete[] arr;
    return 0;
}
