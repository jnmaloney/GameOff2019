#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__


#include "RenderQueue.h"


class GameObject
{
public:
  GameObject();
  ~GameObject();

  void init();
  void update(float dt);
  void draw();

  // Transform
  glm::mat4 mTransform;

  // Drawable
  RenderQueue mRenderQueue;

  // png, width, height

protected:
};


#endif /* end of include guard: GAME_OBJECT */
