#include "MenuElevator.h"
#include "imgui.h"
#include <string>
#include <iostream>


MenuElevator::MenuElevator()
{
}


MenuElevator::~MenuElevator()
{

}


int MenuElevator::drawUI()
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


void MenuElevator::mainMenu()
{
  if (mAdvanceLevel) return;

  ImVec2 pos;
  ImVec2 pivot(0, 0);

  pos = ImVec2(2.2 * 16 * 4.f, 0.5 * 16 * 4.f);
  ImGui::SetCursorScreenPos(pos);
  ImGui::Text("Elevator...");


  for (int i = 0; i < 8; ++i)
  {
    int x = (i % 2) * 100 + 410;
    int y = (i / 2) * -100 + 410;
    pos = ImVec2((float)x, (float)y);
    ImGui::SetCursorScreenPos(pos);

    char buffer [50];
    int n, a=5, b=3;
    n=sprintf (buffer, "[%i]", i + 1);
    if (ImGui::Button(buffer, ImVec2(64.f, 64.f)))
    {
      mAdvanceLevel = 2 + i + 1;
      break;
    }
  }
}


int MenuElevator::keyCallback(int key, int scancode, int action, int mods)
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
