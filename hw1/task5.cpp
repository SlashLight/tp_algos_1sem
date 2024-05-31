#include<iostream>
#include<sstream>
#include<string>
#include<cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;

struct userTimeline
{
    int in;
    int out;

    userTimeline() : in(0), out(0) {}
    userTimeline(int in, int out) : in(in), out(out) {}
};


template<class T>
bool isLessByDefault(const T& l, const T& r) {
    return l < r;
}

bool isLessByOutTime(const userTimeline& l, const userTimeline& r) {
    return l.out < r.out;
}
template<class T>
void merge(T* arr, int p, int q, int r, bool compare(const T&, const T&) = isLessByDefault) {
    int n1 = q - p + 1;
    int n2 = r - q;
    T* L = new T[n1];
    T* R = new T[n2];
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[p + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[q + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = p;
    for (; i < n1 && j < n2; ++k) {
        if (compare(L[i], R[j])) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
    }
    for (;i < n1; ++k) {
        arr[k] = L[i];
        ++i;
    }
    for (;j < n2; ++k) {
        arr[k] = R[j];
        ++j;
    }
    delete[] R;
    delete[] L;
}
template<class T>
void mergeSort(T* arr, int p, int r, bool compare(const T&, const T&)= isLessByDefault) {
    if (p >= r) {
        return;
    }
    int q = (p + r) / 2;
    mergeSort(arr, p, q, compare);
    mergeSort(arr, q + 1, r, compare);
    merge(arr, p, q, r, compare);
}

int main() {
    int n;
    cin >> n;
    auto* a = new userTimeline[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i].in >> a[i].out;
    }

    mergeSort(a, 0, n - 1, isLessByOutTime);

    int counter = 0;
    int t2 = -1;
    int t1 = -1;

    for (int i = 0; i < n; ++i) {
        if (t2 < a[i].in) {
            t2 = a[i].out;
            t1 = t2 - 1;
            counter += 2;
        } else if (t1 < a[i].in) {
            t1 = t2;
            t2 = a[i].out;
            counter++;
        }
    }
    cout << counter;
}