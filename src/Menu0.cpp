#include "Menu0.h"
#include "imgui.h"
#include <string>
#include <iostream>


Menu0::Menu0()
{
  mTexButton.loadPng("data/img/button_E.png");
}


Menu0::~Menu0()
{

}


int Menu0::drawUI()
{
  ImGuiIO& io = ImGui::GetIO();

  ImVec2 pos(0.f, 0.f);
  ImVec2 pivot(0, 0);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::SetNextWindowSize(ImVec2(960, 600));
  ImGui::Begin("Title", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  if (mStateValues->getValue("menu").flags == 1)
  {
    mainMenu();
  }

  if (mStateValues->getValue("can_pick_journal").flags == 1)
  {
    ImGui::SetCursorScreenPos(ImVec2(150 * 4 - 29, 36 * 4 + 1));
    ImGui::Image(
      (ImTextureID)mTexButton.getID(),
      ImVec2(24, 24),
      ImVec2(0,   0),
      ImVec2(0.5, 1),
      ImColor(255,255,255,255),
      ImColor(0,0,0,0));
    ImGui::SetCursorScreenPos(ImVec2(150 * 4, 36 * 4));
    ImGui::Text("Pick up journal");
  }

  if (mStateValues->getValue("can_exit").flags == 1)
  {
    ImGui::SetCursorScreenPos(ImVec2(47 * 4 - 29, 36 * 4 + 1));
    ImGui::Image(
      (ImTextureID)mTexButton.getID(),
      ImVec2(24, 24),
      ImVec2(0,   0),
      ImVec2(0.5, 1),
      ImColor(255,255,255,255),
      ImColor(0,0,0,0));
    ImGui::SetCursorScreenPos(ImVec2(47 * 4, 36 * 4));
    ImGui::Text("Exit");
  }

  ImGui::End();

  return 0;
}


void Menu0::mainMenu()
{
  ImVec2 pos;
  ImVec2 pivot(0, 0);

  pos = ImVec2(2.2 * 16 * 4.f, 0.5 * 16 * 4.f);
  ImGui::SetCursorScreenPos(pos);
  ImGui::Text("Your mission...");

  pos = ImVec2(9 * 16 * 4.f, 1.5 * 16 * 4.f);
  ImGui::SetCursorScreenPos(pos);
  ImGui::Text("(Z) - Accept        (X) - Ignore");

}


int Menu0::keyCallback(int key, int scancode, int action, int mods)
{
  if (mStateValues->getValue("menu").flags == 1)
  {
    if (action == GLFW_PRESS)
    {
      // Z - Next clone
      if (key == GLFW_KEY_Z)
      {
        mStateValues->setValue("next", 1, 0);
        mStateValues->setValue("menu", 0, 0);
      }

      // X - Free this clone
      if (key == GLFW_KEY_X)
      {
        mStateValues->setValue("free", 1, 0);
        mStateValues->setValue("menu", 0, 0);
      }
    }
  }

  return 0;
}
