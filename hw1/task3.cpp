#include<iostream>
#include<sstream>
#include<string>
#include<cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;

class dynamicQueue {
public:
     dynamicQueue() : buffer(0) ,bufferSize(0), head(0), tail(0) {}
    ~dynamicQueue() {delete[] buffer;}

    void Enqueue(int a);
    int Dequeue();

    bool IsEmpty() const {return head == tail;}
private:
    int* buffer;
    int bufferSize;
    int head;
    int tail;

    void grow();
};

void dynamicQueue:: grow() {
    int defaultInitialSize = 2;
    int newBufferSize = max(bufferSize * 2, defaultInitialSize);
    int* newBuffer = new int[newBufferSize];

    int i = 0;
    while (i < bufferSize - 1) {
        newBuffer[i] = buffer[head];
        head = (head + 1) % bufferSize;
        ++i;
    }

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
    head = 0;
    tail = i;
}

void dynamicQueue::Enqueue(int a) {
    if (bufferSize == 0 || (tail + 1) % bufferSize == head) {
        grow();
    }
    buffer[tail] = a;
    tail = (tail + 1) % bufferSize;
}

int dynamicQueue::Dequeue() {
    int result;
    result = buffer[head];
    head = (head + 1) % bufferSize;
    return result;
}

void run(istream& input, ostream& output) {
    int n;
    int command;
    int value;
    input >> n;
    dynamicQueue dynQueue;
    bool result = true;

    for (int i = 0; i < n; i++) {
        input >> command;
        input >> value;
        
        switch (command)
        {
        case 2:
            if (dynQueue.IsEmpty()) {
                result = result && value == -1;
            } else {
                result = result && dynQueue.Dequeue() == value;
            }
            break;
        case 3:
            dynQueue.Enqueue(value);
            break;
        default:
            assert(false);
        }
    }
    output << (result ? "YES" : "NO");
    
}

void testQueue() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3 3 44 3 50 2 44";
        run(input, output);
        assert(output.str() == "YES");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "2 2 -1 3 10";
        run(input, output);
        assert(output.str() == "YES");
    }

    {
        std::stringstream input;
        std::stringstream output;
        input << "2 3 44 2 66";
        run(input, output);
        assert(output.str() == "NO");
    }
}

int main() {
    testQueue();
    return 0;
}