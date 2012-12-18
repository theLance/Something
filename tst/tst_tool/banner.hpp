#include <iostream>
#include <iomanip>
#include <string>

void banner( const std::string name )
{
  size_t half = name.size() / 2;
  std::cout << std::endl << "[" << std::setw( 30 - half ) << std::setfill('-') << "-"
            << std::left << std::setw( 30 + half ) << std::setfill('-') << name << "]"
            << std::endl;
}

