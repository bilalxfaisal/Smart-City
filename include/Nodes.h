#pragma once
#include <iostream>
#include <string>
using namespace std;
namespace HashFuncs
{
    //String Keys
    inline int Polynomial_Rolling_Hash_V1(string& str)
    {
        const int p = 31;
        const int m = 1e9 + 9;
        int hash_value = 0;
        int p_pow = 1;
        for (char c : str) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return static_cast<int>(hash_value);
    }
    inline int Polynomial_Rolling_Hash_V2(string& str)
    {
        const int p = 53;
        const int m = 1e9 + 9;
        int hash_value = 0;
        int p_pow = 1;
        for (char c : str) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return static_cast<int>(hash_value);
    }
    inline int DJB2_Hash(string& str)
    {
        unsigned long hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + c;
        }
        return static_cast<int>(hash);
    }
}

//Hash maps for education sector
