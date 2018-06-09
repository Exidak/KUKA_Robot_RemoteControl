#pragma once

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:

	MainWindow(QObject *parent);
	~MainWindow();

	void setupUi();
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

};