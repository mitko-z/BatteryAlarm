#include <SFML/Graphics.hpp>
#include <string>
#include <cstring>
#include <Windows.h>
#include <shellapi.h>

HWND hWnd;
NOTIFYICONDATA Tray;
#define TITLE_WINDOW "SFML"

//void OnTrayLButtonDown(CPoint pt)
//{
//
//}

int main()
{
	//cout << "Window will be minimised in system tray for 5 seconds and reappear.";
	//Sleep(2000);

	////window handle
	//hWnd = FindWindow("ConsoleWindowClass", NULL);

	////hide the window
	//ShowWindow(hWnd, 0);

	////tray info
	//Tray.cbSize = sizeof(Tray);
	//Tray.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	//Tray.hWnd = hWnd;
	//strcpy_s(Tray.szTip, "My Application");
	//Tray.uCallbackMessage = WM_LBUTTONDOWN;
	//Tray.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	//Tray.uID = 1;

	////set the icon in tasbar tray
	//Shell_NotifyIcon(NIM_ADD, &Tray);


	//Sleep(5000);

	////remove the icon
	//Shell_NotifyIcon(NIM_DELETE, &Tray);
	//ShowWindow(hWnd, 1);

	//return 0;



	sf::RenderWindow window(sf::VideoMode(200, 200), TITLE_WINDOW);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		if (window.hasFocus() == false)
		{
			//window handle
			hWnd = FindWindow(TITLE_WINDOW, NULL);
			//hide the window
			ShowWindow(hWnd, 0);

			//tray info
			Tray.cbSize = sizeof(Tray);
			Tray.hIcon = LoadIcon(NULL, IDI_WINLOGO);
			Tray.hWnd = hWnd;
			//Tray.szTip = TITLE_WINDOW;
			strcpy_s(Tray.szTip, TITLE_WINDOW);
			Tray.uCallbackMessage = WM_LBUTTONDOWN;
			Tray.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
			Tray.uID = 1;

			//set the icon in tasbar tray
			Shell_NotifyIcon(NIM_ADD, &Tray);
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}



	return 0;
}