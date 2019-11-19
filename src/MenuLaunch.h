#pragma once


class SceneManager;
class GameState;


class MenuLaunch // : public StateElement
{
public:
  MenuLaunch();
  ~MenuLaunch();
  void frame();

  SceneManager* sm = 0;
  GameState* gs = 0;

protected:

  void mainMenu();
};
