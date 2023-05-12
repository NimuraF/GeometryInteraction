#include "pch.h"
#include "Point.h"
#include "Leaf.h"
#include "FriendlyLeaf.h"
#include "CoreLeaf.h"
#include "BuffDuplicateHPLeaf.h"
#include "Bird.h"
#include "RedBird.h"

using namespace std;

const int ALL_ENEMIES = 4;
const int ALL_FRIENDLY = 4;

int x;
int bufftimer = 0;
int invulnerability = 0;
bool blink = false;

vector <FriendlyLeaf *> friendlyLeafs;
vector <EnemyBird*> EnemyBirds;

CoreLeaf Core(300, 200, 0, 50);

HDC hdc; //Контекст видеокарты

WNDCLASS NewWindowsClass(HBRUSH Color, HCURSOR Cursor, HINSTANCE hInstance, HICON Icon, LPCWSTR name, WNDPROC procedure);
LRESULT CALLBACK MainProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	srand(time(NULL));

	WNDCLASS MainWindow = NewWindowsClass((HBRUSH)CreateSolidBrush(RGB(255, 255, 255)), LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_QUESTION), L"Main", MainProcedure);

	if (!RegisterClassW(&MainWindow)) { return -1; }
	
	/* Заполняем вектор листов, просто добавляющих ХП */
	for (int i = 0; i < ALL_FRIENDLY - 1; i++) {
		friendlyLeafs.push_back(new FriendlyLeaf(rand() % 600, rand () % 400, 1, rand() % 10 + 1, RGB(0, 255, 0)));
	}

	/* Добавляем в вектор бафающий лист (может быть только 1) */
	friendlyLeafs.push_back(new BuffDuplicateHPLeaf(rand() % 600, - 100, 1, rand() % 10 + 5, RGB(0, 0, 180)));

	/* Заполняем вектор птиц врагов красными птицами, съедающими ХП в % от максимального */
	for (int i = 0; i < ALL_ENEMIES - 1; i++) {
		EnemyBirds.push_back(new RedBird(rand() % 300 - 50, rand() % 300, 2, rand() % 2));
	}

	/* Добавляем обычную птицу, которая прост наносит 10 урона */
	EnemyBirds.push_back(new EnemyBird(rand () % 300 - 50, rand() % 300, 2, rand() % 2));

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
		switch (wparam) {

		/* Основной таймер */
		case 1: {
			Core.createHitbox();

			/* Обрабатываем дружелюбные объекты IUSABLE типа Leaf */
			for (int i = 0; i < ALL_FRIENDLY; i++) {
				friendlyLeafs[i]->createHitbox();
				bool isIntersect = friendlyLeafs[i]->isIntersection(
					Core.getHB().first.first,
					Core.getHB().first.second,
					Core.getHB().second.first,
					Core.getHB().second.second
				);


				if (isIntersect == true) {
					if (bufftimer > 0) {
						Core.setHP(Core.getHP() + friendlyLeafs[i]->Heal() * 2);
					}
					else {
						Core.setHP(Core.getHP() + friendlyLeafs[i]->Heal());
					}
				}

				if (friendlyLeafs[i]->getY() > 600 || isIntersect == true) {
					int X = rand() % 600;
					int Y = -10;
					friendlyLeafs[i]->setCoordinates(X, Y);
				}
			}

			/* Обрабатываем опасные объекты IDANGER типа Bird */
			for (int i = 0; i < ALL_ENEMIES; i++) {

				EnemyBirds[i]->createHitbox();

				bool isIntersect = EnemyBirds[i]->isIntersection(
					Core.getHB().first.first,
					Core.getHB().first.second,
					Core.getHB().second.first,
					Core.getHB().second.second
				);

				

				if (isIntersect == true && invulnerability < 1) {
					if (bufftimer > 0) {
						Core.setHP(Core.getHP() - EnemyBirds[i]->dealtDamage(Core.getHP()) / 2);
					}
					else {
						Core.setHP(Core.getHP() - EnemyBirds[i]->dealtDamage(Core.getHP()));
					}
					invulnerability = 1;
				}

				if (EnemyBirds[i]->getX() <= -100
					|| EnemyBirds[i]->getX() >= 700
					|| EnemyBirds[i]->getY() <= -50
					|| EnemyBirds[i]->getY() >= 450
					) 
				{
					int X = rand() % 300;
					bool angle = rand() % 2;
					int Y = angle > 0 ? 400 : 0;
					EnemyBirds[i]->setCoordinates(X, Y);
					EnemyBirds[i]->setAngle(angle);
				}

			}

			if (bufftimer >= 100) {
				bufftimer = 0;
				KillTimer(hwnd, 9);
			}

			if (invulnerability >= 30) {
				invulnerability = 0;
				KillTimer(hwnd, 8);
			}
			else if (invulnerability > 0 && invulnerability < 30) {
				if (!blink) {
					blink = true;
				}
				else {
					blink = false;
				}
			}

			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}

		/* Таймер положительного эффекта */
		case 9: {
			bufftimer++;
			break;
		}

		case 8: {
			invulnerability++;
			break;
		}

		}
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

		if (invulnerability > 0) {
			if (!blink) {
				Core.Hide();
			}
			else {
				Core.Show();
			}
		}
		else {
			Core.Show();
		}


		for (int i = 0; i < ALL_FRIENDLY; i++) {
			friendlyLeafs[i]->move();
		}

		for (int i = 0; i < ALL_ENEMIES; i++) {
			EnemyBirds[i]->move();
		}

		wchar_t buffer[256];
		wsprintfW(buffer, L"%d", bufftimer);
		if (bufftimer < 100) {
			TextOut(hdc, 100, 100, buffer, 2);
		}
		else {
			TextOut(hdc, 100, 100, buffer, 3);
		}

		wchar_t buffer2[256];
		wsprintfW(buffer2, L"%d", invulnerability);
		TextOut(hdc, 10, 10, buffer2, 2);
		

		EndPaint(hwnd, &ps);
		break;
	}


	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

