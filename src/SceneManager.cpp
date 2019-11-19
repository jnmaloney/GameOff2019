#include "SceneManager.h"
#include "RenderSystem.h"
#include "GameState.h"
#include "Random.h"


SceneManager::SceneManager()
{

}

void SceneManager::init()
{
}


SceneManager::~SceneManager()
{

}


void SceneManager::setScreen(int i)
{
  m_screen = i;
}


int SceneManager::getScreen()
{
  return m_screen;
}


void SceneManager::draw(RenderSystem* rs)
{
  rs->start();
  g_texture.bind();

  // Screen
  //m_screens[m_screen].draw(rs);

  // Game State...
  drawState(rs);

  rs->end();
}


void SceneManager::drawState(RenderSystem* rs)
{
  // glm::mat4 mvp(1.0);
  // RenderQueue rq;
  //
  // rq.draw(rs);
}
