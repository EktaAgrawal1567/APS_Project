//
//  BloomFilter.cpp
//  Bloom_Filter
//
//  Created by Pranjali Ingole on 30/10/18.
//  Copyright © 2018 Pranjali Ingole. All rights reserved.
//
#include "BloomFilter.h"
using namespace std;

ofstream Indices;

void Filter_Initialize()
{
    B_Filter.reset();
    Indices.open(Backup_file, std::ios_base::app | std::ios_base::out);
}

/* murmurHash3 can be used instead of this function, Library available in Python and not available in C or C++. Already implemented hash function is available though.*/
uint64_t Str_Hash(string short_url, int url_length)
{
    uint64_t HashVal = 0;
    int Prime_No = 31;
    for(int i=0; i<url_length; i++)
    {
        int ascii_val = 0;
        if(isupper(short_url[i]))
        {
            ascii_val = short_url[i] - 'A';
        }
        else if(islower(short_url[i]))
        {
            ascii_val = short_url[i] - 'a';
        }
        else
        {
            ascii_val = short_url[i] - '0';
        }
        HashVal += ascii_val*(pow(Prime_No,i));
    }
    HashVal %= M;
    
    return HashVal;
}

uint64_t K_hash(int i, uint64_t HashVal)
{
    uint64_t Hash1, Hash2;
    Hash2 = HashVal * 0xFFFF;
    Hash1 = (HashVal >> 32) * 0xFFFF;
    
    return (Hash1 + (i * Hash2))%M;
}

void Filter_Add(string short_url, int url_length)
{
    for(int i=0; i<K; i++)
    {
        uint64_t HashVal = Str_Hash(short_url, url_length);
        uint64_t index = K_hash(i, HashVal);
        B_Filter.set(index);
        Indices<<index<<endl;
    }
}

bool Filter_Test(string short_url, int url_length)
{
    bool flag = true;
    
    for(int i=0; i<K; i++)
    {
        uint64_t HashVal = Str_Hash(short_url, url_length);
        uint64_t index = K_hash(i, HashVal);
   
        if(!B_Filter.test(index))
        {
            flag = false;
            break;
        }
    }
    return flag;
}

void LoadIndices()
{
    ifstream infile ;
    infile.open(Backup_file, std::ios_base::in);
    
    long long index;
    while(infile>>index)
    {
        B_Filter.set(index);
    }
}
