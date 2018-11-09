#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<bits/stdc++.h>
#define n 4588
#define p 0.5
#define e 2.718
using namespace std;
int filtersize;
int *filterArray;
uint32_t murmur(string element)
{
	uint32_t seed = 0; 
	uint32_t hash;
	uint32_t c1 = 0xcc9e2d51;
	uint32_t c2 = 0x1b873593;
	int r1 = 15;
	int r2 = 13;
	int m1 =5;
	uint32_t n1= 0xe6546b64;
	uint32_t k1;

	hash = seed;
	int	length = element.length(); 
	for (int i=0; i<length; i++)
	{
		k1 = element[i];
		k1 *= c1;
		k1 = (k1<<r1) | (k1>>(32-r1));
		k1 *= c2;

		hash = hash^k1;
		hash = (hash << r2) | (hash >> r2);
		hash = hash*m1 + n1;
	}
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;
	return hash%filtersize;
}
int size()
{
	int m = n*abs(log(p)) / pow(log(2),2);
    return m;
}
int Hashfunction()
{
	double k2 = log10(1/p);
    int k = k2/log10(2);
    if(k<2)
    	k=2;
    return k;
}
void addElement(string line)
{
	uint32_t m_hash = murmur(line);
	filterArray[m_hash] = 1;
}
int queryElement(string pass)
{
	int f=0;
	uint32_t m_hash = murmur(pass);
    if(filterArray[m_hash]==1)
    {
    	f=1;
    }
    return f;
}
int main()
{
	ofstream f1;
	ifstream f2;
	ifstream f3;
	string line;
	string pass;
	f2.open("/home/user/Documents/APS_PRoject/weak_passwords.csv");
	cout<<"Enter passowrd to check:";
	cin>>pass;
	int m_array=size();
	int k_array=Hashfunction();
	filtersize=m_array;
	filterArray=new int[filtersize]();
	while(f2)
	{
		getline(f2,line);
		addElement(line);
	}
	int ans=queryElement(pass);
    if(ans==1)
    	cout<<"Password probably exists!";
    else
    	cout<<"New Password!Can proceed further!";

}