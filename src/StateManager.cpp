#include "StateManager.h"
#include "State.h"
#include <stdio.h>
#include <iostream>


StateManager::StateManager()
{

}


StateManager::~StateManager()
{

}


State* StateManager::getCurrentState()
{
  return m_states[mCurrent];
}


void StateManager::update()
{
  if (m_states[mCurrent]->getMessage())
  {
    int m = (int)m_states[mCurrent]->getMessage();
    if (m == 1)
    {
      mCurrent = (mCurrent + 1) % m_states.size();
    }
    else
    {
      mCurrent = (m - 2) % m_states.size();
    }

    m_states[mCurrent]->start();
    std::cout << m << ": " << mCurrent << std::endl;
  }
}
