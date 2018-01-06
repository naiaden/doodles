#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <set>

std::size_t genHashValue(const std::set<unsigned int>& inputValues)
{
    std::size_t seed = inputValues.size();
    for(auto& i : inputValues)
    {
        seed ^= i + 0x9e37779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

std::size_t genHashValue2(const std::set<unsigned int>& inputValues)
{
    std::size_t seed = inputValues.size();
    for(auto& i : inputValues)
    {
        seed ^= i + 0x9e37779b9 + (seed << 7) + (seed >> 3);
    }
    return seed;
}

int main(int argc, char *argv[])
{
    unsigned long n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    
    std::string inputValuesString;
    std::getline(std::cin, inputValuesString);
    
    std::vector<unsigned int> inputValues;
    
    std::istringstream iss(inputValuesString);
    unsigned int v;
    while(iss >> v)
    {
        inputValues.push_back(v);
    }
    
    // we have to use two hashes, to reduce the risk of two slices
    // ending up in the same bucket. A minimal perfect hash would
    // have been nice. But that's life (for me).
    std::set<std::pair<std::size_t, std::size_t>> valuesHash;
    
    for(auto i = inputValues.begin(); i !=inputValues.end(); ++i)
    {
        for(auto j = i; j !=inputValues.end(); ++j)
        {
            std::vector<unsigned int> slice(i, j+1);
            std::set<unsigned int> sliceSet(slice.begin(), slice.end());
            valuesHash.insert(std::make_pair(genHashValue(sliceSet), genHashValue2(sliceSet)));
        }
    }

    std::cout << valuesHash.size() << "\n";  
    
    return 0;
}

// https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/practice-problems/algorithm/shubham-and-subarrays-325b1e73/


