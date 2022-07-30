#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

#include "hashobject.h"

HashObject::HashObject(void)
{

}

HashObject::~HashObject(void)
{

}

void HashObject::mAddString(const char* szString )
{
  mStringList.push_back( std::string(szString) );
}

unsigned long HashObject::mHash(void)
{
  std::ostringstream buff;
  for (std::vector<std::string>::iterator it = mStringList.begin();
    it != mStringList.end();
    ++it )
  {
    std::string s = *it;
    buff << s;
  }
  std::hash<std::string> strHash;
  size_t code = strHash(buff.str());
  return (unsigned long)code;
}

void HashObject::mHash(char hexBuff[HEXBUFFSIZE])
{
  unsigned long hashCode = mHash();
  std::ostringstream buff;
  buff << std::hex << hashCode;
  memset(hexBuff, 0, HEXBUFFSIZE);
  strncpy(hexBuff, buff.str().c_str(), HEXBUFFSIZE - 1);
}
