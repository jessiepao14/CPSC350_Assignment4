#include <iostream>
#include <algorithm>
#include <cmath>

#include "Registrar.hpp"

using namespace std;

Registrar::Registrar(string name) {
    fileName = name;
    clockTick = 0;
    numWindows = 0;
    meanStudent = 0;
    medianStudent = 0;
    longestStudentWait = 0;
    studentWaitOver10Min = 0;
    meanWindow = 0;
    longestWindowWait = 0;
    windowIdleOver5Min = 0;
}

Registrar::~Registrar() {}

void Registrar::openForBusiness() {
    FileIO readQueue(fileName);
    readQueue.readFile();
    readQueue.getStudentQueue(studentArrivalQueue);
    readQueue.getWindowQueue(studentWaitQueue);
    numWindows = readQueue.getNumWindows();

    int totalTimeSize = studentArrivalQueue.getSize();
    int totalTime[totalTimeSize];
    for (int i = 0; i < totalTimeSize; ++i) {
        totalTime[i] = 0;
    }

    int windows[numWindows];                            
    for (int i = 0; i < numWindows; ++i) {
        windows[i] = 0;
    } 
    int idleWindows[numWindows];                       
    for (int i = 0; i < numWindows; ++i) {
        idleWindows[i] = 0;
    }
    
    int windowEmpty = -1;
    int currentWaitTime = 0;
    int currentIdle = 0;
    int nextPerson = 0;
    int personArrivalTime = 0;
    int numWindowsTaken = 0;
    int numberInLine = 0;
    int currentPerson = 0;

    bool checkEmptyWindows = true;
    
    while ((!studentArrivalQueue.isEmpty() && !studentWaitQueue.isEmpty()) || numWindowsTaken > 0) { 
        
        while (!studentArrivalQueue.isEmpty() && studentArrivalQueue.peek() <= clockTick && numWindowsTaken < numWindows) {       // When the student arrives at the line
            nextPerson = studentWaitQueue.dequeue();
            personArrivalTime = studentArrivalQueue.dequeue();
            totalTime[currentPerson] -= personArrivalTime;
            for (int i = 0; i < numWindows; i++) {
                if (windows[i] == 0) {
                    windows[i] = nextPerson;
                    numWindowsTaken++;
                    currentPerson++;
                    break;
                }   
            }
            
        }
        
        for (int i = currentPerson; i < totalTimeSize; i++) {
            totalTime[i]++;
        }
        
        if (numWindowsTaken < numWindows) {
            for (int i = 0; i < numWindows; i++) {
                if (windows[i] == 0) {
                    idleWindows[i]++;       // increment how long the window is idle for
                    
                }   
            }
        } 
        if (numWindowsTaken > 0) {
            for (int i = 0; i < numWindows; i++) {
                if (windows[i] != 0) {
                    windows[i]--;   // decrement how long the student has been at the window
                    if (windows[i] == 0) {
                        numWindowsTaken--;
                    }
                } 
            }
        }
        clockTick++;
    }

    cout << "~~~~~~~~~Finished Processing~~~~~~~~~" << endl;

    calculateStudentWait(totalTime, totalTimeSize);
    calculateWindowWait(idleWindows, numWindows);
    printStudentWait();
    printWindwoWait();
}

void Registrar::calculateStudentWait(int totalTime[], int size) {
    int sumStudents = 0;
    int studentCounter = 0;
    longestStudentWait = totalTime[0];

    for (int i = 0; i < size; i++) { 
        if (totalTime[i] != 0) {
            sumStudents += totalTime[i];
            studentCounter++;
        }
        if (totalTime[i] > longestStudentWait) {
            longestStudentWait = totalTime[i];
        }
        if (totalTime[i] > 10) {
            studentWaitOver10Min++;
        }
    }
    if (studentCounter == 0) {
        meanStudent = 0;
    }else {
        meanStudent = (1.0) * sumStudents / studentCounter;
    }
    sort(totalTime, totalTime + size);
    medianStudent = totalTime[size / 2];

}

void Registrar::printStudentWait() {
    cout << "1. The mean student wait time : " << ceil(meanStudent * 100.0) / 100.0 << endl;
    cout << "2. The median student wait time : " << medianStudent << endl;
    cout << "3. The longest student wait time : " << longestStudentWait << endl;
    cout << "4. The number of students waiting over 10 minutes: " << studentWaitOver10Min << endl;
}

void Registrar::calculateWindowWait(int idleWindows[], int size) {
    meanWindow = 0;
    longestWindowWait = 0;
    windowIdleOver5Min = 0;

    int sumWindow = 0;
    int windowCounter = 0;

    for (int i = 0; i < size; i++) { 

        if (idleWindows[i] != 0) {
            sumWindow += idleWindows[i];
            windowCounter++;
        }
        if (idleWindows[i] > longestWindowWait) {
            longestWindowWait = idleWindows[i];
        }
        if (idleWindows[i] > 5) {
            windowIdleOver5Min++;
        }
    }
    if (windowCounter == 0) {
        meanWindow = 0;
    } else {
        meanWindow = (1.0) * sumWindow / windowCounter;
    }
    
}

void Registrar::printWindwoWait() {
    cout << "5. The mean window idle time: " << ceil(meanWindow * 100.0) / 100.0 << endl;
    cout << "6. The longest window idle time: " << longestWindowWait << endl;
    cout << "7. Number of windows idle for over 5 minutes: " << windowIdleOver5Min << endl;
}
