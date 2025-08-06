#include<iostream>
#include "./LinkedListHeader.h"
#include "./HashTable.h"
using namespace std;

class Crawler{
    private:
    char URL[100];
    char tarDir[100];
    int depth;
    List<char*> urlList;
    HashTable<char*,char*> urlMap;
    public:
    Crawler();
    Crawler(char* url,char* targetDir,int depth);
    void downloadHTML(char * url,int depth,int curr_depth,int linkCount);
    void checkDirectory();
    int checkURL(char* testURL);
    void giveName(char* filename,int len);
    void extractUrls(char *filepath, int depth, int currDepth, int linkCount);
    void insertUrl(char *url , char* fullPath);
    void displayURLs();
};