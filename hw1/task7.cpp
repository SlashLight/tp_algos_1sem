/*Дан массив строк. Количество строк не больше 105.
 * Отсортировать массив методом поразрядной сортировки MSD по символам.
 * Размер алфавита - 256 символов. Последний символ строки = ‘\0’.*/
#include<iostream>
#include<string>
#include<cassert>
using namespace std;
using std::string;

template <class T>
class CArray {
public:
    CArray() : buffer( 0 ), bufferSize( 0 ), realSize( 0 ){}
    ~CArray() {delete[] buffer;}
    CArray(CArray&) = delete;
    CArray& operator=(const CArray&) = delete;


    int Size() const {return realSize;}
    T* GetBuffer() {return buffer;}
    T GetAt( int index) const;
    T operator[](int index) const {return GetAt(index);}

    void Add(T element);
private:
    T* buffer;
    int bufferSize;
    int realSize;

    void grow();
};

template<class T>
T CArray<T>::GetAt(int index) const {
    assert(index >= 0 && index < realSize && buffer != 0);
    return buffer[index];
}

template<class T>
void CArray<T>:: grow() {
    int defaultBufferSize;
    defaultBufferSize = 10;
    int newBufferSize = max(bufferSize * 2, defaultBufferSize);
    T* newBuffer = new T[newBufferSize];
    for(int i = 0; i < realSize; ++i) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

template<class T>
void CArray<T>::Add(T element) {
    if (realSize == bufferSize) {
        grow();
    }
    assert(realSize < bufferSize && buffer != 0);
    buffer[realSize++] = element;
}

int getMaxRank(string* arr, int size) {
    int max;
    max = arr[0].size();
    for (int i = 1; i < size; ++i) {
        if (arr[i].size() > max) {
            max = arr[i].size();
        }
    }
    return max;
}

template<class T, class GetKey>
void MSD(T* arr, int l, int r, int rank,int maxRank, int alphabetSize, GetKey getKey) {
    if(l >= r - 1|| rank > maxRank) {
        return;
    }
    int* counter = new int[alphabetSize + 2];
    for (size_t k = 0; k < alphabetSize + 2; ++k) {
        counter[k] = 0;
    }

    for (size_t i = l; i < r; ++i) {
        ++counter[getKey(arr[i], rank) + 1];
    }

    for (size_t i = 1; i < alphabetSize + 2; ++i) {
        counter[i] += counter[i - 1];
    }

    auto* tempArr = new string[r - l];
    for (int i = r - 1; i >= l; --i) {
        tempArr[--counter[getKey(arr[i], rank) + 1]] = arr[i];
    }

    for (size_t i = l; i < r; ++i) {
        arr[i] = tempArr[i - l];
    }

    delete[] tempArr;
    for (int i = 0; i < alphabetSize; ++i) {
        MSD(arr, l + counter[i], l + counter[i + 1], rank + 1, maxRank, alphabetSize, getKey);
    }
    delete[] counter;

}

int main(){
    CArray<string> cArr;
    string word;
    while(cin >> word) {
        cArr.Add(word);
    }
    string* arr = cArr.GetBuffer();
    int maxRank = getMaxRank(arr, cArr.Size());
    MSD(arr, 0, cArr.Size(), 0, maxRank, 256, [](const string& str, const int rank){return (str.size() <= rank) ? 0 : str[rank];});
    for (int i = 0; i < cArr.Size(); ++i) {
        cout << arr[i] << endl;
    }
    return 0;
}