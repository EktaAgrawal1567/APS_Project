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
#include <algorithm>
#include "BloomFilter.cpp"

#define LEN 3

using namespace std;

/* Vector of pairs of two strings (Long_URL and Short_URL) */
vector < pair <string, string> > URL_DB;

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

int main(int argc, const char * argv[])
{
    Filter_Initialize();
    
    while(1)
    {
        string long_url, exit_flag;
        cout<<"Enter URL need to be shortened: "<<endl;
        cin>>long_url;
        
        bool filter_flag = true;
        
        while(filter_flag)
        {
            string short_url = Shorten_url(long_url);
            cout<<short_url<<endl;
            Filter_Add(short_url, short_url.length());
            
            filter_flag = Filter_Test(short_url, short_url.length());
            if(filter_flag)
            {
                cout<<"Shorten URL is unique."<<endl;
                URL_DB.push_back(make_pair(short_url, long_url));
                break;
            }
            else
            {
                cout<<"Shorten URL is not unique. Generating again."<<endl;
            }
        }
        
        
        cout<<"Continue? (Yes/No)"<<endl;
        cin>>exit_flag;
        
        if(exit_flag=="No") break;
    }
    
    return 0;
}
