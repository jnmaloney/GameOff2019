#include "MenuIntro0.h"
#include "imgui.h"
#include <string>
#include <iostream>


MenuIntro0::MenuIntro0()
{
  messages.push_back("They tried to transform him into cyborg, which worked almost 90% - operation was not 100% completed -  thus he kept some of his human memories..");
  mTexButton.loadPng("data/img/button_E.png");
}


MenuIntro0::~MenuIntro0()
{

}


int MenuIntro0::drawUI()
{
  if (pause > 0)
    --pause;

  ImGuiIO& io = ImGui::GetIO();

  ImVec2 pos(0.f, 0.f);
  ImVec2 pivot(0, 0);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::SetNextWindowSize(ImVec2(980, 526));
  ImGui::Begin("Title", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  mainMenu();

  ImGui::End();

  return 0;
}


void MenuIntro0::mainMenu()
{
  ImVec4 col(0.65, 0.65, 0.65, 1.0);
  ImGui::PushStyleColor(ImGuiCol_Text, col);
  for (int i = 0; i < message; ++i)
  {
    ImGui::SetCursorScreenPos(ImVec2(32, 526 - (i + 2) * 95 - 75));
    ImGui::TextWrapped("%s", messages[i].c_str());
  }
  ImGui::PopStyleColor();

  ImGui::SetCursorScreenPos(ImVec2(32, 526 - 95 - 75));
  ImGui::TextWrapped("%s", messages[message].c_str());

  if (pause == 0)
  {
    ImGui::SetCursorScreenPos(ImVec2(732, 526 - 70));
    if (message == messages.size() - 1)
      ImGui::TextWrapped("Continue");
    else
      ImGui::TextWrapped("Next");

    ImGui::SetCursorScreenPos(ImVec2(698, 526 - 70));

    if (pressed)
      ImGui::Image(
        (ImTextureID)mTexButton.getID(),
        ImVec2(24, 24),
        ImVec2(0.5, 0),
        ImVec2(1,   1),
        ImColor(255,255,255,255),
        ImColor(0,0,0,0));
    else
      ImGui::Image(
        (ImTextureID)mTexButton.getID(),
        ImVec2(24, 24),
        ImVec2(0,   0),
        ImVec2(0.5, 1),
        ImColor(255,255,255,255),
        ImColor(0,0,0,0));
  }
}


int MenuIntro0::keyCallback(int key, int scancode, int action, int mods)
{
  if (pause > 0) return 0;

  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_E)
    {
      pressed = true;
    }
  }

  if (action == GLFW_RELEASE)
  {
    pressed = false;
    if (key == GLFW_KEY_E)
    {
      ++message;
      if (message == messages.size())
      {
        setAdvanceMessage();
      }
      pause = 40;
    }
  }

  return 0;
}
