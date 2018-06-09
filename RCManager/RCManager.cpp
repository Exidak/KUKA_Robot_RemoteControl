// RCManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication App(argc, argv);
	QLocale::setDefault(QLocale(QLocale::Language::Russian));
	MainWindow wnd(&App);
	wnd.show();
	return App.exec();
}
