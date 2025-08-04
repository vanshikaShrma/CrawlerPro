#include<iostream>
using namespace std;

class Crawler{
    private:
    char URL[100];
    char tarDir[100];
    int depth;
    public:
    Crawler();
    Crawler(char* url,char* targetDir,int depth);
    void downloadHTML();
    void checkDirectory();
    int checkURL();
    void giveName(char* filename,int len);
};