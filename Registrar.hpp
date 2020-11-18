#ifndef _REGISTRAR_HPP
#define _REGISTRAR_HPP

#include <iostream>
#include <string>
#include "GenStructures.hpp"
#include "FileIO.hpp"


class Registrar
{
    public:
        Registrar(string name);
        ~Registrar();

        void openForBusiness();
        void calculateStudentWait(int totalTime[], int size);
        void printStudentWait();
        void calculateWindowWait(int windowTime[], int size);
        void printWindwoWait();
    private:
        string fileName;
        int numWindows;
        int clockTick;

        double meanStudent;
        int medianStudent;
        int longestStudentWait;
        int studentWaitOver10Min;

        double meanWindow;
        int longestWindowWait;
        int windowIdleOver5Min;

        GenQueue<int> studentArrivalQueue;
        GenQueue<int> studentWaitQueue;
};


#endif 