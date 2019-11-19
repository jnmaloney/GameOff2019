#include "MenuMain.h"
#include "imgui.h"
#include <string>
#include <iostream>


MenuMain::MenuMain()
{
  mBackground.loadPng("data/img/menu_screen_2.png");
  mButtonPlay.loadPng("data/img/button_play_normal.png");
  mButtonPlaySelected.loadPng("data/img/button_play_hover.png");
  mButtonPlayPressed.loadPng("data/img/button_play_pressed.png");
  mButtonQuit.loadPng("data/img/button_quit_normal.png");
  mButtonQuitSelected.loadPng("data/img/button_quit_hover.png");
  mButtonQuitPressed.loadPng("data/img/button_quit_pressed.png");
}


MenuMain::~MenuMain()
{

}


int MenuMain::drawUI()
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


void MenuMain::mainMenu()
{
  ImTextureID my_tex_id = (ImTextureID)mBackground.getID();
  float my_tex_w = mBackground.mWidth * 2;
  float my_tex_h = mBackground.mHeight * 2;

  ImGui::Image(
    my_tex_id,
    ImVec2(my_tex_w, my_tex_h),
    ImVec2(0,0),
    ImVec2(1,1),
    ImColor(255,255,255,255),
    ImColor(255,255,255,128));

  ImVec2 pos;
  ImVec2 pivot(0, 0);

  pos = ImVec2(2 * 196, 2 * 148);

  int frame_padding = -1;
  my_tex_id = (ImTextureID)mButtonPlay.getID();
  my_tex_w = mButtonPlay.mWidth * 2;
  my_tex_h = mButtonPlay.mHeight * 2;

  ImVec2 size(my_tex_w, my_tex_h);
  ImGui::SetCursorScreenPos(pos);
  if (ImGui::InvisibleButton("##option01", size))
  {
    // Advance
    setAdvanceMessage();
  }
  if (ImGui::IsItemHovered())
  {
    selected = 0;
    press = false;
  }
  if (ImGui::IsItemActive()) //IsItemClicked())
  {
    press = true;
  }

  if (selected == 0)
  {
    if (press)
      my_tex_id = (ImTextureID)mButtonPlayPressed.getID();
    else
      my_tex_id = (ImTextureID)mButtonPlaySelected.getID();
  }


  ImGui::SetCursorScreenPos(pos);
  ImGui::Image(
    my_tex_id,
    ImVec2(my_tex_w, my_tex_h),
    ImVec2(0,0),
    ImVec2(1,1),
    ImColor(255,255,255,255),
    ImColor(0,0,0,0));
  // if (ImGui::ImageButton(
  //   my_tex_id,
  //   ImVec2(my_tex_w, my_tex_h),
  //   ImVec2(0,0),
  //   ImVec2(1,1),
  //   frame_padding,
  //   ImColor(0,0,0,0)))
  // {
  //   // Advance
  // }


  pos = ImVec2(2 * 196, 2 * 181);

  my_tex_id = (ImTextureID)mButtonQuit.getID();
  my_tex_w = mButtonQuit.mWidth * 2;
  my_tex_h = mButtonQuit.mHeight * 2;

  ImGui::SetCursorScreenPos(pos);
  ImGui::InvisibleButton("##option02", size);
  if (ImGui::IsItemHovered())
  {
    selected = 1;
    press = false;
  }
  if (ImGui::IsItemActive())
  {
    press = true;
  }

  if (selected == 1)
  {
    if (press)
      my_tex_id = (ImTextureID)mButtonQuitPressed.getID();
    else
      my_tex_id = (ImTextureID)mButtonQuitSelected.getID();
  }

  ImGui::SetCursorScreenPos(pos);
  ImGui::Image(
    my_tex_id,
    ImVec2(my_tex_w, my_tex_h),
    ImVec2(0,0),
    ImVec2(1,1),
    ImColor(255,255,255,255),
    ImColor(0,0,0,0));
  // if (ImGui::ImageButton(
  //   my_tex_id,
  //   ImVec2(my_tex_w, my_tex_h),
  //   ImVec2(0,0),
  //   ImVec2(1,1),
  //   frame_padding,
  //   ImColor(0,0,0,0)))
  // {
  //
  // }
}


int MenuMain::keyCallback(int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_E)
    {
      press = true;
    }

    if (key == GLFW_KEY_UP)
    {
      selected = 1 - selected;
    }

    if (key == GLFW_KEY_DOWN)
    {
      selected = 1 - selected;
    }
  }

  if (action == GLFW_RELEASE)
  {
    if (key == GLFW_KEY_E)
    {
      press = false;

      if (selected == 0)
      {
        // Advance
        setAdvanceMessage();
      }
    }
  }

  return 0;
}
