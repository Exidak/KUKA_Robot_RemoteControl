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
	void loadFromFile(QString filepath, bool isSaved = false);
private slots:
	void slotPressConnect();
	void slotBrowseScript();
	void slotLoadFileScript();
	void slotLoadSavedScript();
	void slotRunScript();
	void slotSpeechRec();
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
	QPushButton *btnSpeech;

	ScriptParser *m_scr;
};