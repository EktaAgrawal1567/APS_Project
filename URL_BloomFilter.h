
#ifndef BloomFilter_h
#define BloomFilter_h

#include <stdio.h>
#include <bitset>
#include <string>
#include <cmath>
#include <ctype.h>
#include <fstream>

#define M 800000
#define K 3

using namespace std;

bitset<M> B_Filter;

void Filter_Initialize();
uint64_t Str_Hash(string short_url, int url_length);
uint64_t K_hash(int i, uint64_t HashVal);
void Filter_Add(string short_url, int url_length);
bool Filter_Test(string short_url, int url_length);

#endif /* BloomFilter_h */
