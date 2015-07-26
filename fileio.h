#ifndef FILEIO
#define FILEIO

namespace FileIO{
#include <iostream>
#include <fstream>
#include <string>
#include "vector"

using namespace std;

void createFile (){
    try {
        fstream createFile;
        createFile.open("SaveLoad.txt");

        if(createFile.fail()){
            ofstream outFile("saveload.txt");
        }
        createFile.close();

    }catch (exception e){}

}

void write(){

    string outputText = "Hello";

    try {
        fstream outFile;
        outFile.open("SaveLoad.txt", ios::out | ios::app );

        ifstream fileContent("SaveLoad.txt");

        int count = 0;

        string line;
        while(getline(fileContent, line)){
            count ++;
        }

        if(count < 1){
            outFile << outputText;
        }else{
            outFile << "\n" << outputText;
        }

        outFile.close();

    }
    catch (exception e){}
}

void read(){
    vector<string> linesVector;
    try {
        ifstream fileContent("SaveLoad.txt");
        string line;
        while(getline(fileContent, line)){
            linesVector.push_back(line);
        }
        cout << "V Size : " << linesVector.size();

    }
    catch (exception e){}
}
}

#endif // FILEIO

