#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "../include/Window.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>
#include <gl/GL.h>
#include <gl/GLU.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);
Window::Window(HINSTANCE hInstance, int width, int height, const char *title) {
  const char *CLASS_NAME = "OpenGLWindow";

  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  RegisterClass(&wc);

  hwnd =
      CreateWindowEx(0, CLASS_NAME, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                     CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);

  hdc = GetDC(hwnd);

  PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR),                              // nSize
      1,                                                          // nVersion
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // dwFlags
      PFD_TYPE_RGBA,                                              // iPixelType
      32,                                                         // cColorBits
      0,
      0,
      0,
      0, // cRedBits, cRedShift, cGreenBits, cGreenShift
      0,
      0,
      0,
      0, // cBlueBits, cBlueShift, cAlphaBits, cAlphaShift
      0, // cAccumBits
      0,
      0,
      0,
      0,              // cAccumRedBits, Green, Blue, Alpha
      24,             // cDepthBits
      8,              // cStencilBits
      0,              // cAuxBuffers
      PFD_MAIN_PLANE, // iLayerType
      0,              // bReserved
      0,              // dwLayerMask
      0,              // dwVisibleMask
      0               // dwDamageMask
  };

  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 24;
  pfd.iLayerType = PFD_MAIN_PLANE;

  int format = ChoosePixelFormat(hdc, &pfd);
  SetPixelFormat(hdc, format, &pfd);

  hglrc = wglCreateContext(hdc);
  wglMakeCurrent(hdc, hglrc);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplWin32_Init(hwnd);
  ImGui_ImplOpenGL3_Init("#version 130"); // or your GL version

  ShowWindow(hwnd, SW_SHOW);
}

Window::~Window() {
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hglrc);
  ReleaseDC(hwnd, hdc);
}

bool Window::processMessages() {
  MSG msg = {};
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT)
      return false;
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return true;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam) {

  // Let ImGui handle the message first
  if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
    return true;

  // Your normal Windows message handling
  switch (uMsg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
    // Handle other messages like WM_SIZE if needed

  default:
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
}
