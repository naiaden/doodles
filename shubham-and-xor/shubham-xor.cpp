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
    
    std::vector<std::bitset<32>> a;
    std::istringstream iss(inputValues);
    std::transform(std::istream_iterator<std::string>(iss),
                   std::istream_iterator<std::string>{},
                   std::back_inserter(a),
                   [](const auto& v){ return std::bitset<32>(std::stoul(v)); });

//    std::sort(a.begin(), 
//              a.end(), 
//              [](const auto & lhs, const auto & rhs){ return lhs.to_string() < rhs.to_string(); });

    std::unordered_map<std::bitset<32>, unsigned long> m;
    for(const auto& v: a)
    {
        ++m[v];
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


