#include "MenuLaunch.h"
#include "WindowManager.h"
#include "imgui.h"
#include <string>
#include "SceneManager.h"
#include "GameState.h"
#include <stdio.h>
#include <string.h>
#include <iostream>


MenuLaunch::MenuLaunch()
{
}


MenuLaunch::~MenuLaunch()
{

}


void MenuLaunch::frame()
{
  WindowManager& window = *WindowManager::getInstance();
  ImGuiIO& io = ImGui::GetIO();

  ImVec2 pos(0.f, 0.f);
  ImVec2 pivot(0, 0);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::SetNextWindowSize(ImVec2(960, 600));
  ImGui::Begin("Title", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  int screen = sm->getScreen();
  if (screen == 0 && gs->choose)  // Menu
  {
    mainMenu();
  }

  ImGui::End();
}


void MenuLaunch::mainMenu()
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
