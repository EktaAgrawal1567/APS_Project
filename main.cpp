//
//  main.cpp
//  Bloom_Filter
//
//  Created by Pranjali Ingole on 29/10/18.
//  Copyright © 2018 Pranjali Ingole. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "BloomFilter.cpp"

#define LEN 3

using namespace std;

/* Vector of pairs of two strings (Long_URL and Short_URL) */
vector < pair <string, string> > URL_DB;
ofstream DBfile;

/* unorder_set of long_url to ensure no duplicate long_urls are accepted i.e. Same long url will not be mapped to different multiple shorten_urls. */
unordered_set <string> Long_URL_list;

/* Converts long_url to short_url by randomly generating string of length LEN containg alphanumeric characters */
string Shorten_url(string long_url)
{
    string short_url = "";
    
    for(int i=1; i<=LEN; i++)
    {
        int num = rand() % 62;
        char c;
        if(num<26)
        {
            c = 'a' + num;
        }
        else if(num<52)
        {
            c = 'A' + (num - 26);
        }
        else
        {
            c = '0' + (num - 52);
        }
        
        short_url += c;
    }

    return short_url;
}

void LoadDBfile(string filename)
{
    ifstream infile ;
    infile.open("URL_DB.txt", std::ios_base::in);
    
    
    string long_url, short_url;
    while(infile>>long_url>>short_url)
    {
        URL_DB.push_back(make_pair(short_url, long_url));
        Long_URL_list.insert(long_url);
    }
}

int main(int argc, const char * argv[])
{
    Filter_Initialize();
    LoadIndices();
    LoadDBfile("URL_DB.txt");
    
    DBfile.open("URL_DB.txt", std::ios_base::app | std::ios_base::out);
    
    while(1)
    {
        string long_url, exit_flag;
        cout<<"Enter URL need to be shortened: "<<endl;
        cin>>long_url;
        
        if(Long_URL_list.insert(long_url).second == false)
        {
            cout<<"Duplicate url. Url id already shorten."<<endl;
            continue;
        }
        else
        {
            Long_URL_list.insert(long_url);
        }
        
        bool filter_flag;
        do
        {
            string short_url = Shorten_url(long_url);
            cout<<short_url<<endl;
            
            filter_flag = Filter_Test(short_url, short_url.length());
            if(!filter_flag)
            {
                cout<<"Shorten URL is unique."<<endl;
                URL_DB.push_back(make_pair(short_url, long_url));
                Filter_Add(short_url, short_url.length());
                DBfile<<long_url<<" "<<short_url<<endl;
                break;
            }
            else
            {
                cout<<"Shorten URL is not unique. Generating again."<<endl;
            }
            
        }while(filter_flag);
        
        
        cout<<"Continue? (Yes/No)"<<endl;
        cin>>exit_flag;
        
        if(exit_flag=="No") break;
    }
    
    DBfile.close();
    
    return 0;
}
