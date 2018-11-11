# APS_Project

Applications implemented :
  1. URL Shortener: Use Bloom Filter to check uniqueness of shortened URL efficiently for URL shortener.
  2. Weak Password Dictionary
  
# URL SHORTENER:
 
   Code Description: 
   Code is divided in 3 files as below
   
      1. URL_BloomFilter.h : Contains macros definitions and functions declarations of Bloom Filter
      2. URL_BloomFilter.cpp : Contains Bloom Filter data structure and function definitions of it.
      3. URLShortener.cpp : Contains main() with actual workflow and other functions to generate short url.

   Execution Instructions:
      To execute the application, Compile URLShortener.cpp file only.
      File "URL_DB.txt" containing list of tab delimited Long URL and Short URLs should be placed in the same directory as URLShortener.cpp.
      
        1. Input : URL that needs to be shortened [User can give multiple URLs as input one by one, Input "No" to exit]
        2. Output : Unique Short URL.
      
   Variables and Data Structures :
   
        1. LEN : Fixed length of short url [No. of Alphanumeric characters]
        2. N : Size of input data. Here, Short url is consists of alphanumeric characters [A-Z, a-z, 0-9].
               Each character can be one of the 62 alphanumeric symbols. Hence, Maximum possible unique short urls can be 62^LEN.
               N is 62^3 as LEN is 3.
        3. P : Probability of occurrence of false positives acceptable by user. Assumed value of P = 1% [0.01]
        4. M : Size of Bloom Filter BitSet, Calculated maually from above values of P and N.
        5. K : Number of hash fuctions used in Bloom Filter, Calculated maually from above values of P, M and N.
        6. unordered_set <string> Long_URL_list : Set to store long urls that has been converted to short url already to avoid duplicates.
        7. bitset<M> B_Filter : Bitset for Bloom Filter
    
   Workflow:
   
      1. Initialisation of Bloom Filter and Unordered Set of Long URL.
      2. Take Long URL as input from user.
      3. Check if URL is already shortened previously. If yes Go to step 1.
      4. Generate Short URL randomly.
      5. Check if generated Short URL is unique i.e. not present in the URL Database. If not unique using Bloom Filter then Goto step 3.
      6. Add pair of Long URL and randomly generated unique Short URL to URL Database.

  Use of Bloom Filter:
	  Bloom Filter is used for step 4 in above workflow. It is used to check if generated Short URL is unique or not. 
    Bloom Filter will check URL Database and tell whether generated Short URL is already present in URL Database or not efficiently.

      1. Input to Bloom Filter: Short URL 
      2. Output of Bloom Filter: Unique or Not
      3. Calculation of parameters:
            For LEN = 3, N = 238,328 
            Assuming P=1% and using formulae of Bloom Filter, 
            M = 791709 = 800000 approx. and K = 2.3 = 3 approx.
    
   URL Shortener Functions:
   
      1. LoadDBfile(): Initialises unordered set of Long URLs and Bloom Filter. 
                       It reads content of URL Database and inserts Long URLs in unordered set and adds corresponding Short URL in Bloom Filter.
      2. Shorten_url(): Converts long_url to short_url by randomly generating string of length LEN containing alphanumeric characters. 
                        This function generates string of LEN characters where each character is generated randomly from alphanumeric 62 characters.

   Bloom Filter Functions:
   
      1. Filter_Initialize(): Resets Bloom Filter.
      2. Str_Hash(): Hash function designed for Short URL.
      3. K_hash(): Applies 
        Takes integer ‘i’ and 64 bit hash value “HashVal” as input.
        Splits 64 hash value in two 32 bit numbers “Hash1” and “Hash2”.
        Applies double hashing on it and returns result index value as per below formula	
        [ index = (Hash1 + (i * Hash2)) mod M ]
      4. Filter_Add(): Adds Short URL to Bloom Filter by setting appropriate bits at indices obtained by applying K_Hash() on Short URL.
      5. Filter_Test(): Queries Bloom Filter for given Short URL by checking appropriate bits at indices obtained by applying K_Hash() on Short URL.

