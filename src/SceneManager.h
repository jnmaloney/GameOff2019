#pragma once


#include "Screen.h"
#include "Texture.h"


class RenderSystem;
class GameState;


class SceneManager
{
public:

  SceneManager();
  ~SceneManager();

  void init();

  void setScreen(int i);
  int getScreen();

  void draw(RenderSystem* rs);

  GameState* gs = 0;

protected:

  int m_screen = 0;

  std::vector<Screen> m_screens;

  Texture g_texture;

  void drawState(RenderSystem* rs);

};
