#include<iostream>
#include<sstream>
#include<string>
#include<cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;

struct Element {
    int Value;
    int ArrayIndex;
    int IndexInArray;
};

template<class T>
class DefaultComparator{
public:
    bool operator() (const Element& l, const Element& r) { return l.Value < r.Value;};
};


template<class T, class Comparator = DefaultComparator<T>>
class Heap {
public:
    Heap(Comparator _compare = Comparator()) :buffer(0), realSize(0), bufferSize(0), compare(_compare){};
    explicit Heap(T* arr, int arrSize, Comparator _compare = Comparator()): buffer(arr), realSize(arrSize), bufferSize(arrSize), compare(_compare) {
        buildHeap();
    };
    ~Heap(){};

    int Size() const {return realSize;}
    void Insert(const T& element) {
        if (realSize == bufferSize) {
            grow();
        }
        assert(realSize < bufferSize && buffer != 0);
        buffer[realSize++] = element;
        siftUp(Size() - 1);
    };
    T ExtractTop() {
        assert(Size() > 0);
        T result = buffer[0];
        buffer[0] = buffer[Size() - 1];
        realSize--;
        if (Size() > 0) {
            siftDown(0);
        }
        return result;
    };
    T CheckTop() {
        return buffer[0];
    }
    void Array() const {
        for(int i = 0; i < Size(); ++i){
            T elem = buffer[i];
            cout << buffer[i];
        }
    }

    bool IsEmpty() {return realSize == 0;}

private:
    Comparator compare;
    T* buffer;
    int bufferSize;
    int realSize;

    void grow() {
        int defaultBufferSize;
        defaultBufferSize = 10;
        int newBufferSize = max(bufferSize * 2, defaultBufferSize);
        T* newBuffer = new T[newBufferSize];
        for(int i = 0; i < realSize; ++i) {
            newBuffer[i] = buffer[i];
        }
        buffer = newBuffer;
        bufferSize = newBufferSize;
    };
    void buildHeap() {
        for(int i = Size() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    };
    void siftDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if(left < Size() && compare(buffer[left], buffer[i]))
            smallest = left;
        if(right < Size() && compare(buffer[right], buffer[smallest]))
            smallest = right;
    
        if (smallest != i) {
            T t;
            t = buffer[i];
            buffer[i] = buffer[smallest];
            buffer[smallest] = t;
            siftDown(smallest);
        }
    };
    void siftUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(compare(buffer[parent], buffer[index]))
                return;
            T t;
            t = buffer[index];
            buffer[index] = buffer[parent];
            buffer[parent] = t;
            index = parent;
        }
    };
};


int* heapMerge(int** arrOfArr, int n, int count) {
    Heap<Element> heapOfElems;
    for (int i = 0; i < n; ++i) {
        Element elem{arrOfArr[i][1], i, 0};
        heapOfElems.Insert(elem);
    }

    int* res = new int[count];
    for (int i = 0; i < count; ++i) {
        Element minElement;
        int indexOfMinArray;
        int lenOfMinArray;
        int indexOfNextElem;

        minElement = heapOfElems.ExtractTop();
        res[i] = minElement.Value;
        indexOfMinArray = minElement.ArrayIndex;
        lenOfMinArray = arrOfArr[indexOfMinArray][0];
        indexOfNextElem = minElement.IndexInArray + 1;
        
        if (indexOfNextElem < lenOfMinArray) {
            int nextValue = arrOfArr[indexOfMinArray][indexOfNextElem + 1];
            Element nextElement{nextValue, indexOfMinArray, indexOfNextElem};
            heapOfElems.Insert(nextElement);
        }
    }
    return res;
}

void run(istream& input, ostream& output) {
    int n;
    input >> n;
    int count = 0;
    int** arrOfArr = new int*[n];
    for(int i = 0; i < n; ++i) {
        int m;
        input >> m;
        arrOfArr[i] = new int[m + 1];
        arrOfArr[i][0] = m;
        for(int j = 1; j <= m; ++j) {
            int elem;
            input >> elem;
            arrOfArr[i][j] = elem; 
            count++;
        }
    } 

    int* res;
    res = heapMerge(arrOfArr, n, count);
    for (int i = 0; i < count; ++i) {
        output << res[i]<< " ";
    }
    for(int i = 0; i < n; ++i) {
        delete[] arrOfArr[i];
    } 
    delete[] arrOfArr;
    delete[] res;
}

void testQueue() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 1 6 2 50 90 3 1 10 70";
        run(input, output);
        string res = output.str();
        assert(output.str() == "1 6 10 50 70 90");
    }

}

int main() {
    testQueue();
    return 0;
}