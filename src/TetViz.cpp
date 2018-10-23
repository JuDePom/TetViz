#include "TetViz.h"

#include <LibSL/Mesh/Mesh.h>
#include <LibSL/Mesh/MeshFormat_msh.h>

#include <LibSL/LibSL.h>
#include <LibSL/GPUHelpers/GPUHelpers.h>

/*LIBSL_WIN32_FIX

TetViz *TetViz::s_instance = nullptr;

//-------------------------------------------------------
TetViz::TetViz() {
}

//-------------------------------------------------------
void TetViz::mainRender()
{
  glClearColor(0.f, 0.f, 0.f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Instance()->draw();

  ImGui::Render();
}

//-------------------------------------------------------
void TetViz::mainOnResize(uint width, uint height) {


  Instance()->m_size = ImVec2((float)width, (float)height);
  Instance()->m_Trackball.setWindowSize(width, height);

}

//-------------------------------------------------------
void TetViz::mainKeyPressed(uchar k)
{
}

//-------------------------------------------------------
void TetViz::mainScanCodePressed(uint sc)
{
  if (sc == LIBSL_KEY_SHIFT) {
    ImGui::GetIO().KeyShift = true;
  }
}

//-------------------------------------------------------
void TetViz::mainScanCodeUnpressed(uint sc)
{
  if (sc == LIBSL_KEY_SHIFT) {
    ImGui::GetIO().KeyShift = false;
  }
}

//-------------------------------------------------------
void TetViz::mainMouseMoved(uint x, uint y)
{
  Instance()->m_Trackball.update(x, y);
}

//-------------------------------------------------------
void TetViz::mainMousePressed(uint x, uint y, uint button, uint flags)
{
  // trackball
  if (flags & LIBSL_BUTTON_DOWN) {
    TetViz::Instance()->m_Trackball.buttonPressed(button, x, y);
  } else if (flags & LIBSL_BUTTON_UP) {
    TetViz::Instance()->m_Trackball.buttonReleased(button);
  }
}

//-------------------------------------------------------
void TetViz::launch()
{
  TetViz *viz = TetViz::Instance();
  try {
    // create window
    SimpleUI::init(800, 600, "");

    // attach functions
    SimpleUI::onRender             = viz->mainRender;
    SimpleUI::onKeyPressed         = viz->mainKeyPressed;
    SimpleUI::onScanCodePressed    = viz->mainScanCodePressed;
    SimpleUI::onScanCodeUnpressed  = viz->mainScanCodeUnpressed;
    SimpleUI::onMouseButtonPressed = viz->mainMousePressed;
    SimpleUI::onMouseMotion        = viz->mainMouseMoved;
    SimpleUI::onReshape            = viz->mainOnResize;

    // imgui
    SimpleUI::bindImGui();
    SimpleUI::initImGui();
    SimpleUI::onReshape(800, 600);
    
    // setup view
    Transform::perspective(LIBSL_PROJECTION_MATRIX, float(M_PI / 4.0), 800 / float(600), 0.001f, 100.0f);

    // main loop
    SimpleUI::loop();

    // clean up
    SimpleUI::terminateImGui();

    // shutdown UI
    SimpleUI::shutdown();
  } catch (Fatal& e) {
    std::cerr << Console::red << e.message() << Console::gray << std::endl;
  }
}

int main(int argc, char **argv) {
  TetViz::launch();
  return 0;
}

// -----------------------------------------------
MeshFormat_msh mformat;
TriangleMesh_Ptr mesh;
MeshRenderer<MeshFormat_msh::t_VertexFormat>*  g_Renderer;

bool TetViz::draw() {
  if (ImGui::GetIO().KeysDown['o']) {
    const char* file = "E:/TetViz/meshs/CuteOcto_.msh";
    
    mesh = TriangleMesh_Ptr(mformat.load(file));

    std::cerr << "nbTri: " << mesh->numTriangles() << std::endl;
    g_Renderer = new MeshRenderer<MeshFormat_msh::t_VertexFormat>(mesh.raw());
    
    
  }

  v2f res(800, 600);
  m4x4f persp = perspectiveMatrixGL(float(M_PI) / 4.0f, res[0] / res[1], ZN, ZF);
  m4x4f view  = m_Trackball.matrix();

  

  
  
  if (g_Renderer) {
    LibSL::GPUHelpers::Transform::set(LIBSL_MODELVIEW_MATRIX, TrackballUI::matrix());
    LibSL::GPUHelpers::clearScreen(LIBSL_COLOR_BUFFER | LIBSL_DEPTH_BUFFER,  0, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    g_Renderer->render();
  }

  glLineWidth(2.5);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(15, 15, 15);
  glEnd();

  return true;
}
*/










/* --------------------------------------------------------------------
Author: Sylvain Lefebvre    sylvain.lefebvre@sophia.inria.fr

Simple Library for Graphics (LibSL)

This software is a computer program whose purpose is to offer a set of
tools to simplify programming real-time computer graphics applications
under OpenGL and DirectX.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
-------------------------------------------------------------------- */

// --------------------------------------------------------------
// Triangle Mesh tutorial
// --------------------------------------------------------------

#include <iostream>
#include <ctime>
#include <cmath>

// --------------------------------------------------------------

#include <LibSL/LibSL.h>

#ifdef OPENGL
#include <LibSL/LibSL_gl.h>
#endif

#ifdef DIRECT3D
#include <LibSL/LibSL_d3d.h>
#endif

using namespace LibSL::Mesh;
using namespace LibSL;
// --------------------------------------------------------------

using namespace std;

// --------------------------------------------------------------

LIBSL_WIN32_FIX

// --------------------------------------------------------------

#define SCREEN_W 1024
#define SCREEN_H 768

MeshFormat_msh                                 g_meshformat;
TriangleMesh_Ptr                               g_Mesh;
MeshRenderer<MeshFormat_msh::t_VertexFormat>*  g_Renderer;

// --------------------------------------------------------------

void mainKeyboard(unsigned char key)
{
  static float speed = 1.0f;
  static char last = ' ';

  if (key == 'q') {
    TrackballUI::exit();
  } else if (key == ' ') {
    static bool swap = true;
    if (swap) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    swap = !swap;
  }
}

// --------------------------------------------------------------

void mainAnimate(double time, float elapsed)
{
}

// --------------------------------------------------------------

void mainRender()
{
  /// render on screen

  GPUHelpers::clearScreen(LIBSL_COLOR_BUFFER | LIBSL_DEPTH_BUFFER,
    0, 0, 1);

  GPUHelpers::Transform::set(LIBSL_MODELVIEW_MATRIX, TrackballUI::matrix());

  //g_Renderer->render();

  ImGui::Button("test", ImVec2(100, 100));

  /// draw edges

  glLineWidth(2.5);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);

  ForIndex(i_mesh, g_meshformat.m_meshes.size() / 4) {
    v3f col = randomColorFromIndex(i_mesh);
    glColor3fv(&col[0]);
    
    v3f barycenter(0.0f);
    ForIndex(off, 4) {
      MeshFormat_msh::t_VertexData *vertex = reinterpret_cast<MeshFormat_msh::t_VertexData*>(g_Mesh->vertexDataAt(g_meshformat.m_meshes[i_mesh * 4 + off]));
      barycenter += vertex->pos / 4.0f;
    }
    

    if (barycenter[0] > 0.5f) {
      ForIndex(off, 4) {
        ForIndex(i, 3) {
          MeshFormat_msh::t_VertexData *vertex = reinterpret_cast<MeshFormat_msh::t_VertexData*>(g_Mesh->vertexDataAt(g_meshformat.m_meshes[i_mesh * 4 + (off + i) % 4]));
          glVertex3f(vertex->pos[0], vertex->pos[1], vertex->pos[2]);
        }
      }
    }
  }
  glEnd();


  /// draw bbox

  v3f min = g_Mesh->bbox().minCorner();
  v3f max = g_Mesh->bbox().maxCorner();

  glLineWidth(2.5);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(min[0], min[1], min[2]); glVertex3f(max[0], min[1], min[2]);
  glVertex3f(max[0], min[1], min[2]); glVertex3f(max[0], max[1], min[2]);
  glVertex3f(max[0], max[1], min[2]); glVertex3f(min[0], max[1], min[2]);
  glVertex3f(min[0], max[1], min[2]); glVertex3f(min[0], min[1], min[2]);

  glVertex3f(min[0], min[1], max[2]); glVertex3f(max[0], min[1], max[2]);
  glVertex3f(max[0], min[1], max[2]); glVertex3f(max[0], max[1], max[2]);
  glVertex3f(max[0], max[1], max[2]); glVertex3f(min[0], max[1], max[2]);
  glVertex3f(min[0], max[1], max[2]); glVertex3f(min[0], min[1], max[2]);

  glVertex3f(min[0], min[1], min[2]); glVertex3f(min[0], min[1], max[2]);
  glVertex3f(max[0], min[1], min[2]); glVertex3f(max[0], min[1], max[2]);
  glVertex3f(max[0], max[1], min[2]); glVertex3f(max[0], max[1], max[2]);
  glVertex3f(min[0], max[1], min[2]); glVertex3f(min[0], max[1], max[2]);

  glEnd();

}

/* -------------------------------------------------------- */

int main(int argc, char **argv)
{
  try {

    /// init TrackballUI UI (glut clone for both GL and D3D, with a trackball)
    cerr << "Init TrackballUI   ";
    TrackballUI::onRender = mainRender;
    TrackballUI::onKeyPressed = mainKeyboard;
    TrackballUI::onAnimate = mainAnimate;
    TrackballUI::init(SCREEN_W, SCREEN_H);
    TrackballUI::setCenter(V3F(.5f, .5f, .5f));
    cerr << "[OK]" << endl;

    SimpleUI::bindImGui();
    SimpleUI::initImGui();
    /// help
    printf("[q]     - quit\n");

#ifdef DIRECT3D
    /// d3d init
    LPDIRECT3DDEVICE9 d3d = LIBSL_DIRECT3D_DEVICE;
    d3d->SetRenderState(D3DRS_LIGHTING, FALSE);
    d3d->SetRenderState(D3DRS_ZENABLE, TRUE);
    d3d->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
#endif

#ifdef OPENGL
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);
#endif

    // open mesh
    cerr << "Loading mesh      ";
    
    g_Mesh = TriangleMesh_Ptr(g_meshformat.load("D:/Github/TetViz/meshs/CuteOcto_.msh"));
    g_Mesh->scaleToUnitCube();
    cerr << "[OK]" << endl;
    cerr << sprint("  mesh contains %d vertices and %d triangles\n", g_Mesh->numVertices(), g_Mesh->numTriangles());
    
    g_Mesh->computeBBox();
    cerr << "bbox center: " << g_Mesh->bbox().center() << endl;
    cerr << "bbox min corner: " << g_Mesh->bbox().minCorner() << endl;
    cerr << "bbox max corner: " << g_Mesh->bbox().maxCorner() << endl;

    cerr << "Creating renderer ";
    g_Renderer = new MeshRenderer<MeshFormat_msh::t_VertexFormat>(g_Mesh.raw());
    cerr << "[OK]" << endl;

    // setup view
    Transform::perspective(LIBSL_PROJECTION_MATRIX, float(M_PI / 4.0), SCREEN_W / float(SCREEN_H), 0.001f, 100.0f);

    // init trackball viewpoint
    TrackballUI::trackball().rotation() = quatf(-0.0006f, -0.9992f, -0.0349f, 0.0185f);
    TrackballUI::trackball().translation() = V3F(-0.479f, -0.408f, -2.263f);

    /// main loop
    TrackballUI::loop();

    /// clean exit

    // shutdown UI
    TrackballUI::shutdown();

  } catch (Fatal& e) {
    cerr << e.message() << endl;
    return (-1);
  }

  return (0);
}

/* -------------------------------------------------------- */
