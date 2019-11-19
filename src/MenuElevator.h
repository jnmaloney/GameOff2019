#pragma once


#include "StateElement.h"
#include "Texture.h"


class MenuElevator  : public StateElement
{
public:
  MenuElevator();
  ~MenuElevator();
  int drawUI();

  int keyCallback(int key, int scancode, int action, int mods);

protected:

  void mainMenu();
};
