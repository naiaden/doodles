#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <bitset>
#include <climits>
#include <unordered_map>
#include <math.h>

// https://www.hackerearth.com/problem/algorithm/xor-is-mad-77/
// Count the number of zeros in the binary representation. 2^count-1
// is then the solution...

std::vector< int > get_bits( unsigned long x ) {
    std::string chars( std::bitset< sizeof(long) * CHAR_BIT >( x )
        .to_string( char(0), char(1) ) );
    return std::vector< int >( chars.begin(), chars.end() );
}

int getfirst(std::vector<int> bits)
{
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

    while(std::getline(std::cin, inputValue))
    {
       std::vector<int> vv = get_bits(std::stol(inputValue));
       int count = std::count(vv.begin(), vv.end(), false);
       int first = getfirst(vv);
       
       std::cout << std::fixed << std::setprecision(0) << pow(2, count-first)-1 << "\n";
    }

    return 0;
}



