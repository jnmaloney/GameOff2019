#pragma once


#include "StateElement.h"
#include "Texture.h"
#include "PhysicsLevel2D.h"
#include "RenderQueue.h"


class Enemy  //: public StateElement
{
public:
  Enemy(PhysicsLevel2D* level, float x, float y);
  ~Enemy();

  int update(double dt);
  void draw(RenderSystem* rs, float timer);
  int drawUI();

  int keyCallback(int key, int scancode, int action, int mods);

protected:

  Texture mTexCharacter;
  RenderQueue mQueue;

  void mainMenu();

  btCollisionObject* mObject;

  float m_frameTimer = 0.f;
};
