#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <bitset>
#include <unordered_map>

int main(int argc, char *argv[])
{
    unsigned long n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    
    std::string inputValues;
    std::getline(std::cin, inputValues);
    
    std::unordered_map<std::bitset<32>, unsigned long> m;
    std::istringstream iss(inputValues);
    std::string v;
    while(iss >> v)
    {
        ++m[std::bitset<32>(std::stoul(v))];
    }

    unsigned results = 0;
    for(auto i = m.begin(); i != m.end(); ++i)
    {
        for(auto j = i; j != m.end(); ++j)
        {
            if(!(i->first ^ j->first).count())
            {
                if( i==j)
                    results += ((i->second-1) * (j->second-1));                
                else
                    results += (i->second * j->second);
            }
        }
    }
      
    std::cout << results << "\n";
    
    return 0;
}

// https://www.hackerearth.com/practice/algorithms/sorting/bubble-sort/practice-problems/algorithm/shubham-and-xor-8526868e/


