
#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	time_t t = time(NULL);
	struct tm now;
	localtime_s(&now, &t);
	if (now.tm_mon != 3 || now.tm_mday != 1) {
		//today is not the april fool's day, show error message
		MessageBox(NULL, L"This program cannot be run in windows mode.", L"ERROR", MB_ICONERROR);
		return 0;
	}
	BOOLEAN stopRunning = FALSE;
	do {	
		//continues for 30 seconds
		for (int i = 0; i < 60; i++)
		{
			//need to be palced inside the loop
			HWND hwnd = GetDesktopWindow();
			HDC hdc = GetWindowDC(hwnd);
			RECT rect;
			GetWindowRect(hwnd, &rect);
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			//draw "Happy April Fool's Day!!!" every 0.5s
			Draw(hdc, width, height);
			//shift the screen towards lowerleft every 1s
			if (i % 2 == 0)Shift(hdc, width, height);
			//inverse the screen every 1.5s
			if (i % 3 == 0)Inverse(hdc, width, height);
			//reverse the screen color every 2.5s
			if (i % 5 == 0)Reverse(hdc, width, height);
			Sleep(500);
		}
		//ask you if you want to watch this again
		//but you need to choose "yes" to end this program
		if (MessageBox(NULL,
			L"Happy april fool's day!!!\nDo you want to restart this program from the beginning?",
			L"Watch again?", MB_ICONWARNING | MB_YESNO) == IDYES) {
			stopRunning = TRUE;
			MessageBox(NULL, L"Thank you!", L"The end", MB_ICONINFORMATION);
		}
		//you chose "no" and it restarts
		else {
			MessageBox(NULL,
				L"But you are fooled AGAIN!\nChoose wisely next time!",
				L"HAHA!", MB_ICONINFORMATION);
		}
	} while (!stopRunning);
	return 0;
}

void Draw(HDC hdc, int scrWidth, int scrHeight) {

	int bitmapWidth = 850;
	int bitmapHeight = 450;


	HFONT hFont = CreateFont(150, 0, 0, 0, FW_BOLD, TRUE, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Comic Sans MS");

	HDC hMemDC = CreateCompatibleDC(hdc);

	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, bitmapWidth, bitmapHeight);

	HBITMAP oldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	HFONT oldFont = (HFONT)SelectObject(hMemDC, hFont);

	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, 0xffffff);
	RECT rect;
	SetRect(&rect, 0, 0, bitmapWidth, bitmapHeight);
	DrawText(hMemDC, L"Happy\n   April Fool's\n      Day!!!", -1, &rect, DT_TOP | DT_LEFT);

	BitBlt(hdc, (scrWidth - bitmapWidth) / 2, (scrHeight - bitmapHeight) / 2,
		bitmapWidth, bitmapHeight, hMemDC, 0, 0, SRCINVERT);

	SelectObject(hMemDC, oldBitmap);
	SelectObject(hMemDC, oldFont);

	DeleteObject(hBitmap);
	DeleteObject(hFont);
	DeleteDC(hMemDC);

}

void Shift(HDC hdc, int scrWidth, int scrHeight) {
	BitBlt(hdc, 25, 25, scrWidth, scrHeight, hdc, 0, 0, SRCCOPY);
	//StretchBlt(hdc, 25, 25, scrWidth - 50, scrHeight - 50, hdc, 0, 0, scrWidth, scrHeight, SRCCOPY);
}

void Inverse(HDC hdc, int scrWidth, int scrHeight) {
	StretchBlt(hdc, scrWidth, scrHeight, -scrWidth, -scrHeight, hdc, 0, 0, scrWidth, scrHeight, SRCCOPY);
}

void Reverse(HDC hdc, int scrWidth, int scrHeight) {
	BitBlt(hdc, 0, 0, scrWidth, scrHeight, hdc, 0, 0, NOTSRCCOPY);
}
