#include "ScreenTitle.h"
#include "RenderSystem.h"
#include "imgui.h"


ScreenTitle::ScreenTitle()
{
}


ScreenTitle::~ScreenTitle()
{

}


void ScreenTitle::draw(RenderSystem* rs, float dt)
{
  glClearColor(188.0/255.0, 203.0/255.0, 227.0/255.0, 1.0);

}


void ScreenTitle::init(const std::string& filename)
{

  mTexTitle.loadPng("data/img/intro/leapyfrog.png");

}


int ScreenTitle::keyCallback(int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {

    if (key == GLFW_KEY_X)
    {
      if (mInfo)
      {
        mInfo = false;
      }
      else
      {
        setAdvanceMessage();
      }
    }

    if (key == GLFW_KEY_Z)
    {
      mInfo = !mInfo;
    }
  }

  return 0;
}


int ScreenTitle::drawUI()
{
  ImGuiIO& io = ImGui::GetIO();


  if (mInfo)
  {
    ImVec2 pos(80.f, 40.f);
    ImVec2 pivot(0, 0);
    ImGui::SetNextWindowPos(pos, 0, pivot);
    ImGui::SetNextWindowSize(ImVec2(980, 526));
    ImGui::Begin("Screen1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::Text("Leapy Frog");
    ImGui::Text("Use arrows to move left and right.");
    ImGui::Text("");
    ImGui::Text("Press [X] to jump.");
    ImGui::Text("You can hang and jump off walls.");
    ImGui::Text("");
    ImGui::Text("Press [Z] to use your special action jump.");
    ImGui::Text("Hold [Z] and use the arrow keys to aim.");
    ImGui::Text("");
    ImGui::Text("Image Credit: pixel-frog.itch.io");

  }
  else
  {
    ImVec2 pos(180.f, 180.f);
    ImVec2 pivot(0, 0);
    ImGui::SetNextWindowPos(pos, 0, pivot);
    ImGui::SetNextWindowSize(ImVec2(980, 526));
    ImGui::Begin("Screen1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::Image((ImTextureID)mTexTitle.getID(), ImVec2(310 * 2, 99 * 2), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));

    ImGui::Text("    [X]  Start");
    ImGui::Text("    [Z]  About");
  }

  ImGui::End();

  return 0;
}
