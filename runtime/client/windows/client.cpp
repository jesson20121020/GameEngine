﻿// client.cpp : 定义应用程序的入口点。
//

#include "../Scene.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "imconfig.h"
#include "client.h"
#include "framework.h"
#include "../glheader.h"
#include <iostream>
#include "../FileUtils.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                     // 当前实例
WCHAR szTitle[MAX_LOADSTRING];       // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

HDC hdc;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam);

BOOL InitOpenGLEnv(HWND hWnd) {
  hdc = GetDC(hWnd);
  PIXELFORMATDESCRIPTOR pfd;
  memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
  pfd.nVersion = 1;
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.cColorBits = 32;
  pfd.cDepthBits = 24;
  pfd.cStencilBits = 8;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

  int pixelFormat = ChoosePixelFormat(hdc, &pfd);
  SetPixelFormat(hdc, pixelFormat, &pfd);
  HGLRC hrc = wglCreateContext(hdc);
  wglMakeCurrent(hdc, hrc);

  return true;
}


void onBeginDraw()
{
	glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    if (ImGui::GetCurrentContext()) {
      ImGui::NewFrame();

      RenderImGui();
      // ImGui::ShowDemoWindow();

      ImGui::Render();
    }
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void initImGui(HWND hWnd)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(FileUtils::getInstance()->getFullFilePath("fonttitle02.ttf").c_str(), 14.0f, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplWin32_EnableDpiAwareness();
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 420");
}

void destroyImGui()
{
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void onDraw()
{
	Renderer();
    drawImGui();
}

void onPostDraw()
{
	glFlush();
}


static const unsigned int s_combinetion_number_table[15][15] = {
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 4, 6, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 5, 10, 10, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 6, 15, 20, 15, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 7, 21, 35, 35, 21, 7, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 8, 28, 56, 70, 56, 28, 8, 1, 0, 0, 0, 0, 0, 0 },
    { 1, 9, 36, 84, 126, 126, 84, 36, 9, 1, 0, 0, 0, 0, 0 },
    { 1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1, 0, 0, 0, 0 },
    { 1, 11, 55, 165, 330, 462, 462, 330, 165, 55, 11, 1, 0, 0, 0 },
    { 1, 12, 66, 220, 495, 792, 924, 792, 495, 220, 66, 12, 1, 0, 0 },
    { 1, 13, 78, 286, 715, 1287, 1716, 1716, 1287, 715, 286, 78, 13, 1, 0 },
    { 1, 14, 91, 364, 1001, 2002, 3003, 3432, 3003, 2002, 1001, 364, 91, 14, 1 }
};

/// <summary>
/// 计算排列组合, 这里直接读表，提高计算速度（由编辑器端限制n的个数，防止这里越界）
/// </summary>
/// <param name="n"></param>
/// <param name="k"></param>
/// <returns></returns>
unsigned long CalcCombinetionNumber(int n, int k)
{
    return s_combinetion_number_table[n][k];
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: 在此处放置代码。

  // 初始化全局字符串
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  char  szPath[MAX_PATH];
  PSTR  lpFilename;

  // Retrieve the full path for the current module.
  if (GetModuleFileName(NULL, szPath, sizeof szPath) == 0)
      return -1;

  // Get a pointer to the filename part of
  // the string containing the full path. 
  lpFilename = (strrchr(szPath, '\\') + 1);

  std::string exePath = szPath;
  std::string exeDir = "";
  std::string exeName = "";
  size_t pos = exePath.rfind('\\');
  if (pos != std::string::npos) {
      exeDir = exePath.substr(0, pos);
      exeName = exePath.substr(pos + 1);
  }

  FileUtils::getInstance()->addSearchPath(exeDir + "/Resources", true);

  auto ret = CalcCombinetionNumber(10, 5);

  // 执行应用程序初始化:
  if (!InitInstance(hInstance, nCmdShow)) {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

  MSG msg;

  // 主消息循环:
  while (GetMessage(&msg, nullptr, 0, 0)) {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

	onBeginDraw();
	onDraw();
	onPostDraw();
    SwapBuffers(hdc);
  }

  Destroy();
  destroyImGui();
  return (int)msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENT);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  hInst = hInstance; // 将实例句柄存储在全局变量中

  HWND hWnd =
      CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                    0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd) {
    return FALSE;
  }

  InitOpenGLEnv(hWnd);

  auto x = glGetString(GL_VERSION);
  std::cout << x;

  WINDOWINFO info;
  RECT rect;
  ::GetWindowRect(hWnd, &rect);

  initImGui(hWnd);
  Init(rect.right - rect.left, rect.bottom - rect.top);

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
    LRESULT result = 0;
    result = ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
  switch (message) {
  case WM_COMMAND: {
    int wmId = LOWORD(wParam);
    // 分析菜单选择:
    switch (wmId) {
    case IDM_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  } break;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: 在此处添加使用 hdc 的任何绘图代码...
    EndPaint(hWnd, &ps);
  } break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  
  return result;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);
  switch (message) {
  case WM_INITDIALOG:
    return (INT_PTR)TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR)TRUE;
    }
    break;
  }
  return (INT_PTR)FALSE;
}
