#pragma once


#include <vector>
#include "StateValueTable.h"


class RenderSystem; // ??


class StateElement
{
public:

  StateElement() {}
  virtual ~StateElement() {}

  virtual void init2() {}

  virtual int keyCallback(int key, int scancode, int action, int mods) { return 0; }

  virtual int update(double dt) { return 0; }

  virtual int drawUI() { return 0; }

  //void serialize(...)
  //{
  //
  //}

  void start() { mAdvance = false; mAdvanceLevel = 0; }
  int getAdvanceLevel() { return mAdvanceLevel; }
  bool getAdvance() { return mAdvance; }

  virtual void draw(RenderSystem* rs, float timer) {} // ??

  void setValueTable(StateValueTable* valuesPtr) { mStateValues = valuesPtr; }

protected:

  void setAdvanceMessage() { mAdvance = true; }

  // A table shared by all elements of a state
  StateValueTable* mStateValues = 0;

  // Signals the state to finish
  int mAdvanceLevel = 0;

private:

  // Signals the state to finish
  bool mAdvance = false;
};
