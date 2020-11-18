#ifndef _FILE_IO_HPP
#define _FILE_IO_HPP

#include <iostream>
#include "GenStructures.hpp"

using namespace std;

class FileIO
{
    private:
        string fileName;
        int arrivalTime;
        int numberOfPeople;
        int idSetter;
        int numWindows;
        GenQueue<int> studentArrivalQueue;
        GenQueue<int> studentWaitQueue;

    public:
        FileIO(string name);
        ~FileIO();

        bool readFile();

        void getStudentQueue(GenQueue<int> &arrivalQueue);
        void getWindowQueue(GenQueue<int> &waitQueue);
        int getNumWindows();

};

#endif 