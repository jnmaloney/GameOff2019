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


clock_t start;
OdinEngine g_odin;
StateManager g_stateManager;

//Texture g_white;
//Mesh g_square;

  // AudioManager g_trackSounds;
  // AudioManager g_trackIntro;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  g_stateManager.getCurrentState()->keyCallback(key, scancode, action, mods);
}


EM_BOOL gamepad_callback(int eventType, const EmscriptenGamepadEvent *gamepadEvent, void *userData)
{
  //g_stateManager.getCurrentState()->gamepadCallback(eventType, gamepadEvent, userData);
  return true;
}


//
// Drawing
//
void loop()
{
  //
  // Gamepad
  //
  if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_SUCCESS)
  {
    //std::cout << "gamepad data" << std::endl;
    if (emscripten_get_num_gamepads() > 0)
    {
      //std::cout << "gamepad number" << std::endl;
      EmscriptenGamepadEvent status;
      if (emscripten_get_gamepad_status(0, &status) == EMSCRIPTEN_RESULT_SUCCESS)
      {
        //std::cout << "gamepad status" << std::endl;

        if (status.connected)
        {
          double axis_x = status.axis[0];
          double axis_y = status.axis[1];
          // bool button_a = status.digitalButton[status.mapping[1]];
          // bool button_b = status.digitalButton[status.mapping[2]];
          bool button_a = status.digitalButton[0];
          bool button_b = status.digitalButton[1];
          g_stateManager.getCurrentState()->gamepadUpdate(axis_x, axis_y, button_a, button_b);

          // for (int i = 0; i < 20; ++i)
          // {
          //   std::cout << i << " gamepad " << (int)status.mapping[i] << std::endl;
          // }
        }
      }
    }
  }

  //
  // Timing
  //
  double time_now = std::clock();
  double dt = (time_now - start) / (double) CLOCKS_PER_SEC;
  start = time_now;
  static const double step_max = 0.100;
  if (dt > step_max) dt = step_max;
  if (dt <= 0) return;

  //
  // OpenGL draw pass
  //
  g_odin.rs.start();
  g_stateManager.getCurrentState()->prestart(&g_odin.rs);
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


EM_BOOL contextlost(int eventType, const void *reserved, void *userData)
{

  std::cout << "contextlost" << std::endl;
  return 0;
}


EM_BOOL contextrest(int eventType, const void *reserved, void *userData)
{
  std::cout << "contextrest" << std::endl;
  return 0;
}


EM_BOOL resized(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
  std::cout << "resized" << std::endl;
  return 0;
}


EM_BOOL fullscreened(int eventType, const EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, void *userData)
{
  std::cout << "fullscreened" << std::endl;
  return 0;
}

//
// Initialise
//
int init()
{
  emscripten_set_fullscreenchange_callback("canvas", NULL, true, fullscreened);
  emscripten_set_resize_callback("canvas", NULL, true, resized);
  emscripten_set_webglcontextlost_callback("canvas", NULL, true, contextlost);
  emscripten_set_webglcontextrestored_callback("canvas", NULL, true, contextrest);

  //
  // Initialise Odin Engine 2019
  //
  g_odin.windowManager.width = 980;
  g_odin.windowManager.height = 526;
  g_odin.windowManager.init("Leapy Frog");
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

  // GamePad callback
  //EM_BOOL (*em_gamepad_callback_func)(int eventType, const EmscriptenGamepadEvent *gamepadEvent, void *userData)
  //emscripten_set_gamepadconnected_callback(void *userData, EM_BOOL useCapture, em_gamepad_callback_func callback)
  emscripten_set_gamepadconnected_callback(NULL, true, gamepad_callback);

  // Setting ortho mode
  g_odin.rs.modeOrtho(0., 0., 0.25 * 980, 0.25 * 526);

  // Load mesh
  // g_square.load_obj("data/square.obj");
  // g_square.upload_obj();
  // g_white.loadPng("data/white.png");

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
