//#include <iostream>
#include <fstream>

#include "FileIO.hpp"
//#include "GenStructures.hpp"

FileIO::FileIO(string name)
{
    fileName = name;
    numWindows = 0;
    arrivalTime = 0;
    numberOfPeople = 0;
    idSetter = 0;
}

FileIO::~FileIO() {}

bool FileIO::readFile() {
    int currentLine;
    int lineNumber = 0;
    
    ifstream inFile;
    inFile.open(fileName);

    if(!inFile) {
        cout << "Error opening " << fileName << endl;
    }
    cout << "Openning " << fileName << " for reading.... " << endl;

    inFile >> currentLine;
    if (currentLine < 0) {
        cout << "ERROR!! The registrar is closed no windows are open" << endl;
        inFile.close();
        return false;
    } else {
        numWindows = currentLine;
    }

    while (inFile >> currentLine) {
        if (numberOfPeople == 0) {
            arrivalTime = currentLine;
            inFile >> numberOfPeople;
        } else {
            studentArrivalQueue.enqueue(arrivalTime);
            studentWaitQueue.enqueue(currentLine);
            --numberOfPeople;
        }
    }
    // cout << "\n\n Student Arrival Queue" << endl;
    // studentArrivalQueue.printQueue();

    // cout << "\n\n Student wait Queue" << endl;
    // studentWaitQueue.printQueue();

    // cout << fileName << " was successfully read" << endl;
    inFile.close();
    return true;
}

void FileIO::getStudentQueue(GenQueue<int> &arrivalQueue) {
    while (studentArrivalQueue.getSize() > 0) {
        arrivalQueue.enqueue(studentArrivalQueue.dequeue());
    }
}

void FileIO::getWindowQueue(GenQueue<int> &waitQueue) {
    while (studentWaitQueue.getSize() > 0) {
        waitQueue.enqueue(studentWaitQueue.dequeue());
    }
}

int FileIO::getNumWindows() {
    return numWindows;
}

