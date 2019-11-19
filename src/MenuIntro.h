#pragma once


#include "StateElement.h"
#include "Texture.h"
#include <vector>
#include <string>


//
// Scrolling Text interlude
//
class MenuIntro : public StateElement
{
public:
  MenuIntro();
  ~MenuIntro();

  void draw(RenderSystem* rs, float timer);

  int drawUI();

  int keyCallback(int key, int scancode, int action, int mods);

protected:

  void mainMenu();

  Texture mTexButton;

  std::vector<std::string> messages;
  int message = 0;
  double max_pause = 0.33;
  double pause = 0.02;
  bool pressed = false;

};
