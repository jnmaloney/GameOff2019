#pragma once


#include <vector>


class State;


class StateManager
{
public:

  StateManager();
  ~StateManager();

  //void init(const char* sourceFile);

  State* getCurrentState();

  void addState(State* s) { m_states.push_back(s); }

  void update();

  //void serialize(...)
  //{
  //
  //}

protected:

  std::vector<State*> m_states;

  int mCurrent = 0;
};
