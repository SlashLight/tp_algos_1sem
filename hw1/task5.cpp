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


void run(istream& input, ostream& output) {
    int n;
    input >> n;
    userTimeline* a = new userTimeline[n];
    for (int i = 0; i < n; i++) {
        int in;
        int out;
        input >> in >> out;
        a[i] = userTimeline(in, out);
    }

    mergeSort(a, 0, n - 1, isLessByOutTime);

    int counter = 0;
    int t1 = -1;
    int t0 = -1;

    for (int i = 0; i < n; ++i) {
        if (t1 < a[i].in) {
            t1 = a[i].out;
            t0 = a[i].out - 1;
            counter += 2;
        } else if (t0 < a[i].in) {
            t0 = t1;
            t1 = a[i].out;
            counter++;
        }
    }
    output << counter;
}

void testQueue() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "5 1 10 10 12 1 10 1 10 23 24";
        run(input, output);
        assert(output.str() == "5");
    }

   {
        std::stringstream input;
        std::stringstream output;
        input << "3 1 10 8 10 5 10";
        run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "5 7 9 5 7 18 20 12 18 9 12";
        run(input, output);
        assert(output.str() == "6");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "1 2 25";
        run(input, output);
        assert(output.str() == "2");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "5 7 9 25 30 15 17 20 23 1 4";
        run(input, output);
        assert(output.str() == "10");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "5 7 12 15 19 8 14 17 20 23 25";
        run(input, output);
        assert(output.str() == "6");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "0";
        run(input, output);
        assert(output.str() == "0");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "5 1 10 1 7 1 15 1 5 1 13";
        run(input, output);
        assert(output.str() == "2");
    }
}

int main() {
    testQueue();
    return 0;
}