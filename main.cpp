#include "pch.h"
#include "Point.h"
#include "Leaf.h"
#include "FriendlyLeaf.h"
#include "CoreLeaf.h"

using namespace std;

const int ALL_ENEMIES = 3;
const int ALL_FRIENDLY = 4;

int x;

vector <FriendlyLeaf> friendlyLeafs;

CoreLeaf Core(300, 200, 0, 50);

HDC hdc; //Контекст видеокарты

WNDCLASS NewWindowsClass(HBRUSH Color, HCURSOR Cursor, HINSTANCE hInstance, HICON Icon, LPCWSTR name, WNDPROC procedure);
LRESULT CALLBACK MainProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	srand(time(NULL));

	WNDCLASS MainWindow = NewWindowsClass((HBRUSH)CreateSolidBrush(RGB(255, 255, 255)), LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"Main", MainProcedure);

	if (!RegisterClassW(&MainWindow)) { return -1; }
	
	/* Заполняем вектор листов, оказывающих положительные эффекты */
	for (int i = 0; i < ALL_FRIENDLY; i++) {
		friendlyLeafs.push_back(FriendlyLeaf(rand() % 600, rand () % 400, 1, rand() % 10 + 1, RGB(0, 255, 0)));
	}

	MSG MainWindowMessage = { 0 };

	CreateWindowW(L"Main", L"Figures", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 600, 400, NULL, NULL, NULL, NULL);

	while (GetMessage(&MainWindowMessage, NULL, NULL, NULL)) {
		TranslateMessage(&MainWindowMessage);
		DispatchMessage(&MainWindowMessage);
	}

	cin.get();
	return 0;
}

WNDCLASS NewWindowsClass(
	HBRUSH BGCOLOR, /* Цвет бэкграунда*/
	HCURSOR CURSOR, /* Курсор */
	HINSTANCE hInst, /* Дескриптор приложения */
	HICON hIcon, /* Иконка */
	LPCWSTR Name, /* Имя окна*/
	WNDPROC Procedure /* Имя коллбэк процедуры */
) {
	WNDCLASS Window = { 0 };

	Window.hbrBackground = BGCOLOR;
	Window.hCursor = CURSOR;
	Window.hInstance = hInst;
	Window.hIcon = hIcon;
	Window.lpszClassName = Name;
	Window.lpfnWndProc = Procedure;

	return Window;
}

LRESULT CALLBACK MainProcedure
(
	HWND hwnd, /* Дескриптор окна*/
	UINT msg, /* Сообщение для обработки */
	WPARAM wparam,
	LPARAM lparam
)
{
	switch (msg) {

	/* Событие создания*/
	case WM_CREATE: {
		SetTimer(hwnd, 1, 5, NULL);
		break;
	}

	/* Событие уничтожения */
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	case WM_TIMER: {

		Core.createHitbox();

		/* Обрабатываем дружелюбные объекты типа Leaf */
		for (int i = 0; i < ALL_FRIENDLY; i++) {
			friendlyLeafs[i].createHitbox();
			bool isIntersect = friendlyLeafs[i].isIntersection(
				Core.getHB().first.first,
				Core.getHB().first.second,
				Core.getHB().second.first,
				Core.getHB().second.second
			);


			if (isIntersect == true) {
				Core.setHP(Core.getHP() + friendlyLeafs[i].Heal());
			}

			if (friendlyLeafs[i].getY() > 600 || isIntersect == true) {
				int X = rand() % 600;
				int Y = -10;
				friendlyLeafs[i].setCoordinates(X, Y);
			}
		}



		InvalidateRect(hwnd, NULL, TRUE);
		break;
	}

	case WM_KEYDOWN: {
		switch (LOWORD(wparam)) {

		case VK_LEFT: {
			Core.setCoordinates(Core.getX() - 10, Core.getY());
			break;
		}

		case VK_RIGHT: {
			Core.setCoordinates(Core.getX() + 10, Core.getY());
			break;
		}

		}
	}

	/* Событие отрисовки */
	case WM_PAINT: {
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);

		Core.Show();

		for (int i = 0; i < ALL_FRIENDLY; i++) {
			friendlyLeafs[i].move();
		}

		EndPaint(hwnd, &ps);
		break;
	}


	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}