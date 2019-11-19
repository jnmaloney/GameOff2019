#include <stdio.h>
#include <ctime>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>
#endif

#include "OdinEngine.h"

#include "State.h"
#include "StateManager.h"

#include "MenuMain.h"
#include "MenuIntro.h"
#include "Screen1.h"
#include "ScreenIntro.h"
#include "ScreenTitle.h"
#include "ScreenPlayerFixed.h"
#include "Menu0.h"
#include "MenuIntro0.h"
#include "MenuElevator.h"
#include "OrbitCamera.h"


clock_t start;
OdinEngine g_odin;
StateManager g_stateManager;

Texture g_white;
Mesh g_square;

OrbitCamera cameraControl;


  // AudioManager g_trackSounds;
  // AudioManager g_trackIntro;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  g_stateManager.getCurrentState()->keyCallback(key, scancode, action, mods);
}


//
// Drawing
//
void loop()
{
  //double timer = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  double time_now = std::clock();
  double dt = (time_now - start) / (double) CLOCKS_PER_SEC;
  start = time_now;
  // if (dt > 30. / 1000.) dt = 30. / 1000.;
  // if (dt <= 0) return;

  //
  // OpenGL draw pass
  //
  //cameraControl.update(1.0);
  //g_odin.rs.setCameraPos(cameraControl.getPos(), cameraControl.pivot);
  //g_odin.rs.setCameraPos(glm::vec3(0, 0, 200), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  g_odin.rs.start();
  // g_odin.rs.bindMesh(&g_square);
  // g_odin.rs.bindMeshElement(&g_square, 0);
  // g_white.bind();
  g_stateManager.getCurrentState()->draw(&g_odin.rs, dt);
  g_odin.rs.end();

  //
  // Menu draw pass
  //
  g_odin.menuManager.predraw();
  g_stateManager.getCurrentState()->drawUI();
  g_odin.menuManager.postdraw(g_odin.windowManager);

  g_stateManager.update();
}


//
// Initialise
//
int init()
{
  //
  // Initialise Odin Engine 2019
  //
  g_odin.windowManager.width = 980;
  g_odin.windowManager.height = 526;
  g_odin.windowManager.init("Game Title");
  g_odin.menuManager.fontNameTTF = "data/font/DisposableDroidBB.ttf";
  g_odin.menuManager.init(g_odin.windowManager);
  g_odin.rs.init();

  // Init game..
  srand(time(NULL));

  //
  // Set up the State Set for the game
  //
  State* state0 = new State();
  State* state1 = new State();
  State* state2 = new State();
  g_stateManager.addState(state0);
  g_stateManager.addState(state1);
  g_stateManager.addState(state2);
  ScreenTitle* screen = new ScreenTitle();
  screen->init("");
  state0->addElement(screen);
  ScreenIntro* screen0 = new ScreenIntro();
  screen0->init("");
  state1->addElement(screen0);
  Screen1* screen1 = new Screen1();
  screen1->init("");
  state2->addElement(screen1);

  // Timer
  start = clock();

  // Key callback
  glfwSetKeyCallback(g_odin.windowManager.g_window, key_callback);

  // Setting ortho mode
  g_odin.rs.modeOrtho(0., 0., 0.25 * 980, 0.25 * 526);
  //g_odin.rs.modeOrtho(0., 0., 980, 526);

  glClearColor(50.0/255.0, 50.0/255.0, 50.0/255.0, 1.0);

  // Load mesh
  g_square.load_obj("data/square.obj");
  g_square.upload_obj();
  g_white.loadPng("data/white.png");

  std::cout << "end init() ok" << std::endl;

  return 0;
}


void quit()
{
  glfwTerminate();
}


extern "C" int main(int argc, char** argv)
{
  if (init() != 0) return 1;

  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
  #endif

  quit();

  return 0;
}
