#pragma once


#include "graphics.h"
#include <vector>
#include "RenderQueue.h"
#include "WindowManager.h"


class SquareDrawer
{
public:
  SquareDrawer();
  ~SquareDrawer();

  void init();

  void addSquare(float x, float y, float w, float h);

  void draw(WindowManager* window);

  void clear() { m_squareList.clear(); }

protected:

  std::vector<glm::mat4> m_squareList;

  RenderQueue m_renderQueue;

  GLuint m_program;
  GLint m_uniformML;
  GLint m_uniformVP;
  GLint m_attribute_v_coord;
};
