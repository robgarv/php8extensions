#include "HoldStructure.h"
#include <sstream>

HoldStructure::HoldStructure() : 
  mValueA(0),
  mValueB(),
  mValueC() 
{ 
  mInit(); 
}

HoldStructure::~HoldStructure() { 
  mClear();
}

void HoldStructure::mSetField(const std::string &fieldName, long value)
{
  std::map<std::string, HoldFieldDef>::iterator it = mFieldDefs.find(fieldName);
  if (it == mFieldDefs.end())
  {
    throw HoldStructureException(fieldName, 
      "The specified field not found (set long field)");
  }
  HoldFieldDef def = it->second;
  // *(def.mFieldPointer.longValue) = value;
  long* ptr = def.mFieldPointer.longValue;
  *ptr = value;
}
void HoldStructure::mSetField(const std::string& fieldName, const std::string& value)
{
  std::map<std::string, HoldFieldDef>::iterator it = mFieldDefs.find(fieldName);
  if (it == mFieldDefs.end())
  {
    throw HoldStructureException(fieldName, 
      "The specified field not found (set string field)");
  }
  HoldFieldDef def = it->second;
  *def.mFieldPointer.stringValue = value;
}

void *HoldStructure::mReadField(const std::string& fieldName, HoldStructureFieldType &type)
{
  std::map<std::string, HoldFieldDef>::iterator it = mFieldDefs.find(fieldName);
  if (it == mFieldDefs.end())
  {
    throw HoldStructureException(fieldName, 
      "The specified field not found (read field)");
  }
  HoldFieldDef def = it->second;
  type = def.mType;
  void *ptr;
  switch(type)
  {
  case longfield:
    ptr = (void*)def.mFieldPointer.longValue;
    break;
  case stringfield:
    ptr = (void*)def.mFieldPointer.stringValue;
    break;
  default:
    throw HoldStructureException(fieldName, "unsupported field type");
  }
  return ptr;
}

void HoldStructure::mInit()
{
  mFieldDefs["ValueA"] = HoldFieldDef("ValueA", &mValueA );
  mFieldDefs["ValueB"] = HoldFieldDef("ValueB", &mValueB);
  mFieldDefs["ValueC"] = HoldFieldDef("ValueC", &mValueC);
}

void HoldStructure::mClear()
{
  mFieldDefs.clear();
}

std::string HoldStructure::mToString()
{
  std::ostringstream buff;
  for( std::map<std::string, HoldFieldDef>::iterator it = mFieldDefs.begin();
    it != mFieldDefs.end(); ++it)
  {
    buff << it->first;
    buff << " => " << it->second.mToString() << std::endl;
  }
  return buff.str();
}

HoldFieldDef::HoldFieldDef(const std::string& fieldName, long* pLong) :
  mFieldName(fieldName),
  mType(longfield)
{  
  mFieldPointer.longValue = pLong;
}
HoldFieldDef::HoldFieldDef(const std::string& fieldName, std::string*pStr) :
  mFieldName(fieldName),
  mType(stringfield)
{ 
  mFieldPointer.stringValue = pStr;
}

std::string HoldFieldDef::mToString()
{
  std::ostringstream buff;

  switch (mType)
  {
  case stringfield:
    buff << *mFieldPointer.stringValue;
    break;
  case longfield:
    buff << *mFieldPointer.longValue;
    break;
  }
  return buff.str();
}