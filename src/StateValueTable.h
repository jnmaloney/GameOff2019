#pragma once


#include <string>
#include <map>


class StateValue
{
public:
  StateValue() {}
  ~StateValue() {}

  bool set = false;
  int flags = 0;
  double value = 0;
};


class StateValueTable
{
public:
  StateValueTable() {}
  ~StateValueTable() {}

  StateValue getValue(std::string name)
  {
    StateValue valueCopy = mValues[name];
    mValues[name].set = false;
    return valueCopy;
  }

  void setValue(std::string name, int flags, double value)
  {
    mValues[name].flags = flags;
    mValues[name].value = value;
    mValues[name].set = true;
  }

protected:

  std::map<std::string, StateValue> mValues;
};
