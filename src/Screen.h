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
  
protected:

  std::vector<RenderQueue> m_renderQueues;
};
