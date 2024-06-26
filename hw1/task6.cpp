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

template <class T>
bool IsLessDefault(const T& l, const T& r) {
    return l < r;
}

template <class T>
int partition(T* arr, int l, int r, bool isLess(const T& l, const T& r)) {
    int pivot = arr[r - 1];
    int i = l;

    for (int j = l; j < r - 1; ++j) {
        if (isLess(arr[j], pivot)) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[r - 1]);
    return i;
}

template <class T>
int medianOfThreePartition(T* arr, int l, int r, bool isLess(const T& l, const T& r)) {
    T mid = arr[(r - 1 + l) / 2];
    T first = arr[l];
    T last = arr[r - 1];

    T maxElem = max(max(first, last), mid);
    T minElem = min(min(first, last), mid);
    T medianElem = mid + first + last - maxElem - minElem;

    if (medianElem == mid) {
        swap(arr[(r - 1 + l) / 2], arr[r - 1]);
    } else if (medianElem == first) {
        swap(arr[l], arr[r - 1]);
    }

    return partition(arr, l, r, isLess);
}

template <class T>
int findKStat(T* arr, int n, int k, bool isLess(const T& l, const T& r) = IsLessDefault) {
    int l = 0;
    int r = n;
    int pivotPos = medianOfThreePartition(arr, l, r, isLess);
    while (l < r) {
        if (pivotPos == k) {
            return arr[k];
        }
        if (pivotPos < k) {
            l = pivotPos + 1;
        } else {
            r = pivotPos;
        }
        pivotPos = medianOfThreePartition(arr, l, r, isLess);
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
