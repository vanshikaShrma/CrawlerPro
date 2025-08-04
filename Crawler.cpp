#include <iostream>
#include "./Crawler.h"
#include "./stringHeader.h"
#include <stdlib.h>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

Crawler::Crawler(char *url, char *targetDir, int depth)
{
    my_strcpy(URL, url);
    my_strcpy(tarDir, targetDir);
    this->depth = depth;
    cout << "initialization done" << endl;
    cout << URL << endl;
    cout << tarDir << endl;
    cout << this->depth << endl;
}
void Crawler::downloadHTML()
{
    char cmd[100];
    cmd[0] = '\0';
    char file[15]="abcdef.html";
    // giveName(file,15);
    cout<<file<<endl;
    if (checkURL())
    {
        checkDirectory();
        cout<<"hello"<<endl;
        my_strcat(cmd, "wget ");
        my_strcat(cmd, URL);
        my_strcat(cmd, " -O ");
        my_strcat(cmd, tarDir);
        my_strcat(cmd, "/");
        cout<<"aaaaaaa"<<file<<endl;
        my_strcat(cmd, file);
        cout << "cmd : " << cmd << endl;

        system(cmd);
    }
    else
    {
        cout << "No crawling for this page";
    }
}
void Crawler::checkDirectory()
{
    if (!fs::exists(tarDir))
    {
        if (fs::create_directories(tarDir))
        {
            cout << "created successfully: " << tarDir << endl;
        }
        else
        {
            cout << "Failed to create" << endl;
        }
    }
    else
    {
        cout << "Directory given already exists";
    }
}
int Crawler::checkURL()
{
    char cmd[100];
    cmd[0] = '\0';
    my_strcat(cmd, "wget ");
    my_strcat(cmd, "--spider -q ");
    my_strcat(cmd, URL);
    cout << "cmd for check url: " << cmd << endl;
    if (system(cmd)==0)
    {
        cout << "Reachable url" << endl;
    }
    else
    {
        cout << "Not reachable url" << endl;
        return 0;
    }
    return 1;
}
void Crawler::giveName(char* filename,int len)
{
    char charSet[]="abcdefghigklmnopqrstuvwxyz";
    for(int i=0;i<len-5;i++)
    {
        int index=rand()%25;
        filename[i]=charSet[index];
    }
    filename[len-5]='\0';
    my_strcat(filename,".html");
    cout<<"file name generated is: "<<filename<<endl;
}