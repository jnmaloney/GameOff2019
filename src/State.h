#pragma once


#include <vector>
#include "StateValueTable.h"


class StateElement;
#include "StateElement.h"


class RenderSystem;


class State
{
public:
  State() {}
  ~State() {}

  void addElement(StateElement* i)
  {
    mElements.push_back(i);
    i->setValueTable(&mValues);
  }

  void keyCallback(int key, int scancode, int action, int mods)
  {
    auto i = mElements.begin();
    while (i != mElements.end() && (*i)->keyCallback(key, scancode, action, mods) == 0)
    {
      ++i;
    }
  }

  void update(double dt)
  {
    auto i = mElements.begin();
    while (i != mElements.end() && (*i)->update(dt) == 0)
    {
      ++i;
    }
  }

  void drawUI()
  {
    auto i = mElements.begin();
    while (i != mElements.end() && (*i)->drawUI() == 0)
    {
      ++i;
    }
  }


  void start()
  {
    for (auto i : mElements)
    {
      i->start();
    }
  }


  //const char* getMessage()
  int getMessage()
  {
    for (auto i = mElements.begin(); i != mElements.end(); ++i)
    {
      if ((*i)->getAdvanceLevel()) return (*i)->getAdvanceLevel();
      if ((*i)->getAdvance()) return 1;
    }

    return 0;
  }


  virtual void draw(RenderSystem* rs, float timer)
  {
    for (auto i = mElements.begin(); i != mElements.end(); ++i)
    {
      (*i)->draw(rs, timer);
    }
  } // ??


protected:

  std::vector<StateElement*> mElements;
  StateValueTable mValues;

};
