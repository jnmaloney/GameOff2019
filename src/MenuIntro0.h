#pragma once


#include "StateElement.h"
#include "Texture.h"
#include <vector>
#include <string>


//
// Scrolling Text interlude
//
class MenuIntro0 : public StateElement
{
public:
  MenuIntro0();
  ~MenuIntro0();
  int drawUI();

  int keyCallback(int key, int scancode, int action, int mods);

protected:

  void mainMenu();

  Texture mTexButton;

  std::vector<std::string> messages;
  int message = 0;
  double pause = 40;
  bool pressed = false;

};
