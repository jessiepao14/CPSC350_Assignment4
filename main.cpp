#include <iostream>
#include <string>
#include "Registrar.hpp"

using namespace std;

void welcome();

int main(int argc, char const *argv[])
{
    if (argc == 2) { // if there is a file as a command line argument
        welcome();
        string filename = argv[1];
        Registrar registrar(filename);
        cout << "Start....." << endl;
        registrar.openForBusiness();
        cout << "DONE!" << endl;
    } else {    // if there isn't a file exit the program
        cout << "Please enter a file to read as an argument" << endl;
    }
    return 0;
}

void welcome() {
    cout << "~~~~~~~~~~~~ Assignment 4: Registrar ~~~~~~~~ "<< endl;
}