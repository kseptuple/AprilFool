#pragma once
#include <Windows.h>
#include <iostream>
#include <time.h>

void Draw(HDC, int,int);
void Shift(HDC,int, int);
void Inverse(HDC,int, int);
void Reverse(HDC, int, int);
DWORD WINAPI DoMain(LPVOID);