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
    
    std::string inputValue;

    unsigned long count;
    while(std::getline(std::cin, inputValue))
    {
       count = 0;
       
       unsigned long value = std::stol(inputValue);
       for(int i = 1; i < value; ++i)
       {
//            std::cout << "\t" << i << "\t" << i+value << "\t" << std::to_string(i^value) << "\n";
            if(i+value == (unsigned long)(i^value)) 
                ++count;
       }
       std::cout << count << "\n";
    }

    return 0;
}



