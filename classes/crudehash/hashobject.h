#ifndef _HASHOBJECT_H
#define _HASHOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "php.h"

#ifdef __cplusplus
}
#endif

#include <string>
#include <vector>

class HashObject 
{
public:
  static const size_t HEXBUFFSIZE = 16 + 1;  // 16 hex digits plus null
  HashObject(void);
  virtual ~HashObject(void);

  void mAddString(const char* szString);
  unsigned long mHash(void);
  void mHash(char hexbuff[HEXBUFFSIZE]);

protected:
  std::vector<std::string> mStringList;
};

#endif