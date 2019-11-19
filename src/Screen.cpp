#include "Screen.h"


Screen::Screen()
{

}


Screen::~Screen()
{

}


void Screen::draw(RenderSystem* rs)
{
  size_t n = m_renderQueues.size();
  for (size_t i = 0; i < n; ++i)
  {
    m_renderQueues[n - i - 1].draw(rs);
  }
}
