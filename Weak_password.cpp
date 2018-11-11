#include "Weak_password.h"
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
uint32_t fnv(string element)
{
	uint32_t fnv_prime=16777619;
	uint32_t fnv_offset = 2166136261;
	int n2 =element.length();
	uint32_t hash = 0;

	hash = fnv_offset;
	for (int i=0; i<n2; i++)
	{
		hash = hash^element[i];
		hash = hash*fnv_prime;
	}

	return hash%filtersize;
}
double size(double k)
{
	double m = (n*k)/0.693;
    return m;
}
double probability(double m,double k)
{
	double p1,p2,p3,p4,p5;
	p1=(1-(1/m));
	p3=k*n;
	p2=pow(p1,p3);
	p4=1-p2;
	p5=pow(p4,k);
	return p5;
}
void addElement(string line)
{
	uint32_t m_hash = murmur(line);
	uint32_t f_hash = fnv(line);
	filterArray[m_hash] = 1;
	filterArray[f_hash]=1;
}
int queryElement(string pass)
{
	int f=0;
	uint32_t m_hash = murmur(pass);
	uint32_t f_hash =fnv(pass);
    if(filterArray[m_hash]==1 && filterArray[f_hash]==1)
    {
    	f=1;
    }
    return f;
}
int main()
{
	double k;
	ofstream f1;
	ifstream f2;
	ifstream f3;
	string line;
	string pass;
	f2.open("/home/user/Documents/APS_PRoject/weak_passwords.csv");
	cout<<"Enter passowrd to check:";
	cin>>pass;
	k=6;
	double m=size(k);
    double p=probability(m,k);
	filtersize=m;
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