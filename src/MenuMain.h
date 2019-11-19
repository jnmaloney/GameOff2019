#pragma once


#include "StateElement.h"
#include "Texture.h"


//
// Main Menu state
//
class MenuMain : public StateElement
{
public:
  MenuMain();
  ~MenuMain();

  int drawUI();
  int keyCallback(int key, int scancode, int action, int mods);

protected:

  void mainMenu();

  int selected = 0;
  bool press = false;

  Texture mBackground;
  Texture mButtonPlay;
  Texture mButtonPlaySelected;
  Texture mButtonPlayPressed;
  Texture mButtonQuit;
  Texture mButtonQuitSelected;
  Texture mButtonQuitPressed;

};
