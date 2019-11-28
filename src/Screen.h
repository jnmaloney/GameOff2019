#pragma once


#include <vector>
#include "StateElement.h"
#include "RenderQueue.h"


class RenderSystem;


//
// A RenderQueue based elemets
//
class Screen : public StateElement
{
public:

  Screen();
  virtual ~Screen();

  void draw(RenderSystem* rs);

  virtual void draw(RenderSystem* rs, float timer) {}
  virtual int keyCallback(int key, int scancode, int action, int mods) { return 0; }
  virtual int gamepadUpdate(double x, double y, int a, int b) { return 0; }


  virtual void prestart(RenderSystem* rs) {}

protected:

  std::vector<RenderQueue> m_renderQueues;
};
