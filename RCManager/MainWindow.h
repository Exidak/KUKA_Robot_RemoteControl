#pragma once

#include "ScriptParser.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:

	MainWindow(QObject *parent);
	~MainWindow();

	void setupUi();
private:
	void activateButtons(bool b);
private slots:
	void slotPressConnect();
	void slotBrowseScript();
	void slotLoadFileScript();
	void slotLoadSavedScript();
	void slotRunScript();
protected:
	QLabel * lblStatus;
	QPushButton * btnConnect;
	QLineEdit *leFileScript;
	QPushButton *btnBrowse;
	QPushButton *btnFileLoad;
	QListWidget *lstScripts;
	QPushButton *btnScrLoad;
	QTextEdit *textScript;
	QPushButton *btnRun;

	ScriptParser *m_scr;
};