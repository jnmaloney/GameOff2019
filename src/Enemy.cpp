#include "Enemy.h"
#include "imgui.h"
#include "PhysicsLevel2D.h"
#include <string>
#include <iostream>


Enemy::Enemy(PhysicsLevel2D* level, float x, float y)
{
  mObject = level->addPickup(x, y, x + 19, x + 34, this);
  mTexCharacter.loadPng("data/img/enemy_4/enemy_4_idle.png");

  mQueue.x_res = 267.0f / 89.0f;
  mQueue.y_res = 174.0f / 87.0f;
  mQueue.mod_vert = 2;
  mQueue.div_vert = 3;
}


Enemy::~Enemy()
{

}


int Enemy::drawUI()
{
  ImGuiIO& io = ImGui::GetIO();

  ImVec2 pos(0.f, 0.f);
  ImVec2 pivot(0, 0);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::SetNextWindowSize(ImVec2(960, 600));
  ImGui::Begin("Title", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    mainMenu();

  ImGui::End();

  return 0;
}


void Enemy::mainMenu()
{
  ImVec2 pos;
  ImVec2 pivot(0, 0);

  pos = ImVec2(2.2 * 16 * 4.f, 0.5 * 16 * 4.f);
  ImGui::SetCursorScreenPos(pos);
  ImGui::Text("Enemy... %i, %i",
    (int)mObject->getWorldTransform().getOrigin().x(),
    (int)mObject->getWorldTransform().getOrigin().y()
    );

}


int Enemy::keyCallback(int key, int scancode, int action, int mods)
{
  // if (mStateValues->getValue("menu").flags == 1)
  // {
  //   if (action == GLFW_PRESS)
  //   {
  //     // Z - Next clone
  //     if (key == GLFW_KEY_Z)
  //     {
  //       mStateValues->setValue("next", 1, 0);
  //       mStateValues->setValue("menu", 0, 0);
  //     }
  //
  //     // X - Free this clone
  //     if (key == GLFW_KEY_X)
  //     {
  //       mStateValues->setValue("free", 1, 0);
  //       mStateValues->setValue("menu", 0, 0);
  //     }
  //   }
  // }

  return 0;
}


int Enemy::update(double dt)
{
  // Walk

  // Attack

  return 0;
}


void Enemy::draw(RenderSystem* rs, float dt)
{
  m_frameTimer += dt;
  if (m_frameTimer > 240.0) m_frameTimer -= 240;
  float timer = m_frameTimer;

  float x, y;
  x = mObject->getWorldTransform().getOrigin().x();
  y = mObject->getWorldTransform().getOrigin().y() - 52;
  float z = 0.f;
  int t = 1 + ((int)(timer * 12.f)) % 5;

  glm::mat4 mvp(1.0);
  mvp = glm::mat4(1.0);

  mvp = glm::translate(mvp,
    glm::vec3(
      x,
      y,
      z));

  mvp = glm::scale(mvp,
    glm::vec3(
      82.f,
      82.f,
      1.0f));

        // if (mFacingRight == false)
        // {
        //   mvp = glm::scale(mvp,
        //     glm::vec3(
        //       -1.f,
        //        1.f,
        //        1.f));
        // }
  // center point
  mvp = glm::translate(mvp,
    glm::vec3(
     -0.5f,
      0,
      0));

  mQueue.clear();
  mQueue.setTile(t);
  mQueue.setMVP(mvp);
  mQueue.submit();

  mTexCharacter.bind();
  mQueue.draw(rs);
}
