#pragma once


#include <vector>
#include <deque>
#include <string>
#include <PlayerController.h>


class GameState
{
public:

  GameState();
  ~GameState();

  void tick();

  int mScore = 0;
  std::string mLetters;

  class Message
  {
  public:
    std::string text;
    float timeLeft = 5.f;
  };
  void addMessage(std::string text);
  std::deque<Message> mMessages;

  bool choose = false;
  bool play = true;

  PlayerController mPlayerController;

protected:

};
