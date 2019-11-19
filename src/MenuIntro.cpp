#include "MenuIntro.h"
#include "imgui.h"
#include <string>
#include <iostream>


MenuIntro::MenuIntro()
{
  messages.push_back("In the operation room, many humans are being about to become cyborgs.");
  messages.push_back("an ordinary human before, he was invited to work at this company that promised him a higher salary and a lot of special technology to work with, but he didn't know what he was hired for...until he was forced inside a tube for experimentation.");
  //messages.push_back("They tried to transform him into cyborg, which worked almost 90%% - operation was not 100%% completed -  thus he kept some of his human memories..");
  mTexButton.loadPng("data/img/button_E.png");
}


MenuIntro::~MenuIntro()
{

}


void MenuIntro::draw(RenderSystem* rs, float timer)
{
  if (pause > 0)
  {
    pause -= timer;
  }
  else pause = 0;
}


int MenuIntro::drawUI()
{
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


void MenuIntro::mainMenu()
{
  ImVec4 col(0.65, 0.65, 0.65, 1.0);
  col.x = (1.0 - pause/max_pause) * col.x + (pause/max_pause);
  col.y = (1.0 - pause/max_pause) * col.y + (pause/max_pause);
  col.z = (1.0 - pause/max_pause) * col.z + (pause/max_pause);
  ImGui::PushStyleColor(ImGuiCol_Text, col);
  for (int i = 0; i < message; ++i)
  {
    ImGui::SetCursorScreenPos(ImVec2(32, 526 - (message - i + 1 - pause/max_pause) * 95 - 75));
    ImGui::TextWrapped("%s", messages[i].c_str());
  }
  ImGui::PopStyleColor();

  if (pause == 0)
  {
    if (message == messages.size())
    {
      setAdvanceMessage();
      return;
    }
    ImGui::SetCursorScreenPos(ImVec2(32, 526 - 95 - 75));
    ImGui::TextWrapped("%s", messages[message].c_str());
  }

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


int MenuIntro::keyCallback(int key, int scancode, int action, int mods)
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
      // if (message == messages.size())
      // {
      //   setAdvanceMessage();
      // }
      pause = max_pause;
    }
  }

  return 0;
}
