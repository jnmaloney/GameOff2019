#include "PlayerController.h"
#include "RenderSystem.h"
#include <stdio.h>
#include <iostream>


PlayerController::PlayerController()
{
  mRenderQueueWalk.setSheet(12, 1);
  mRenderQueueIdle.setSheet(11, 1);
  mRenderQueueHit.setSheet(7, 1);
  mRenderQueueJump.setSheet(1, 1);
  mRenderQueueJump2.setSheet(4, 1);
  mRenderQueueWall.setSheet(5, 1);
  mRenderQueueFall.setSheet(1, 1);
  mRenderQueueBall.setSheet(3, 1);

  mTexCharacterWalk.loadPng("data/img/frog/Run (32x32).png");
  mTexCharacterIdle.loadPng("data/img/frog/Idle (32x32).png");
  mTexCharacterHit.loadPng("data/img/frog/Hit (32x32).png");
  mTexCharacterJump.loadPng("data/img/frog/Jump (32x32).png");
  mTexCharacterJump2.loadPng("data/img/frog/Double Jump (32x32).png");
  mTexCharacterWall.loadPng("data/img/frog/Wall Jump (32x32).png");
  mTexCharacterFall.loadPng("data/img/frog/Fall (32x32).png");
  mTexCharacterBall.loadPng("data/img/frog/BallFrame.png");

  mRenderQueueEffect.setSheet(8, 8);
  mTexEffect.loadPng("data/img/effect_charge.png");

  mRenderQueueArrow.setSheet(1, 1);
  mTexArrow.loadPng("data/img/arrow96c.png");
}


PlayerController::~PlayerController()
{

}


void PlayerController::wantsToMoveLeft()
{
  if (mWallGrip) return;
  mFacingRight = false;
  mLeft = true;
  // if (m_actionCharge)
  // {
  //   m_actionChargeLeft = 1;
  // }
}


void PlayerController::wantsToMoveRight()
{
  if (mWallGrip) return;
  mFacingRight = true;
  mRight = true;
  // if (m_actionCharge)
  // {
  //   m_actionChargeRight = 1;
  // }
}


void PlayerController::wantsToStop()
{
  mLeft = false;
  mRight = false;
  // m_actionChargeRight = 0;
  // m_actionChargeLeft = 0;
}


int PlayerController::getJump()
{
  if (m_actionCharge) return 0;

  if (mJump)
  {
    mJump = 0;
    return 1;
  }
  return 0;
}


void PlayerController::wantsToJump()
{
  if (mGrounded && !mFalling && !mJumping)
  {
    mJump = true;
    mGrounded = false;
  }
  if (mWallGrip)
  {
    mJump = true;
    mWallGrip = false;
  }
}


void PlayerController::wantsToDrop()
{
  mWallGrip = false;
}


void PlayerController::wantsToAction()
{
  if (mGrounded)
  {
    m_actionCharge = true;
  }
}


void PlayerController::setPos(float x, float y)
{
    mX = x;
    mY = y;
}


void PlayerController::forceFaceLeft()
{
  mFacingRight = false;
  mRight = false;
}


void PlayerController::forceFaceRight()
{
  mFacingRight = true;
  mLeft = false;
}


void PlayerController::draw(RenderSystem* rs, float dt)
{
    //
    // Player Controls (Action)
    //
    if (m_actionCharge)
    {
      if (mLeft && !mRight)
      {
        actionDir -= 270.0 * dt;
      }
      if (mRight && !mLeft)
      {
        actionDir += 270.0 * dt;
      }
      if (actionDir < -81.0f) actionDir = -81.f;
      if (actionDir >  81.0f) actionDir =  81.f;
    }

  //
  // Updates...
  //
  mGrounded = !(mJumping || mFalling || mWallGrip);

  //
  // Set character sprite frame
  //

  if (m_cannonAction)
  {
    mTexCharacter = mTexCharacterJump2;
    mQueue = mRenderQueueJump2;
  }
  else if (m_actionCharge)
  {
    mTexCharacter = mTexCharacterBall;
    mQueue = mRenderQueueBall;
  }
  else if (mWallGrip)
  {
    mTexCharacter = mTexCharacterWall;
    mQueue = mRenderQueueWall;
  }
  else if (mJumping)
  {
    mTexCharacter = mTexCharacterJump;
    mQueue = mRenderQueueJump;
  }
  else if (mFalling)
  {
    mTexCharacter = mTexCharacterFall;
    mQueue = mRenderQueueFall;
  }
  else if (mRight && !mLeft)
  {
    mTexCharacter = mTexCharacterWalk;
    mQueue = mRenderQueueWalk;
  }
  else if (mLeft && !mRight)
  {
    mTexCharacter = mTexCharacterWalk;
    mQueue = mRenderQueueWalk;
  }
  else
  {
    // Idle
    mTexCharacter = mTexCharacterIdle;
    mQueue = mRenderQueueIdle;
  }

  // Changing free-float mode
  if (m_cannonAction == false)
  {
    if (mFalling) m_freeContinueFloat = false; // !
  }
  if (mWallGrip) m_freeContinueFloat = false; // !
  if (mFalling) m_cannonAction = false;


  //
  // Draw
  //

  m_frameTimer += dt;
  if (m_frameTimer > 240000.0) m_frameTimer -= 240000;
  float timer = m_frameTimer;

  float PIXEL = 1.f;

  const float framedelay = 12.f;
  int t = 1 + ((int)(timer * framedelay)) % mQueue.mod_vert;
  float x = mX;
  float y = mY;
  float z = 2;

  glm::mat4 mvp(1.0);
  mvp = glm::mat4(1.0);

  mvp = glm::translate(mvp,
    glm::vec3(
      x,
      y,
      z));

  mvp = glm::scale(mvp,
    glm::vec3(
      PIXEL * 32.f,
      PIXEL * 32.f,
      1.0f));

  if (mFacingRight == false)
  {
    mvp = glm::scale(mvp,
      glm::vec3(
        -1.f,
         1.f,
         1.f));
  }

  // center point
  mvp = glm::translate(mvp,
    glm::vec3(
     -0.5f,
     -0.0f,
      0));

    if (m_actionCharge)
    {
      glm::mat4 mvp3(1.0);
      mvp3 = glm::translate(mvp3, glm::vec3(x, y + 24, -2.f));
      mvp3 = glm::scale(mvp3, glm::vec3(0.5*PIXEL * 100.f, 0.5*PIXEL * 100.f, 1.0f));

      mvp3 = glm::rotate(mvp3,
        glm::radians(actionDir),
        glm::vec3(0, 0, 1));

      // center point
      mvp3 = glm::translate(mvp3,
        glm::vec3(
         -0.5f,
         -0.5f,
          0));


      mRenderQueueArrow.clear();
      mRenderQueueArrow.setTile(1);
      mRenderQueueArrow.setMVP(mvp3);
      mRenderQueueArrow.submit();
      mTexArrow.bind();
      mRenderQueueArrow.draw(rs);

      glm::mat4 mvp2(1.0);
      mvp2 = glm::translate(mvp2, glm::vec3(x, y, -1.f));
      mvp2 = glm::scale(mvp2, glm::vec3(PIXEL * 100.f, PIXEL * 100.f, 1.0f));

      // center point
      mvp2 = glm::translate(mvp2,
        glm::vec3(
         -0.5f,
         -0.3f,
          0));

      mRenderQueueEffect.clear();
      mRenderQueueEffect.setTile(1 + ((int)(timer * 2*framedelay)) % 61);
      mRenderQueueEffect.setMVP(mvp2);
      mRenderQueueEffect.submit();
      mTexEffect.bind();
      mRenderQueueEffect.draw(rs);


    }

  mQueue.clear();
  mQueue.setTile(t);
  mQueue.setMVP(mvp);
  mQueue.submit();

  mTexCharacter.bind();
  mQueue.draw(rs);
}


void PlayerController::setFreeFloatMode()
{
  m_freeContinueFloat = true;
}


void PlayerController::setStopFloatMode()
{
  m_freeContinueFloat = false;
}



bool PlayerController::collect(float x, float y)
{
  if (abs(x - mX) < 16 && abs(y - mY - 24) < 16) return true;
  return false;
}
