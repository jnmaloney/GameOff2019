#include "Screen1.h"
#include "TileMap.h"
#include "TileSet.h"
#include "RenderSystem.h"
#include "imgui.h"
#include <stdio.h>
#include <iostream>


Screen1::Screen1()
{

}


Screen1::~Screen1()
{

}


void Screen1::draw(RenderSystem* rs, float dt)
{
  //glClearColor(50.0/255.0, 50.0/255.0, 50.0/255.0, 1.0);
  glClearColor(142.0/255.0, 47.0/255.0, 21.0/255.0, 1.0); // "Autumn"

  //
  // Stamina
  //
  if (!mPlayerController.mFalling && !mPlayerController.mJumping && !mPlayerController.m_actionCharge)
  {
    float rate = 0.5;
    stamina += rate * dt;
  }

  //
  // Pickup
  //
  for (int i = 0; i < 3; ++i)
  {
    if (m_pickups[i].picked > 0)
    {
      if (mPlayerController.collect(m_pickups[i].x, m_pickups[i].y))
      {
        m_pickups[i].picked = 0;

        // add score
        m_score += 1;

        // restore draw list
        m_renderQueues[1].clear();
        for (int j = 0; j < 3; ++j)
        {
          if (m_pickups[j].picked == 0) continue;

          // stamp
          float z = 0.f;
          glm::mat4 mvp(1.0);
          mvp = glm::translate(mvp,
            glm::vec3(
              m_pickups[j].x - 28/2,
              m_pickups[j].y - 24 + 2,
              z));
          mvp = glm::scale(mvp,
            glm::vec3(
              28,
              24,
              1));

          m_renderQueues[1].setTile(1);
          m_renderQueues[1].setMVP(mvp);
          m_renderQueues[1].submit();
        }
      }
    }
  }

  m_renderQueues[2].clear();
  for (int i = 0; i < 3; ++i)
  {
    if (m_pickups[i].picked == 0 && m_pickups[i].timer > 0)
    {
      int t = m_pickups[i].timer * 12.f;
      float z = 1.f;
      glm::mat4 mvp(1.0);
      mvp = glm::translate(mvp,
        glm::vec3(
          m_pickups[i].x - 50,
          m_pickups[i].y - 50,
          z));
      mvp = glm::scale(mvp,
        glm::vec3(
          100,
          100,
          1));

      m_renderQueues[2].setTile(1 + t);
      m_renderQueues[2].setMVP(mvp);
      m_renderQueues[2].submit();

      m_pickups[i].timer -= dt;
    }
  }

  //
  // Timer
  //
  if (m_score < 3)
  {
    m_timer += dt;
    while (m_timer >= 60)
    {
      m_timer -= 60;
      m_mins += 1;
    }
  }

  //
  // Player values: transfer from State to PlayerController
  //
  if (mStateValues->getValue("grounded").flags == 1)
  {
    mPlayerController.mJumping = false;
    mPlayerController.mFalling = false;
    mPlayerController.mWallLeft = false;
    mPlayerController.mWallRight = false;
  }
  else  /* ? */ if (!(mPlayerController.mWallGrip))
  {
    if (mLevel.mPhysicsLevel.getDynamicYDir() < 0)
    {
      mPlayerController.mJumping = true;
      mPlayerController.mFalling = false;
    }
    else
    {
      mPlayerController.mJumping = false;
      mPlayerController.mFalling = true;
    }
  }

  if (mStateValues->getValue("wall right").flags == 1)
  {
    // Grab wall, if hit wall while in air
    if (mPlayerController.mWallRight == false && !mPlayerController.m_cannonAction)
    {
      if (mPlayerController.mJumping || mPlayerController.mFalling)
      {
        mPlayerController.mWallGrip = true;
        mPlayerController.mJumping = false;
        mPlayerController.mFalling = false;
        mPlayerController.forceFaceRight();
        // mPlayerController.moveRight();        // !
        // mPlayerController.moveLeft2();        // !
        // mPlayerController.moveRight2();        // !
      }
    }

    mPlayerController.mWallRight = true;
  }
  else
  {
    mPlayerController.mWallRight = false;
  }

  if (mStateValues->getValue("wall left").flags == 1)
  {
    // Grab wall, if hit wall while in air
    if (mPlayerController.mWallLeft == false && !mPlayerController.m_cannonAction)
    {
      if (mPlayerController.mJumping || mPlayerController.mFalling)
      {
        mPlayerController.mWallGrip = true;
        mPlayerController.mJumping = false;
        mPlayerController.mFalling = false;
        mPlayerController.forceFaceLeft();
        // mPlayerController.moveLeft();                // !
        // mPlayerController.moveRight2();                // !
        // mPlayerController.moveLeft2();                // !
      }
    }

    mPlayerController.mWallLeft = true;
  }
  else
  {
    mPlayerController.mWallLeft = false;
  }

  //
  // Physic World update
  //
  if (mPlayerController.mWallGrip)
  {
    mLevel.mPhysicsLevel.freezeDynamic();
  }
  else
  {
    mLevel.mPhysicsLevel.unfreezeDynamic();
  }

  //
  // Player Controls
  //
  {
    if (mPlayerController.getJump())
    {
      if (mPlayerController.mWallGrip)
      {
        mPlayerController.mWallGrip = false; // !
        mLevel.mPhysicsLevel.unfreezeDynamic();

        if (mPlayerController.getDir() == -1)// && !mPlayerController.mWallRight && mPlayerController.getDir() == -1)
        {
          // Jump right
          mLevel.mPhysicsLevel.jumpDynamic(0.5f);

          // Set 'facing' hack
          // mPlayerController.moveLeft2();
          // mPlayerController.moveRight();
          //mPlayerController.moveRight2();
          mPlayerController.setFreeFloatMode();
        }
        else if (mPlayerController.getDir() == 1)// && !mPlayerController.mWallLeft && mPlayerController.getDir() == 1)
        {
          // Jump left
          mLevel.mPhysicsLevel.jumpDynamic(-0.5f);

          // Set 'facing' hack
          // mPlayerController.moveRight2();
          // mPlayerController.moveLeft();
          //mPlayerController.moveLeft2();
          mPlayerController.setFreeFloatMode();
        }
        else
        {
          mLevel.mPhysicsLevel.jumpDynamic();
        }
      }
      else // Not Grip
      {
        mLevel.mPhysicsLevel.jumpDynamic();
        int d = mPlayerController.getDir();
        int mode = mPlayerController.m_freeContinueFloat ? 2 : 0;
        mLevel.mPhysicsLevel.addDynamicImpulse(d, mode);
      }
    }
    else // Not jump
    {
      int d = mPlayerController.getDir();
      //int mode = (mPlayerController.mJumping || mPlayerController.mFalling);
      //mLevel.mPhysicsLevel.addDynamicImpulse(d, mode);

      // if (mPlayerController.mJumping)
      // {
      //   mLevel.mPhysicsLevel.addDynamicImpulse(d, 2);
      // }
      // else if (mPlayerController.mFalling)
      // {
      //   mLevel.mPhysicsLevel.addDynamicImpulse(d, 1);
      // }
      // else
      // {
      //   mLevel.mPhysicsLevel.addDynamicImpulse(d, 0);
      // }
      int mode = mPlayerController.m_freeContinueFloat ? 2 : 0;
      mLevel.mPhysicsLevel.addDynamicImpulse(d, mode);
    }
  }

  //
  // Player Controls (Action)
  //
  if (mPlayerController.m_actionCharge)
  {
    if (mPlayerController.m_actionChargeLeft && !mPlayerController.m_actionChargeRight)
    {
      mPlayerController.actionDir -= 270.0 * dt;
    }
    if (mPlayerController.m_actionChargeRight && !mPlayerController.m_actionChargeLeft)
    {
      mPlayerController.actionDir += 270.0 * dt;
    }
    if (mPlayerController.actionDir < -81.0f) mPlayerController.actionDir = -81.f;
    if (mPlayerController.actionDir >  81.0f) mPlayerController.actionDir =  81.f;
  }

  //
  //  Track the character and set camera position
  //

  // Step! And get position
  float x = 0.f;
  float y = 0.f;
  mLevel.mPhysicsLevel.step(dt);
  mLevel.mPhysicsLevel.getDynamicPosition(&x, &y);
  mPlayerController.setPos(x, y - 19); // Pixel offset

  // Estimate position for camera smoothing
  glm::vec3 tla1 = (mCameraHistory[0] + mCameraHistory[1] + mCameraHistory[2]) / 3.f;
  glm::vec3 tla2 = (mCameraHistory[1] + mCameraHistory[2] + mCameraHistory[3]) / 3.f;
  mCameraHistory[0] = mCameraHistory[1];
  mCameraHistory[1] = mCameraHistory[2];
  mCameraHistory[2] = mCameraHistory[3];
  mCameraHistory[3].x = x;
  mCameraHistory[3].y = y;
  glm::vec3 est3 = tla2 + (tla2 - tla1);
  est3.y -= 16;

  // Limit camera jerkiness
  glm::vec3 cameraDir = est3 - mCameraPos;
  float l = cameraDir.length();
  float maxl = 70.0 * dt;
  if (l > maxl)
    cameraDir = (maxl / l) * cameraDir;
  mCameraPos += cameraDir;

  // Set camera and render
  rs->setCameraPos(
    glm::vec3(mCameraPos.x, mCameraPos.y, 200),
    glm::vec3(mCameraPos.x, mCameraPos.y, 0),
    glm::vec3(0, 1, 0));

  mTexGround.bind();
  m_renderQueues[0].draw(rs, x, y);

  mTexPickup.bind();
  m_renderQueues[1].draw(rs);

  mTexCollectEffect.bind();
  m_renderQueues[2].draw(rs);

  mPlayerController.draw(rs, dt);
}


void Screen1::init(const std::string& filename)
{
  mTexGround.loadPng("data/img/Terrain.png");
  mTexPickup.loadPng("data/box1.png");
  mTexCollectEffect.loadPng("data/1_magicspell_spritesheet.png");

  mLevel.init("data/level_1.tmx", "data/img/Terrain.png", 420.f);
  mLevel.mPhysicsLevel.addDynamic(160, 1209, 24, 24);

  float x = 160;
  float y = 160;
  mCameraHistory[0] = glm::vec3(x, y, 0);
  mCameraHistory[1] = glm::vec3(x, y, 0);
  mCameraHistory[2] = glm::vec3(x, y, 0);
  mCameraHistory[3] = glm::vec3(x, y, 0);
  mCameraPos = glm::vec3(x, y, 0);

  //
  // Set renderqueue status from tileset
  //

  // Generate Render Queues
  m_renderQueues.resize(0);
  size_t n = 3;
  m_renderQueues.resize(n);

  m_renderQueues[0].x_res = 22;//mLevel.getMap()->tilewidth;
  m_renderQueues[0].y_res = 11;// mLevel.getMap()->tileheight;
  m_renderQueues[0].mod_vert = 22;// mLevel.getSet()->mTexture.mWidth / mLevel.getMap()->tilewidth;
  m_renderQueues[0].div_vert = 22;// mLevel.getSet()->mTexture.mHeight / mLevel.getMap()->tileheight;

  m_renderQueues[1].setSheet(1, 1);

  m_renderQueues[2].setSheet(9, 9);

  //std::cout << mLevel.getMap()->width << ", " << mLevel.getMap()->height << std::endl;

  //
  // Create Goal Items
  //
  int ind = 0;
  for (const auto& i : mLevel.getMap()->objects)
  {
    //btCollisionObject* pickup =
    //mLevel.mPhysicsLevel.addPickup(i.x - 8, i.y - 8, i.x + 8, i.y + 8, (void*)ind);
    m_pickups[ind].x = i.x;
    m_pickups[ind].y = i.y;
    m_pickups[ind].picked = 1;
    m_pickups[ind].info = 100;

    ++ind;

    // stamp
    float z = 0.f;
    glm::mat4 mvp(1.0);
    mvp = glm::translate(mvp,
      glm::vec3(
        i.x - 28/2,
        i.y - 24 + 2,
        z));
    mvp = glm::scale(mvp,
      glm::vec3(
        28,
        24,
        1));

    m_renderQueues[1].setTile(1);
    m_renderQueues[1].setMVP(mvp);
    m_renderQueues[1].submit();
  }

  //
  // Create Tile renderqueue
  //
  // Map tile render
  m_renderQueues[0].clear();
  int z = 0;
  for (int i = 0; i < mLevel.getMap()->width; ++i)
  {
    for (int j = 0; j < mLevel.getMap()->height; ++j)
    {
      glm::mat4 mvp(1.0);

      // mvp = glm::scale(mvp,
      //   glm::vec3(
      //     2,
      //     2,
      //     1));

      mvp = glm::translate(mvp,
        glm::vec3(
          i * mLevel.getMap()->tilewidth,
          j * mLevel.getMap()->tileheight,
          z));

      mvp = glm::scale(mvp,
        glm::vec3(
          mLevel.getMap()->tilewidth,
          mLevel.getMap()->tileheight,
          1));

      int t = i + mLevel.getMap()->width * j;
      int u = mLevel.getMap()->layers[0].data[t];
      //std::cout << u << std::endl;
      if (u != 0)
      {
        // stamp
        m_renderQueues[0].setTile(u);
        m_renderQueues[0].setMVP(mvp);
        m_renderQueues[0].submit();
      }
    }
  }
  //std::cout << "finish" << std::endl;

}


int Screen1::keyCallback(int key, int scancode, int action, int mods)
{
  //
  // Press Key
  //
  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_LEFT)
    {
      mPlayerController.moveLeft();
    }
    if (key == GLFW_KEY_RIGHT)
    {
      mPlayerController.moveRight();
    }
    if (key == GLFW_KEY_X)
    {
      // Ground Jump
      if (mStateValues->getValue("grounded").flags == 1)
      {
        mPlayerController.jump();
      }

      // Wall Jump
      if (mPlayerController.mWallGrip)
      {
        mPlayerController.jump();
        //mPlayerController.mWallGrip = false;
      }
    }

    if (key == GLFW_KEY_Z && stamina >= 1.f)
    {
      if (!(mPlayerController.mFalling || mPlayerController.mJumping || mPlayerController.mWallGrip))
      {
        mPlayerController.m_actionCharge = true;
        mPlayerController.actionDir = 0.f;
        mPlayerController.moveRight2();
        mPlayerController.moveLeft2();
      }
    }
  }

  //
  // Release Key
  //
  if (action == GLFW_RELEASE)
  {
    if (key == GLFW_KEY_LEFT)
    {
      mPlayerController.moveLeft2();
    }
    if (key == GLFW_KEY_RIGHT)
    {
      mPlayerController.moveRight2();
    }

    if (key == GLFW_KEY_Z)
    {
      if (mPlayerController.m_actionCharge) // !
      {
        stamina = 0.f;
        mLevel.mPhysicsLevel.jumpLaunchDynamic(glm::radians(mPlayerController.actionDir)); // Action here
        mPlayerController.setFreeFloatMode();
        mPlayerController.m_cannonAction = true;
      }
      mPlayerController.m_actionCharge = false;
    }
  }

  return 0;
}


int Screen1::drawUI()
{
  ImGuiIO& io = ImGui::GetIO();

  ImVec2 pos(0.f, 0.f);
  ImVec2 pivot(0, 0);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::SetNextWindowSize(ImVec2(960, 600));
  ImGui::Begin("Screen1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

  //
  // State values being set (!!!)
  //
  bool ground = false;
  bool ceiling = false;
  bool wallLeft = false;
  bool wallRight = false;
  mLevel.mPhysicsLevel.contactPoints(&ground, &ceiling, &wallLeft, &wallRight);
  mStateValues->setValue("grounded", ground, 0);
  mStateValues->setValue("wall left", wallLeft, 0);
  mStateValues->setValue("wall right", wallRight, 0);
	// if (ground)
	// 	ImGui::Text("ground");
	// if (ceiling)
	// 	ImGui::Text("ceiling");
	// if (wallLeft)
	// 	ImGui::Text("wall left");
	// if (wallRight)
	// 	ImGui::Text("wall right");

  //
  // Game UI
  //
  int m = m_mins;
  int s = m_timer;
  ImGui::Text(" Score: %i / %i", m_score, 3);
  ImGui::Text(" Time: %i:%02i", m, s);

  ImGui::ProgressBar(stamina, ImVec2(100.0f, 0.0f));
  ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
  ImGui::Text("Stamina");

  ImGui::End();

  return 0;
}
