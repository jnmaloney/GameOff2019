#pragma once


#include "Screen.h"
#include "Texture.h"


// TODO - needs to be its own component
class PlayerController
{
public:

  PlayerController();
  ~PlayerController();

  void setPos(float x, float y);

  void moveLeft();
  void moveRight();

  void moveLeft2();
  void moveRight2();

  void draw(RenderSystem* rs, float timer);

  void jump() { mJump = 1; }

  int getDir()
  {
    if (mRight && !mLeft) return 1;
    if (mLeft && !mRight) return -1;
    return 0;
  }

  int getJump()
  {
    if (m_actionCharge) return 0;

    if (mJump)
    {
      mJump = 0;
      return 1;
    }
    return 0;
  }

  bool mJumping = false;
  bool mFalling = false;
  bool mWallRight = false;
  bool mWallLeft = false;
  bool mWallGrip = false;

  bool m_actionCharge = false;
  bool m_actionChargeLeft = false;
  bool m_actionChargeRight = false;
  float actionDir = 0.f;

  // Player keeps moving with no input
  void setFreeFloatMode();
  // Player stops moving without input
  void setStopFloatMode();

  bool m_freeContinueFloat = false; // Jump direction will continue
  bool m_cannonAction = false;

  bool collect(float x, float y);

  void forceFaceLeft();
  void forceFaceRight();

protected:

  // Which way are you trying to move
  bool mRight = false;
  bool mLeft = false;
  int mJump = 0;

  bool mFacingRight = true;
  bool mGrounded = true;

  float mX = 0;
  float mY = 0;

  double m_frameTimer = 0.0;
  RenderQueue mRenderQueueWalk;
  RenderQueue mRenderQueueIdle;
  RenderQueue mRenderQueueJump;
  RenderQueue mRenderQueueJump2;
  RenderQueue mRenderQueueHit;
  RenderQueue mRenderQueueWall;
  RenderQueue mRenderQueueFall;
  RenderQueue mRenderQueueBall;
  RenderQueue& mQueue = mRenderQueueHit;

  Texture mTexCharacterWalk;
  Texture mTexCharacterIdle;
  Texture mTexCharacterJump;
  Texture mTexCharacterJump2;
  Texture mTexCharacterHit;
  Texture mTexCharacterWall;
  Texture mTexCharacterFall;
  Texture mTexCharacterBall;
  Texture& mTexCharacter = mTexCharacterHit;

  RenderQueue mRenderQueueEffect;
  Texture mTexEffect;

  RenderQueue mRenderQueueArrow;
  Texture mTexArrow;
};
