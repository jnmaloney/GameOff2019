#pragma once


#include "Screen.h"
#include "Texture.h"
#include "TileLevel.h"
#include "PlayerController.h"
#include "Enemy.h"


class Screen1 : public Screen
{
public:

  Screen1();
  ~Screen1();

  void draw(RenderSystem* rs, float timer);
  void init(const std::string& filename);

  int keyCallback(int key, int scancode, int action, int mods);
  int gamepadUpdate(double x, double y, int a, int b);

  int drawUI();

  TileLevel mLevel;


    void prestart(RenderSystem* rs);


protected:

  Texture mTexGround;
  Texture mTexPickup;
  Texture mTexCollectEffect;
  Texture mTexBack;
  PlayerController mPlayerController;

  glm::vec3 mCameraHistory[4];
  glm::vec3 mCameraPos;
  glm::vec3 mCameraPos2;

  int m_score = 0;
  float m_timer = 0.f;
  int m_mins = 0;

  float stamina = 1.0f;

  class PickUp
  {
  public:
    float x;
    float y;
    int picked;
    int info;
    float timer = 75.f / 12.f;
  };
  PickUp m_pickups[3];
};
