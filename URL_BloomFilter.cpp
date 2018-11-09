#include "BloomFilter.h"
using namespace std;

void Filter_Initialize()
{
    B_Filter.reset();
}

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
