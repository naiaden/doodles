#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <bitset>
#include <climits>
#include <unordered_map>


std::vector< int > get_bits( unsigned long x ) {
    std::string chars( std::bitset< sizeof(long) * CHAR_BIT >( x )
        .to_string( char(0), char(1) ) );
    return std::vector< int >( chars.begin(), chars.end() );
}

int getfirst(std::vector<int> bits)
{
//    int i = 0;
    for(int i = 0; i < bits.size(); ++i)
    {
        if(bits[i]) return i;
    }
}

int main(int argc, char *argv[])
{
    unsigned long n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    
    std::string inputValue;

    unsigned long count;
    while(std::getline(std::cin, inputValue))
    {
       
        std::vector<int> vv = get_bits(std::stol(inputValue));
       count = std::count(vv.begin(), vv.end(), false);
       std::cout << count << "\t" << getfirst(vv) << "\t" << count-getfirst(vv) << "\n";
       for(int i : vv)
        std::cout << i << " ";
        std::cout << "\n" << count << "\n\n";
/*       
       unsigned long value = std::stol(inputValue);
       for(int i = 1; i < value; ++i)
       {
//            std::cout << "\t" << i << "\t" << i+value << "\t" << std::to_string(i^value) << "\n";
            if(i+value == (unsigned long)(i^value)) 
                ++count;
       }
*/

    }

    return 0;
}



