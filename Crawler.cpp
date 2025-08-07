#include <iostream>
#include "./Crawler.h"
#include "./stringHeader.h"
#include <stdlib.h>
#include <filesystem>
#include "./LinkedListHeader.h"

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
void Crawler::downloadHTML(char *url, int depth, int curr_depth, int linkCount)
{
    if (curr_depth >= depth)
    {
        cout << "Reached Max depth returning back" << endl;
        return;
    }
    cout << "[Download for url: ]" << url << endl;
    char *dummy;
    if (urlMap.search(url, dummy))
    {
        cout << "Already processed: " << url << endl;
        return;
    }
    char cmd[100];
    cmd[0] = '\0';
    char file[15];
    giveName(file, 15);
    if (checkURL(url))
    {
        checkDirectory();
        char *fullPath = new char[200];
        fullPath[0] = '\0';
        my_strcat(fullPath, tarDir);
        my_strcat(fullPath, "/");
        my_strcat(fullPath, file);
        insertUrl(url,fullPath);
        cout << "hello" << endl;
        my_strcat(cmd, "wget -q ");
        my_strcat(cmd, url);
        my_strcat(cmd, " -O ");
        my_strcat(cmd, tarDir);
        my_strcat(cmd, "/");
        my_strcat(cmd, file);
        cout << "cmd : " << cmd << endl;
        system(cmd);
        cout << "Calling extractUrls with filePath: " << fullPath << endl;
        if (!fs::exists(fullPath))
            cout << "File does not exist!" << endl;
        extractUrls(fullPath, depth, curr_depth, linkCount);
        delete[] fullPath;
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
int Crawler::checkURL(char *testURL)
{
    char cmd[100];
    cmd[0] = '\0';
    my_strcat(cmd, "wget ");
    my_strcat(cmd, "--spider -q ");
    my_strcat(cmd, testURL);
    cout << "cmd for check url: " << cmd << endl;
    if (system(cmd) == 0)
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
void Crawler::giveName(char *filename, int len)
{
    char charSet[] = "abcdefghijklmnopqrstuvwxyz";
    int i;
    for (i = 0; i < len - 6; i++)
    {
        int index = rand() % 25;
        filename[i] = charSet[index];
    }
    filename[i] = '\0';
    my_strcat(filename, ".html");
    cout << "file name generated is: " << filename << endl;
}
void Crawler ::extractUrls(char *filepath, int depth, int currDepth, int linkCount)
{
    if (currDepth > depth)
    {
        cout << "Reached Max depth returning back" << endl;
        return;
    }
    cout << "filePath : " << filepath << endl;
    char *buffer = readFile(filepath);

    if (buffer == nullptr)
    {
        cout << "File not found" << endl;
        return;
    }
    // cout << "file : " << buffer << endl;
    char *searchPosition = buffer;
    char *ahrefPos = nullptr;
    int currPageCount = 0;
    while ((ahrefPos = my_strstr(searchPosition, "<a href=\"http")) != nullptr && currPageCount < linkCount)
    {
        char *qStart = my_strstr(ahrefPos, "\"");
        if (qStart == nullptr)
            break;

        char *qEnd = my_strstr(qStart + 1, "\"");
        if (qEnd == nullptr)
            break;

        int len = qEnd - qStart - 1;
        if (len > MAX_LEN)
            len = MAX_LEN - 1;
        char *url = new char[MAX_LEN];
        int i = 0;
        while (i < len)
        {
            url[i] = qStart[i + 1];
            i++;
        }
        url[len] = '\0';
        cout << "url : " << url << endl;
        cout << "calling crawl for url : " << url << endl;
        downloadHTML(url, depth, currDepth + 1, linkCount);
        currPageCount++;
        searchPosition = qEnd + 1;
        delete[] url;
    }
    // abhi ke liye relative check krne ko likh ri
    searchPosition = buffer;
    while ((ahrefPos = my_strstr(searchPosition, "<a href=\"/")) != nullptr && currPageCount < linkCount)
    {
        char *qStart = my_strstr(ahrefPos, "\"");
        if (qStart == nullptr)
            break;

        char *qEnd = my_strstr(qStart + 1, "\"");
        if (qEnd == nullptr)
            break;

        int len = qEnd - qStart - 1;
        if (len > MAX_LEN)
            len = MAX_LEN - 1;
        char *url = new char[MAX_LEN];
        int i = 0;
        while (i < len)
        {
            url[i] = qStart[i + 1];
            i++;
        }
        url[len] = '\0';
        char *finalUrl = new char[MAX_LEN];
        my_strcpy(finalUrl, URL);
        int baseLen = my_strlen(finalUrl);
        if (baseLen > 0 && finalUrl[baseLen - 1] == '/')
        {
            finalUrl[baseLen - 1] = '\0';
        }
        my_strcat(finalUrl, url);
        cout<<"Relative url ye tha: "<<url<<endl;
        cout << "url after making it absolute: " << finalUrl << endl;
        cout << "calling crawl for url : " << finalUrl << endl;
        downloadHTML(finalUrl, depth, currDepth + 1, linkCount);
        currPageCount++;
        searchPosition = qEnd + 1;
        delete[] url;
        delete[] finalUrl;
    }
    cout << "no nested links found" << endl;
    delete[] buffer;
}

void Crawler::insertUrl(char *url , char* fullPath)
{
    char *urlStore = new char[my_strlen(url) + 1];
    char* fullPathStore = new char[my_strlen(fullPath)+1];
    my_strcpy(urlStore, url);
    my_strcpy(fullPathStore,fullPath);
    char *dummyOut = nullptr;
    if (urlMap.search(urlStore, dummyOut))
    {
        cout << "URL already exists (skipping): " << url << endl;
        delete[] urlStore;
        delete[] fullPathStore;
        return;
    }
    urlList.addAtLast(urlStore);
    urlMap.insert(urlStore, fullPathStore);
    cout << "url inserted: " << url << endl;
    cout << "endl" << endl;
    cout << "[insertUrl] this: " << this << endl;
}
void Crawler::displayURLs()
{
    cout << "These are urls inside linked list urlList: " << endl;
    urlList.display();
    cout<<endl;
    cout<<"------Now in hash------"<<endl;
    urlMap.display();
    cout << "[displayURLs] this: " << this << endl;
}
void Crawler::wordsExtracted()
{
    urlMap.traverse();
}