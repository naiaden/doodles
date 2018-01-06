#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <bitset>
#include <unordered_map>

//tail -n 1 851cc5e6ef0111e7.txt.clean.txt| tr ' ' '\n' | sort | uniq -c | sort -r | cut -f7 -d' ' | sort | uniq -c | awk '{if($2>1) print $1*($2*($2-1))/2}' | paste -s -d+ - | bc

int main(int argc, char *argv[])
{
    unsigned long n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    
    std::string inputValues;
    std::getline(std::cin, inputValues);
    
    std::unordered_map<unsigned long, unsigned long> counts;
    std::unordered_map<unsigned long, unsigned long long> countsOfCounts;
    
    std::istringstream iss(inputValues);
    std::string v; 
    while(iss >> v)
    {
        ++counts[std::stoul(v)];
    }

    for(auto i = counts.begin(); i != counts.end(); ++i)
    {
        ++countsOfCounts[i->second];
    }

    unsigned long long results = 0;
    for(auto i = countsOfCounts.begin(); i != countsOfCounts.end(); ++i)
    {
        if(i->first > 1)
            results += i->second * (i->first * (i->first -1))/2;
    }
      
    std::cout << results << "\n";
    
    return 0;
}

// https://www.hackerearth.com/practice/algorithms/sorting/bubble-sort/practice-problems/algorithm/shubham-and-xor-8526868e/


