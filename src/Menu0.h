#pragma once


#include "StateElement.h"
#include "Texture.h"


class Menu0  : public StateElement
{
public:
  Menu0();
  ~Menu0();
  int drawUI();

  int keyCallback(int key, int scancode, int action, int mods);

protected:

  void mainMenu();

  Texture mTexButton;
};
