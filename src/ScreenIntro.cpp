#include "ScreenIntro.h"
#include "RenderSystem.h"
#include "imgui.h"


ScreenIntro::ScreenIntro()
{
}


ScreenIntro::~ScreenIntro()
{

}


void ScreenIntro::draw(RenderSystem* rs, float dt)
{
  //glClearColor(0.0, 0.0, 0.0, 1.0);
  glClearColor(50.0/255.0, 50.0/255.0, 50.0/255.0, 1.0);

  mTimer -= dt;
  if (mTimer < 0)
  {
    mTimer = 10.f;
    mPage += 1;
  }
  if (mPage >= 4)
    setAdvanceMessage();
}


void ScreenIntro::init(const std::string& filename)
{
  mTex1.loadPng("data/img/intro/tadpole.png");
  mTex2.loadPng("data/img/intro/commonfrog.png");
  mTex3.loadPng("data/img/intro/scroll.png");
  mTex4.loadPng("data/img/intro/ninjafrog.png");
}


int ScreenIntro::keyCallback(int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_X || key == GLFW_KEY_Z)
    {
      mTimer -= 2.0f;
    }
  }

  return 0;
}


int ScreenIntro::gamepadUpdate(double x, double y, int a, int b)
{
  if (a || b)
  {
    mTimer -= 0.2f;
  }

  return 0;
}


int ScreenIntro::drawUI()
{
  float timer = 10.f - mTimer;

  {
    ImVec2 pos(372, 145);
    ImVec2 pivot(0, 0);
    ImGui::SetNextWindowPos(pos, 0, pivot);
    ImGui::SetNextWindowSize(ImVec2(980, 526));
    ImGui::Begin("Screen1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    if (mPage == 0)
    {
      if (timer > 0.02)
      ImGui::Image((ImTextureID)mTex1.getID(), ImVec2(59 * 4, 59 * 4), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
    }
    if (mPage == 1)
    {
      if (timer > 0.02)
      ImGui::Image((ImTextureID)mTex2.getID(), ImVec2(59 * 4, 59 * 4), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
    }
    if (mPage == 2)
    {
      if (timer > 0.02)
      ImGui::Image((ImTextureID)mTex3.getID(), ImVec2(59 * 4, 59 * 4), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
    }
    if (mPage == 3)
    {
      if (timer > 0.02)
      ImGui::Image((ImTextureID)mTex4.getID(), ImVec2(59 * 4, 59 * 4), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
    }


    ImGui::End();
  }
  {
    ImVec2 pos(90.f, 60.f);
    ImVec2 pivot(0, 0);
    ImGui::SetNextWindowPos(pos, 0, pivot);
    ImGui::SetNextWindowSize(ImVec2(980, 526));
    ImGui::Begin("Screen2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    if (mPage == 0)
    {
      if (timer > 0.5) ImGui::Text("When I was a tadpole...");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      if (timer > 5.0) ImGui::Text("My father left.");
    }

    if (mPage == 1)
    {
      if (timer > 0.5) ImGui::Text("The last thing he said to me...");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      if (timer > 5.0) ImGui::Text("\"I need to go now. This could be my last journey.\"");
    }

    if (mPage == 2)
    {
      if (timer > 0.5) ImGui::Text("\"If I don't return...\"");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      if (timer > 5.0) ImGui::Text("\"Avenge me.\"");
    }

    if (mPage == 3)
    {
      if (timer > 0.5) ImGui::Text("Now...");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      ImGui::Text("");
      if (timer > 5.0) ImGui::Text("it is my time.");
    }

    ImGui::End();
  }

  return 0;
}
