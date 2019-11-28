#pragma once


#include "Screen.h"
#include "Texture.h"


class ScreenTitle : public Screen
{
public:

  ScreenTitle();
  ~ScreenTitle();

  void draw(RenderSystem* rs, float timer);
  void init(const std::string& filename);

  int keyCallback(int key, int scancode, int action, int mods);
  int gamepadUpdate(double x, double y, int a, int b);
  int drawUI();

protected:

  Texture mTexTitle;

  bool mInfo = false;
  bool mNotInfo = true;

};
