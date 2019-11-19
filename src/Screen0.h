#pragma once


#include "Screen.h"
#include "Texture.h"


class Screen0 : public Screen
{
public:

  Screen0();
  ~Screen0();

  void draw(RenderSystem* rs, float timer);
  void init(const std::string& filename);

  int keyCallback(int key, int scancode, int action, int mods);

protected:

  bool mNext = true;
  bool mFree = false;
  bool mChoose = false;

  Texture mTexGround;
  Texture mTexBack;
  Texture mTexTube1;
  Texture mTexTube2;
  Texture mTexProp1;
  Texture mTexPropJournal;
  Texture mTexExit;
  Texture mTexDialog;

  float mYScroll = 0;
  bool mLoop = true;
  float mScrollSpeed = -0.6f;

  double m_frameTimer = 0.0;
};
