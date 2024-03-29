#include<iostream>
#include<sstream>
#include<string>
#include<cassert>
#define assertm(exp, msg) assert(((void)msg, exp))
using namespace std;

unsigned int numOfEvenBits(unsigned int number) {
    unsigned int counter;  
    counter = 0;
    
    while(number > 0) {
        if ((number & 1) == 1) {
            ++counter;
        }
        number = number >> 2;
    }
    return counter;
}

void run(istream& input, ostream& output) {
    unsigned int number;
    unsigned int counter;
    input >> number;
    output << numOfEvenBits(number);
    return;
}

void testQueue() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "25";
        run(input, output);
        assert(output.str() == "2");
    }
}

int main() {
    testQueue();
    return 0;
}