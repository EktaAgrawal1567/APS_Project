//
//  BloomFilter.h
//  Bloom_Filter
//
//  Created by Pranjali Ingole on 04/11/18.
//  Copyright © 2018 Pranjali Ingole. All rights reserved.
//

#ifndef BloomFilter_h
#define BloomFilter_h

#include <stdio.h>
#include <bitset>
#include <string>
#include <cmath>
#include <ctype.h>

#define M 1559100
#define K 4

using namespace std;
bitset<M> B_Filter;

void Filter_Initialize();
uint64_t Str_Hash(string short_url, int url_length);
uint64_t K_hash(int i, uint64_t HashVal);
void Filter_Add(string short_url, int url_length);
bool Filter_Test(string short_url, int url_length);

#endif /* BloomFilter_h */
