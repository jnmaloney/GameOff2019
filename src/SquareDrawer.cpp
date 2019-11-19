#include "SquareDrawer.h"
#include "shaders.h"
#include "MeshManager.h"


SquareDrawer::SquareDrawer()
{

}


SquareDrawer::~SquareDrawer()
{

}


void SquareDrawer::init()
{

    // GL Setup
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

     // Geometry pass shaders

  	const char vertexShaderSource[] =
  		"attribute vec4 vPosition;		                     \n"
      "uniform mat4 ModelLocal; \n"
      "uniform mat4 ViewProj; \n"
  		"void main()                                         \n"
  		"{                                                   \n"
  		"   gl_Position = ViewProj * (ModelLocal * vPosition);                         \n"
  		"}                                                   \n";

    const char fragmentShaderSource[] =
  		"precision mediump float;                     \n"
  		"void main()                                  \n"
  		"{                                            \n"
      "  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); \n"
  		"}                      \n";


  	//load vertex and fragment shaders
  	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
  	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  	m_program = buildProgram(vertexShader, fragmentShader, "vPosition", 0);


    m_uniformVP = glGetUniformLocation(m_program, "ViewProj");
    m_uniformML = glGetUniformLocation(m_program, "ModelLocal");
    m_attribute_v_coord = glGetAttribLocation(m_program, "vPosition");

    // addSquare(0, 0, 1, 1);
}


void SquareDrawer::addSquare(float x, float y, float w, float h)
{
  glm::mat4 t(1.0);
  t = glm::translate(t, glm::vec3(x, y, 0));
  t = glm::scale(t, glm::vec3(w, h, 1));
  m_squareList.push_back(t);
}


void SquareDrawer::draw(WindowManager* window)
{
  Mesh* mesh = MeshManager::get()->getMesh(0);

  float v_side = 1.0 / window->height;
  float near = 0.01f;
  float far = 1000.f;
  glm::mat4
  Projection = glm::ortho(
    -v_side * window->width,
     v_side * window->width,
    -v_side * window->height,
     v_side * window->height,
     (float)near,
     (float)far);

   // Camera View matrix
   glm::mat4
   View = glm::lookAt(
                 glm::vec3(0, 0, 10.f), // Camera in World Space
                 glm::vec3(0,  0, 0.f), // looks at
                 glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
                );

   // Calculate ViewProj
   glm::mat4 VP = Projection * View;

   //glm::mat4 ML(1.0);



  glUseProgram(m_program);

  glUniformMatrix4fv(m_uniformVP, 1, GL_FALSE, &VP[0][0]);

  for (std::vector<glm::mat4>::iterator i = m_squareList.begin(); i != m_squareList.end(); ++i)
  {
    glm::mat4 ML = *i;
    glUniformMatrix4fv(m_uniformML, 1, GL_FALSE, &ML[0][0]);

    glEnableVertexAttribArray(m_attribute_v_coord);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vbo_vertices);
    glVertexAttribPointer(
      m_attribute_v_coord,
      4,                  // number of elements per vertex, here (x,y,z,w)
      GL_FLOAT,           // the type of each element
      GL_FALSE,           // take our values as-is
      0,                  // no extra data between each position
      0                   // offset of first element
    );


    //glUniformMatrix4fv(m_uniformML, 1, GL_FALSE, &transforms.x[0][0]);

    // Draw Elements
    for (auto const elements : mesh->m_matIboElements)
    {
      // Render the element
      // - Calculate the size of the element (TODO)
      // - Set uniforms (colour)
      // - Draw

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements.second.elements);
      //int size = mesh->m_matElements[elements.first].size(); // TODO what?
      //int size = elements.second.size();
      // setRenderColour(c, uniformDiffuse);
      // c++;
      //std::cout << size << std::endl;

      //
      //              ----     DRAW     ----
      //
      glDrawElements(GL_TRIANGLES, elements.second.size, GL_UNSIGNED_SHORT, 0);

      //std::cout << size << std::endl;
      //std::cout << "Drawing " << std::endl;
    }
  }
}
