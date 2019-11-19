#include "GameState.h"
#include "Random.h"
#include <stdio.h>
#include <string.h>
#include <iostream>


GameState::GameState()
{

}


GameState::~GameState()
{

}


void GameState::tick()
{
  //
  // Msg
  //
  if (mMessages.size())
  {
    mMessages[0].timeLeft -= 1.f;
    while (mMessages[0].timeLeft <= 0.f)
    {
      mMessages.pop_front();
    }
  }

  //
  //  Init
  //

}


void GameState::addMessage(std::string text)
{
  Message m;
  m.text = text;
  if (mMessages.size()) m.timeLeft = 0;
  mMessages.push_back(m);
}
