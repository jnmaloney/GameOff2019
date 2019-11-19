#pragma once


#include "Screen.h"
#include "Texture.h"
#include "PhysicsLevel2D.h"
#include "PlayerController.h"


// Just a fixed screen showing the player
class ScreenPlayerFixed : public Screen
{
public:

  ScreenPlayerFixed();
  ~ScreenPlayerFixed();

  void draw(RenderSystem* rs, float timer);
  void init();
  int keyCallback(int key, int scancode, int action, int mods);

protected:

  PhysicsLevel2D mPhysicsLevel;
  PlayerController mPlayerController;

  Texture mTexCharacter;
};
