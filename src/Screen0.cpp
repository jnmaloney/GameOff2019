#include "Screen0.h"
#include "RenderSystem.h"


Screen0::Screen0()
{
 mYScroll = -2.3f;
}


Screen0::~Screen0()
{

}


void Screen0::draw(RenderSystem* rs, float dt)
{
  m_frameTimer += dt;
  if (m_frameTimer > 24.0) m_frameTimer -= 24;
  float timer = m_frameTimer;

  //
  //  Set camera position
  //
  rs->modeOrtho(0.0, 0.0, 0.25 * 980, 0.25 * 526);

  //
  // Set/Get State Values
  //
  if (mStateValues->getValue("menu").set)
  {
    mChoose = mStateValues->getValue("menu").flags;
  }
  else
  {
    mStateValues->setValue(
      "menu",
      mChoose ? 1 : 0,
      0);
  }

  if (mStateValues->getValue("next").set)
  {
    mNext = true;
  }

  // if (mStateValues->getValue("free").set)
  // {
  //   mFree = true;
  // }
  mFree = mStateValues->getValue("free").flags;


  //
  // Scrolling Valueis
  //

  float TILE = 49.f;

  if (mNext)
  {
    mYScroll += dt * mScrollSpeed;
    if (mYScroll < -6.f)
    {
      mYScroll += 4.f;
      mLoop = true;
    }

    if (mYScroll < -4.f && mLoop)
    {
      mNext = false;
      mLoop = false;
      mChoose = true;
      mScrollSpeed = -1.15;
    }
  }

  //
  // SET UP THE QUEUES
  //
  int t = 1;
  float x = mYScroll * TILE - 4.f * TILE;
  float y = 1.9f * TILE;
  float z = 0;

  glm::mat4 mvp(1.0);
  mvp = glm::translate(mvp,
    glm::vec3(
      x,
      y,
      z));

  mvp = glm::scale(mvp,
    glm::vec3(
      256.f,
      128.f,
      1.0f));

  m_renderQueues[0].clear();
  m_renderQueues[0].setTile(t);
  m_renderQueues[0].setMVP(mvp);
  m_renderQueues[0].submit();

  x += 4.f * TILE;
  z = -1;
  mvp = glm::mat4(1.0);
  mvp = glm::translate(mvp,
    glm::vec3(
      x,
      y,
      z));

  mvp = glm::scale(mvp,
    glm::vec3(
      256.f,
      128.f,
      1.0f));

  m_renderQueues[0].setTile(t);
  m_renderQueues[0].setMVP(mvp);
  m_renderQueues[0].submit();

  x += 4.f * TILE;
  z = -2;
  mvp = glm::mat4(1.0);
  mvp = glm::translate(mvp,
    glm::vec3(
      x,
      y,
      z));

  mvp = glm::scale(mvp,
    glm::vec3(
      256.f,
      128.f,
      1.0f));

  m_renderQueues[0].setTile(t);
  m_renderQueues[0].setMVP(mvp);
  m_renderQueues[0].submit();

  x += 4.f * TILE;
  z = -2;
  mvp = glm::mat4(1.0);
  mvp = glm::translate(mvp,
    glm::vec3(
      x,
      y,
      z));

  mvp = glm::scale(mvp,
    glm::vec3(
      256.f,
      128.f,
      1.0f));

  m_renderQueues[0].setTile(t);
  m_renderQueues[0].setMVP(mvp);
  m_renderQueues[0].submit();

  m_renderQueues[1].clear();
  for (int i = 0; i < 3; ++i)
  {
    x = mYScroll * TILE + i * 256.f;
    y = 0;
    z = -9;
    t = 1;
    mvp = glm::mat4(1.0);
    mvp = glm::translate(mvp,
      glm::vec3(
        x,
        y,
        z));

    mvp = glm::scale(mvp,
      glm::vec3(
        256.f,
        256.f,
        1.0f));

    m_renderQueues[1].setTile(t);
    m_renderQueues[1].setMVP(mvp);
    m_renderQueues[1].submit();
  }

  m_renderQueues[2].clear();
  if (mFree == false)
  {
    x = mYScroll * TILE + 98.f;
    if (mYScroll < -3.f) x += 4.f * TILE;
    y = 1.9f * TILE - 61.f;
    z = -1;
    t = 1 + ((int)(timer * 8.f)) % 8;
    mvp = glm::mat4(1.0);
    mvp = glm::translate(mvp,
      glm::vec3(
        x,
        y,
        z));

    mvp = glm::scale(mvp,
      glm::vec3(
        46.f,
        65.f,
        1.0f));

    m_renderQueues[2].setTile(t);
    m_renderQueues[2].setMVP(mvp);
    m_renderQueues[2].submit();

    x += 4.f * TILE;

    mvp = glm::mat4(1.0);
    mvp = glm::translate(mvp,
      glm::vec3(
        x,
        y,
        z));

    mvp = glm::scale(mvp,
      glm::vec3(
        46.f,
        65.f,
        1.0f));

    m_renderQueues[2].setTile(t);
    m_renderQueues[2].setMVP(mvp);
    m_renderQueues[2].submit();
  }

  m_renderQueues[3].clear();
  if (mFree == true)
  {
    x = 98.f;
    y = 1.9f * TILE - 58.f;
    z = -1;
    t = 1;
    mvp = glm::mat4(1.0);
    mvp = glm::translate(mvp,
      glm::vec3(
        x,
        y,
        z));

    mvp = glm::scale(mvp,
      glm::vec3(
        64.f,
        64.f,
        1.0f));

    m_renderQueues[3].setTile(t);
    m_renderQueues[3].setMVP(mvp);
    m_renderQueues[3].submit();
  }

  m_renderQueues[4].clear();
  if (mFree == true)
  {
    x = 98.f;
    y = 1.9f * TILE - 64.f;
    z = 1;
    t = 9 + ((int)(timer * 8.f)) % 12;
    mvp = glm::mat4(1.0);
    mvp = glm::translate(mvp,
      glm::vec3(
        x,
        y,
        z));

    mvp = glm::scale(mvp,
      glm::vec3(
        82.f,
        82.f,
        1.0f));

    m_renderQueues[4].setTile(t);
    m_renderQueues[4].setMVP(mvp);
    m_renderQueues[4].submit();
  }

  x = 0;
  y = 1;
  z = 1;
  t = 1;
  mvp = glm::mat4(1.0);
  mvp = glm::translate(mvp,
    glm::vec3(
      x,
      y,
      z));

  mvp = glm::scale(mvp,
    glm::vec3(
      0.5f * 1024.f,
      0.5f * 128.f,
      1.0f));

  m_renderQueues[5].clear();
  m_renderQueues[5].setTile(t);
  m_renderQueues[5].setMVP(mvp);
  m_renderQueues[5].submit();

  //
  // Props
  //
  m_renderQueues[6].clear();
  m_renderQueues[6].setTile(1);
  m_renderQueues[7].clear();
  m_renderQueues[7].setTile(1);
  m_renderQueues[8].clear();
  m_renderQueues[8].setTile(1);
  z = -6;
  for (int i = -1; i <= 1; ++i)
  {
    x = i * 4 * TILE + mYScroll * TILE + 154;
    y = -15;//134 - 108;
    mvp = glm::translate(
      glm::mat4(1.0),
      glm::vec3(x, y, z - 1));
    mvp = glm::scale(mvp,
      glm::vec3(
        137.f,
        108.f,
        1.0f));
    m_renderQueues[6].setMVP(mvp);
    m_renderQueues[6].submit();

    x = i * 4 * TILE + mYScroll * TILE + 145;
    y = 45; // 134 - 50;
    mvp = glm::translate(
      glm::mat4(1.0),
      glm::vec3(x, y, z));
    mvp = glm::scale(mvp,
      glm::vec3(
        31.f,
        50.f,
        1.0f));
    m_renderQueues[7].setMVP(mvp);
    m_renderQueues[7].submit();

    x = i * 4 * TILE + mYScroll * TILE + 16;
    y = 21;//134 - 77;
    mvp = glm::translate(
      glm::mat4(1.0),
      glm::vec3(x, y, z));
    mvp = glm::scale(mvp,
      glm::vec3(
        65.f,
        77.f,
        1.0f));
    m_renderQueues[8].setMVP(mvp);
    m_renderQueues[8].submit();
  }

  //
  // DRAW IT
  //
  mTexGround.bind();
  m_renderQueues[0].draw(rs);
  mTexBack.bind();
  m_renderQueues[1].draw(rs);

  mTexProp1.bind();
  m_renderQueues[6].draw(rs);
  mTexPropJournal.bind();
  m_renderQueues[7].draw(rs);
  if (mStateValues->getValue("has_journal").flags)
  {
    mTexExit.bind();
    m_renderQueues[8].draw(rs);
  }

  mTexTube1.bind();
  m_renderQueues[2].draw(rs);
  mTexTube2.bind();

  m_renderQueues[3].draw(rs);
  if (mChoose)
  {
    mTexDialog.bind();
    m_renderQueues[5].draw(rs);
  }
}


void Screen0::init(const std::string& filename)
{

  mTexGround.loadPng("data/img/floor_256_128.png");
  mTexBack.loadPng("data/img/wall_loop.png");
  mTexTube1.loadPng("data/img/prop_lab_tube_with_cyborg.png");
  mTexTube2.loadPng("data/img/prop_lab_tube_broken.png");
  mTexDialog.loadPng("data/img/dialogue_box_mission.png");

  mTexProp1.loadPng("data/img/shelf.png");
  mTexPropJournal.loadPng("data/img/prop_board.png");
  mTexExit.loadPng("data/img/prop_portal.png");

  // Generate Render Queues
  m_renderQueues.resize(0);
  size_t n = 9;
  m_renderQueues.resize(n);

  m_renderQueues[0].x_res = 1;
  m_renderQueues[0].y_res = 1;
  m_renderQueues[0].mod_vert = 1;
  m_renderQueues[0].div_vert = 1;

  m_renderQueues[1].x_res = 1;
  m_renderQueues[1].y_res = 1;
  m_renderQueues[1].mod_vert = 1;
  m_renderQueues[1].div_vert = 1;

  m_renderQueues[2].x_res = 256.0f / 46.0f;//46
  m_renderQueues[2].y_res = 256.0f / 65.0f;//61
  m_renderQueues[2].mod_vert = 3;
  m_renderQueues[2].div_vert = 3;

  m_renderQueues[3].x_res = 1;
  m_renderQueues[3].y_res = 1;
  m_renderQueues[3].mod_vert = 1;
  m_renderQueues[3].div_vert = 1;

  // m_renderQueues[4].x_res = 512.0f / 80.0f;
  // m_renderQueues[4].y_res = 512.0f / 80.0f;
  // m_renderQueues[4].mod_vert = 5;
  // m_renderQueues[4].div_vert = 5;

  m_renderQueues[5].x_res = 1;
  m_renderQueues[5].y_res = 1;
  m_renderQueues[5].mod_vert = 1;
  m_renderQueues[5].div_vert = 1;

    m_renderQueues[6].x_res = 1;// 137;
    m_renderQueues[6].y_res = 1; //108;
    m_renderQueues[6].mod_vert = 1;
    m_renderQueues[6].div_vert = 1;

    m_renderQueues[7].x_res = 1;//31;
    m_renderQueues[7].y_res = 1;//50;
    m_renderQueues[7].mod_vert = 1;
    m_renderQueues[7].div_vert = 1;

    m_renderQueues[8].x_res = 1;//65;
    m_renderQueues[8].y_res = 1;//77;
    m_renderQueues[8].mod_vert = 1;
    m_renderQueues[8].div_vert = 1;
}


int Screen0::keyCallback(int key, int scancode, int action, int mods)
{
  return 0;
}
