#include <SFML/Graphics.hpp>
//#include <string>
#include <cstring> // strcpy_s
#include <Windows.h>
#include <shellapi.h>
//#include "SystemTray.h"

HWND hWnd;
NOTIFYICONDATA Tray;
#define TITLE_WINDOW "SFML window"

int main()
{
	// SFML makes a window
	sf::RenderWindow window(sf::VideoMode(200, 200), TITLE_WINDOW);
	//window handle
	hWnd = FindWindow(TITLE_WINDOW, NULL);

	//CSystemTray iconHandler;

	// TODO remove the shape below
	// standard SFML test figure
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);


	//tray info
	/*Tray.cbSize = sizeof(Tray);
	Tray.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	Tray.hWnd = hWnd;
	strcpy_s(Tray.szTip, TITLE_WINDOW);
	Tray.uCallbackMessage = WM_LBUTTONDOWN;
	Tray.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	Tray.uID = 1;*/

	//set the icon in tasbar tray
	//Shell_NotifyIcon(NIM_ADD, &Tray);

	while (window.isOpen())
	{
		// TODO modify the if statement to when user press minimize button
		if (window.hasFocus() == false)
		{
			//hide the window
			//ShowWindow(hWnd, 0);
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