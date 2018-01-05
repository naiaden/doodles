#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <bitset>

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

    unsigned results = 0;
    for(size_t i = 0; i < a.size(); ++i)
    {
        for(size_t j = i+1; j < a.size(); ++j)
        {
            if(!(a[i] ^ a[j]).count())
            {
                ++results;
            }
        }
    }
    
    std::cout << results << "\n";
    
    return 0;
}

// https://www.hackerearth.com/practice/algorithms/sorting/bubble-sort/practice-problems/algorithm/shubham-and-xor-8526868e/


