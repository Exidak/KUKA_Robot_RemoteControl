// SpeechRecognizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VoiceRecordDlg.h"

int main(int argc, char *argv[])
{
	QApplication App(argc, argv);
	QLocale::setDefault(QLocale(QLocale::Language::Russian));
	VoiceRecordDlg wnd(&App);
	wnd.show();
	return App.exec();
}
