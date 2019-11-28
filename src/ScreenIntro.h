#pragma once


#include "Screen.h"
#include "Texture.h"


class ScreenIntro : public Screen
{
public:

  ScreenIntro();
  ~ScreenIntro();

  void draw(RenderSystem* rs, float timer);
  void init(const std::string& filename);

  int keyCallback(int key, int scancode, int action, int mods);
  int gamepadUpdate(double x, double y, int a, int b);
  int drawUI();

protected:

  Texture mTex1;
  Texture mTex2;
  Texture mTex3;
  Texture mTex4;

  int mPage = 0;
  float mTimer = 10.f;

};
