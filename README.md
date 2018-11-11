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
	
# PREVENTING WEAK PASSWORD:

   Code Description: 
   Code is divided in 2 files as below
   
      1. Weak_password.h : Contains macros definitions and functions declarations of Bloom Filter
      2. Weak_password.cpp : Contains Bloom Filter data structure and function definitions of it.
      
   Execution Instructions:
      To execute the application, Compile Weak_password.cpp file only.
        
        1. Input : User password
        2. Output : Whether the password is weak or not.
	
     

      
   
