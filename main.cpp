#include<iostream>
#include "./Crawler.h"
#include "./stringHeader.h"
using namespace std;

int main(int argc,char** argv)
{
    cout<<argv[1]<<endl;
    cout<<argv[2];
    Crawler cw(argv[1],argv[2],30);
     cout << "[main] cw: " << &cw << endl;
    cw.downloadHTML(argv[1],1,0,5);
    cout<<"ek kaam hogya"<<endl;
    cw.displayURLs();
    cw.wordsExtracted();
    return 0;
}