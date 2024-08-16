
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <conio.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <tuple>
#include <fstream>
#include <experimental/filesystem>
#include <filesystem>

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>

#pragma warning(disable: 4996)

#include "GlobalVars.h"
#include "Triangle.h"
#include "AActor.h"

std::vector<class AActor*> actors;
std::vector<int> typesOfActors;

HWND GetConsoleHwnd()
{
    HWND hwnd;
    wchar_t Old[200];
    GetConsoleTitle(Old, 200);
    SetConsoleTitle(L"Console");
    Sleep(40);
    hwnd = FindWindow(NULL, L"Console");
    SetConsoleTitle(Old);
    return hwnd;
}

RECT desktop_rect_;
HWND desktop_ = GetConsoleHwnd();

void setWall()
{
    for (size_t i = 0; i < SCREEN_HEIGHT; ++i)
    {
        std::cout << '#';

        for (size_t j = 1; j < SCREEN_WIDTH - 1; ++j)
        {
            std::cout << ((!i || i == SCREEN_HEIGHT - 1) ? '#' : ' ');
        }

        std::cout << '#' << '\n';
    }
}

void SetWindowSize()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = { 0, 0 };

    SetConsoleScreenBufferSize(consoleHandle, size);
    SMALL_RECT rect = { 0, 0, 80, 50 };
    SetConsoleWindowInfo(consoleHandle, TRUE, &rect);
}

POINT NewMouseCoords;
POINT OldMouseCoords;

int WindowX()
{
    return desktop_rect_.right;
}

int WindowY()
{
    return desktop_rect_.bottom;
}

void ClipMouse()
{
    RECT r2;
    RECT rr;

    GetWindowRect(desktop_, &rr);

    SetRect(&r2, rr.left, rr.top, rr.right, rr.bottom);
    ClipCursor(&r2);
}

void SetMouseSettings()
{
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

    SystemParametersInfo(SPI_SETCURSORS, 0, NULL, 0);

    /*Запретить выделение консоли*/
    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    SetConsoleMode(hin, ENABLE_MOUSE_INPUT);
}

void BlockMouseMovement()
{
    SetCursorPos(WindowX() / 2, WindowY() / 2);
}

void GetNewMousePos()
{
    if (NewMouseCoords.x > desktop_rect_.right - 10 || NewMouseCoords.x < desktop_rect_.left + 10 || NewMouseCoords.y > desktop_rect_.bottom - 10
        || NewMouseCoords.y < desktop_rect_.top + 10)
    {
        BlockMouseMovement();
        OldMouseCoords = { WindowX() / 2, WindowY() / 2 };
    }
    GetCursorPos(&NewMouseCoords);
}

void EnableANSICode()
{
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

extern void SpawnDefaultFigures();
extern void hideCursor(int off = 1);
extern void DrawMenu();
extern void MenuImpl();

void TrianglePreLoadTextures()
{
    std::vector<std::string> preLoadTexturesNames;
    preLoadTexturesNames.push_back("Textures/missing_textures/missing_textures.bmp");

    std::string path = std::experimental::filesystem::current_path().string();
    path += "\\Textures";

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        std::string fn;
        fn.insert(0, entry.path().string().c_str() + entry.path().string().find_last_of('\\') + 1);

        if (fn.find(".bmp") != std::string::npos)
        {
            preLoadTexturesNames.push_back("Textures/" + fn);
        }
    }

    Triangle::PreLoadTextures(preLoadTexturesNames);
}

void PreLoad()
{
    TrianglePreLoadTextures();
}

int main()
{
    PreLoad();

    EnableANSICode();

    GetWindowRect(desktop_, &desktop_rect_);
    int currentFigureIndex = 2;

    SpawnDefaultFigures();

    //SetWindowSize();
    setWall();
    hideCursor();
    ClipMouse();
    SetMouseSettings();
    DrawMenu();

    for (size_t i = 0; i < actors.size(); ++i)
        actors[i]->BeginPlay();

    GetCursorPos(&OldMouseCoords);

    MenuImpl();
}