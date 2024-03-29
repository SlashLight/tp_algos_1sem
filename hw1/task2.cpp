#include<iostream>
#include<sstream>
#include<string>
#include<cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;

class CArray {
public:
    CArray() : buffer( 0 ), bufferSize( 0 ), realSize( 0 ){}
    ~CArray() {delete[] buffer; }

    int Size() const {return realSize;}

    int GetAt( int index) const;
    int operator[](int index) const {return GetAt(index);}

    void Add(int element);
private:
    int* buffer;
    int bufferSize;
    int realSize;

    void grow();
};

int CArray::GetAt(int index) const {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

void CArray:: grow() {
    int defaultBufferSize;
    defaultBufferSize = 10;
    int newBufferSize = max(bufferSize * 2, defaultBufferSize);
    int* newBuffer = new int[newBufferSize];
    for(int i = 0; i < realSize; ++i) {
        newBuffer[i] = buffer[i];
    }
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

void CArray::Add(int element) {
    if (realSize == bufferSize) {
        grow();
    }
    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

int binSearch(int* a, int first, int border, int elem) {
    int last;
    last = border;
    while(first < last) {
        int mid = (first + last) / 2;
        if (a[mid] < elem) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }

    return (first == border || a[first] < elem) ? -1 : first;
}

int expSearch(int* a, int size, int elem) {
    if (a[0] == elem) {
        return 0;
    }

    int i = 1;
    while(i < size && a[i] <= elem) {
        i *= 2;
    }

    return binSearch(a, i/2, min(i, size), elem);
}

void findIndexOfSuperriorElement(int* a, int* b, int sizeA, int sizeB, CArray* result) {
    for(int i = 0; i < sizeB; ++i) {
        int index;
        index = expSearch(a, sizeA, b[i]);
        if (index != -1) {
            result->Add(index);
        } else {
            result->Add(sizeA);
        }
    }
    return;
}

void run(istream& input, ostream& output) {
    int n;
    int m;
    input >> n;
    input >> m;
    int* a = new int[n];
    int* b = new int[m];

    for (int i = 0; i < n; i++) {
        input >> a[i];
    } 
    for (int i = 0; i < m; i++) {
        input >> b[i];
    } 
    CArray res;
    findIndexOfSuperriorElement(a, b, n, m, &res);
    int size;
    size = res.Size();
	for (int i = 0; i < size - 1; ++i) {
        output << res[i] << " ";
    }
    output << res[size - 1];
    delete[] a;
    delete[] b;
}

void testQueue() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "2 1 1 2 2";
        run(input, output);
        assert(output.str() == "1");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "4 3 2 4 5 7 4 6 1";
        run(input, output);
        string s;
        s = output.str();
        assert(s == "1 3 0");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "7 1 1 1 1 1 1 1 2 2";
        run(input, output);
        assert(output.str() == "6");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "7 2 1 1 1 1 1 1 2 2 5";
        run(input, output);
        string res;
        res = output.str();
        assert(res == "6 7");
    }
}

int main() {
    testQueue();
    return 0;
}