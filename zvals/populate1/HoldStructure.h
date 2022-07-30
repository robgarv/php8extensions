#ifndef _HOLD_STRUCTURE_H
#define _HOLD_STRUCTURE_H

#include <string>
#include <sstream>
#include <map>

class HoldStructureException
{
  public:
    std::string mFieldName;
    std::string mMessage;
    HoldStructureException(const std::string &fieldName, const std::string& Message) :
      mFieldName(fieldName),
      mMessage(mMessage)
    { ; }
    virtual ~HoldStructureException() { ; }

    std::string mFormat()
    {
      std::ostringstream buff;
      buff << "Field [" << mFieldName << "] error: " << mMessage;
      return buff.str();
    }
};

typedef enum {
  stringfield = 1,
  longfield
} HoldStructureFieldType;


struct HoldFieldDef {
  std::string mFieldName;
  HoldStructureFieldType mType;
  union uFieldPointer
  {
    long *longValue;
    std::string *stringValue;
  } mFieldPointer;

  HoldFieldDef(void) {;}
  HoldFieldDef(const std::string& fieldName, long* pLong);
  HoldFieldDef(const std::string& fieldName, std::string* pStr) ;
  virtual ~HoldFieldDef() { ; }
  
  std::string mToString();
  void operator=(const HoldFieldDef &d)
  {
    mFieldName = d.mFieldName;
    mType = d.mType;
    mFieldPointer = d.mFieldPointer;
  }
};

// A very crude container structure. It holds a long and two strings
struct HoldStructure
{

  long mValueA;
  std::string mValueB;
  std::string mValueC;

  HoldStructure();
  virtual ~HoldStructure();

  void mSetField(const std::string &fieldName, long value);
  void mSetField(const std::string &fieldName, const std::string& value);
  void *mReadField(const std::string& fieldName, HoldStructureFieldType& type);
  std::string mToString();
  std::map<std::string, HoldFieldDef> mFieldDefs;

protected:

  void mInit();
  void mClear();
};

#endif