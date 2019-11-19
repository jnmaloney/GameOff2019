#include "ScreenPlayerFixed.h"
#include "TileMap.h"
#include "TileSet.h"


ScreenPlayerFixed::ScreenPlayerFixed()
{

}


ScreenPlayerFixed::~ScreenPlayerFixed()
{

}


void ScreenPlayerFixed::draw(RenderSystem* rs, float dt)
{

  //
  // Set/Get State Values
  //
  if (mStateValues->getValue("free").flags == 1)
  {

    //
    // Make sure a dynamic body exists
    //
    static bool added = false;
    if (added == false)
    {
      mPhysicsLevel.addDynamic(245*0.5, 108, 19, 34);

      added = true;
    }

    //
    //
    //
    if (mStateValues->getValue("grounded").flags == 1)
    {
      mPlayerController.mJumping = false;
      mPlayerController.mFalling = false;
    }
    else
    {
      if (mPhysicsLevel.getDynamicYDir() < 0)
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

    //
    // Player Controls
    //
    {
      if (mPlayerController.getJump())
      {
        mPhysicsLevel.jumpDynamic();
      }

      int d = mPlayerController.getDir();
      mPhysicsLevel.addDynamicImpulse(d);
    }

    //
    // Drawing
    //
    float a = 0;
    float b = 0;
    mPhysicsLevel.step(dt);
    mPhysicsLevel.getDynamicPosition(&a, &b);

    bool ground = false;
    bool ceiling = false;
    bool wallLeft = false;
    bool wallRight = false;
    mPhysicsLevel.contactPoints(&ground, &ceiling, &wallLeft, &wallRight);
    mStateValues->setValue("grounded", ground, 0);

    float PIXEL = 1.f;

    int t = 1;
    float x = a;// - 41;
    float y = b - 82;
    mPlayerController.setPos(x, y);

    mTexCharacter.bind();
    mPlayerController.draw(rs, dt);

    //
    //  Trigger Test
    //
    if (mPhysicsLevel.isTrigger(0) && mStateValues->getValue("has_journal").flags == 0)
    {
      mStateValues->setValue("can_pick_journal", 1, 0);
    }
    else
    {
      mStateValues->setValue("can_pick_journal", 0, 0);
    }

    if (mPhysicsLevel.isTrigger(1) && mStateValues->getValue("has_journal").flags)
    {
      mStateValues->setValue("can_exit", 1, 0);
    }
    else
    {
      mStateValues->setValue("can_exit", 0, 0);
    }
  }

}


void ScreenPlayerFixed::init()
{
  mTexCharacter.loadPng("data/img/main_char_full(1).png");

  mPhysicsLevel.init();
  // Wall
  mPhysicsLevel.addTile(-10, 0, 0, 1000);
  mPhysicsLevel.addTile(245, 255, 0, 1000);
  // Floor
  mPhysicsLevel.addTile(0, 1000, 134, 200);
  mPhysicsLevel.addTile(0, 0, 0, 0); // ?

  mPhysicsLevel.addTrigger(146+0, 146+31-0, 133, 134);
  mPhysicsLevel.addTrigger(16+0, 16+65-0, 133, 134);

  //mPhysicsLevel.addDynamic(245*0.5, 108);

  //
  m_renderQueues.resize(0);
  size_t n = 4;
  m_renderQueues.resize(n);

  m_renderQueues[0].x_res = 512.0f / 80.0f;
  m_renderQueues[0].y_res = 512.0f / 80.0f;
  m_renderQueues[0].mod_vert = 5;
  m_renderQueues[0].div_vert = 5;

}


int ScreenPlayerFixed::keyCallback(int key, int scancode, int action, int mods)
{
  if (mStateValues->getValue("free").flags == 1)
  {
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
      if (key == GLFW_KEY_UP)
      {
        if (mStateValues->getValue("grounded").flags == 1)
          mPlayerController.jump();
      }
    }

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
    }
  }

  if (mStateValues->getValue("can_pick_journal").flags == 1)
  {
    if (action == GLFW_PRESS)
    {
      if (key == GLFW_KEY_E)
      {
        mStateValues->setValue("can_pick_journal", 0, 0);
        mStateValues->setValue("has_journal", 1, 0);
      }
    }
  }

  if (mStateValues->getValue("can_exit").flags == 1)
  {
    if (action == GLFW_PRESS)
    {
      if (key == GLFW_KEY_E)
      {
        // Next Scene
        setAdvanceMessage();
      }
    }
  }

  return 0;
}
