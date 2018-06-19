#include "stdafx.h"
#include "tmp\moc_MainWindow.cpp"
#include "ScriptParser.h"
#include "SpeechDlg.h"

MainWindow::MainWindow(QObject *parent)
{
	m_scr = new ScriptParser();
	setupUi();
}


MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
	resize(800, 600);
	QWidget *centralwidget = new QWidget(this);
	QGridLayout *gridLayout = new QGridLayout(centralwidget);

	// connect 
	QGroupBox *gbConnect = new QGroupBox(centralwidget);
	QVBoxLayout *vlCon = new QVBoxLayout(gbConnect);
	QHBoxLayout *hlStatus = new QHBoxLayout(gbConnect);
	QLabel *lblStatusHed = new QLabel(gbConnect);
	lblStatus = new QLabel(gbConnect);
	QHBoxLayout *hlCon = new QHBoxLayout(gbConnect);
	btnConnect = new QPushButton(gbConnect);

	// load file
	QGroupBox *gbLoad = new QGroupBox(centralwidget);
	QHBoxLayout *hbLoad = new QHBoxLayout(gbLoad);
	leFileScript = new QLineEdit(gbLoad);
	btnBrowse = new QPushButton(gbLoad);
	btnFileLoad = new QPushButton(gbLoad);

	// scripts
	QGroupBox *gbScripts = new QGroupBox(centralwidget);
	QVBoxLayout *vlScr = new QVBoxLayout(gbScripts);
	lstScripts = new QListWidget(gbScripts);
	QHBoxLayout *hbScr = new QHBoxLayout(gbScripts);
	btnScrLoad = new QPushButton(gbScripts);

	// script view
	QGroupBox *gbView = new QGroupBox(centralwidget);
	QVBoxLayout *vlView = new QVBoxLayout(gbView);
	textScript = new QTextEdit(gbView);
	QHBoxLayout *hbView = new QHBoxLayout(gbView);
	btnRun = new QPushButton(gbView);
	btnSpeech = new QPushButton(gbView);

	gbConnect->setTitle(QString::fromLocal8Bit("Соединение"));
	lblStatusHed->setText(QString::fromLocal8Bit("Статус"));
	lblStatus->setText("X");
	btnConnect->setText(QString::fromLocal8Bit("Соединиться"));

	gbLoad->setTitle(QString::fromLocal8Bit("Скрипт из файла"));
	btnBrowse->setText(QString::fromLocal8Bit("Обзор..."));
	btnFileLoad->setText(QString::fromLocal8Bit("Загрузить"));

	gbScripts->setTitle(QString::fromLocal8Bit("Скрипты"));
	btnScrLoad->setText(QString::fromLocal8Bit("Загрузить"));

	gbView->setTitle(QString::fromLocal8Bit("Скрипт"));
	btnRun->setText(QString::fromLocal8Bit("Пуск"));
	btnSpeech->setText(QString::fromLocal8Bit("Голосовой ввод"));

	connect(btnConnect, &QPushButton::clicked, this, &MainWindow::slotPressConnect);
	connect(btnBrowse, &QPushButton::clicked, this, &MainWindow::slotBrowseScript);
	connect(btnFileLoad, &QPushButton::clicked, this, &MainWindow::slotLoadFileScript);
	connect(btnScrLoad, &QPushButton::clicked, this, &MainWindow::slotLoadSavedScript);
	connect(btnRun, &QPushButton::clicked, this, &MainWindow::slotRunScript);
	connect(btnSpeech, &QPushButton::clicked, this, &MainWindow::slotSpeechRec);

	hlCon->addStretch(1);
	hlCon->addWidget(btnConnect);
	hlStatus->addWidget(lblStatusHed);
	hlStatus->addStretch(1);
	hlStatus->addWidget(lblStatus);
	vlCon->addLayout(hlStatus);
	vlCon->addLayout(hlCon);
	gridLayout->addWidget(gbConnect, 0, 0);

	hbLoad->addWidget(leFileScript);
	hbLoad->addWidget(btnBrowse);
	hbLoad->addWidget(btnFileLoad);
	gridLayout->addWidget(gbLoad, 0, 1);

	hbScr->addStretch(1);
	hbScr->addWidget(btnScrLoad);
	vlScr->addWidget(lstScripts);
	vlScr->addLayout(hbScr);
	gridLayout->addWidget(gbScripts, 1, 0);

	hbView->addWidget(btnSpeech);
	hbView->addStretch(1);
	hbView->addWidget(btnRun);
	vlView->addWidget(textScript);
	vlView->addLayout(hbView);
	gridLayout->addWidget(gbView, 1, 1);

	gridLayout->setColumnStretch(0, 1);
	gridLayout->setColumnStretch(1, 3);

	setCentralWidget(centralwidget);

	activateButtons(false);
} // setupUi

void MainWindow::activateButtons(bool b)
{
	leFileScript->setEnabled(b);
	btnBrowse->setEnabled(b);
	btnFileLoad->setEnabled(b);
	lstScripts->setEnabled(b);
	btnScrLoad->setEnabled(b);
	textScript->setEnabled(b);
	btnRun->setEnabled(b);
}

void MainWindow::loadFromFile(QString filepath, bool isSaved)
{
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"), 
			QString::fromLocal8Bit("Не удается открыть файл\n") + filepath +"\n"+ file.errorString(), QMessageBox::Ok, QMessageBox::Ok);
	}
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		if (isSaved)
			textScript->append(QString::fromLocal8Bit(line));
		else
			textScript->append(line);
	}
}

void MainWindow::slotBrowseScript()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Открыть скрипт"), "", QString::fromLocal8Bit("Скрипт (*.txt)"));
	leFileScript->setText(fileName);
}

void MainWindow::slotLoadFileScript()
{
	loadFromFile(leFileScript->text());
}

void MainWindow::slotLoadSavedScript()
{
	QListWidgetItem *cur = lstScripts->currentItem();
	if (cur)
	{
		QString scr_path = "scripts\\";
		scr_path += cur->text();
		loadFromFile(scr_path, true);
	}
	else
		QMessageBox::warning(this, QString::fromLocal8Bit("Ошибка"), QString::fromLocal8Bit("Выберите снчала скрипт"), QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::slotRunScript()
{
	btnRun->setEnabled(false);
	try
	{
		std::string script_text = textScript->toPlainText().toStdString();
		m_scr->runScript(script_text);
		ECommand curLextype;
		int position;
		while (m_scr->execNextCommand(curLextype, position))
		{
			int count2Highlight = 0;
			switch (curLextype)
			{
			case RC_CMD_FUNCTION:
			case RC_CMD_WAIT:
				count2Highlight = 2;
				break;
			case RC_CMD_MOVE:
			case RC_CMD_ROTATE:
				count2Highlight = 3;
				break;
			case RC_CMD_STOP:
				count2Highlight = 1;
				break;
			}

			QString scrtext = textScript->toPlainText();
			textScript->clear();
			
			QRegExp separator("( |\n|=r)");
			QStringList list = scrtext.split(separator, QString::SkipEmptyParts);

			// find position 
			int pos_hl1 = 0;
			int pos_hl2;
			QStringList::iterator sIt = list.begin();
			while (position)
			{
				if (sIt != list.end())
				{
					pos_hl1 += sIt->size() + 1;//scrtext.indexOf(' ', pos_hl1 + 1);
					sIt++;
				}
				position--;
			}
			pos_hl2 = pos_hl1;
			while (count2Highlight)
			{
				if (sIt != list.end())
				{
					pos_hl2 += sIt->size() + 1;//scrtext.indexOf(' ', pos_hl2 + 1);
					sIt++;
				}
				count2Highlight--;
			}
			QTextCharFormat fmt;
			fmt.setBackground(Qt::yellow);

			textScript->setText(scrtext);
			QTextCursor cursor(textScript->document());
			cursor.setPosition(pos_hl1, QTextCursor::MoveAnchor);
			cursor.setPosition(pos_hl2, QTextCursor::KeepAnchor);
			cursor.setCharFormat(fmt);
			qApp->processEvents();
		}
		QString scrtext = textScript->toPlainText();
		textScript->clear();
		textScript->setText(scrtext);
	}
	catch (ScriptParser::ScriptError err)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("Синтаксическая ошибка"), QString::fromLocal8Bit("Ошибка синтаксиса в скрипте.\nПозиция: ") + QString::number(err.pos), QMessageBox::Ok, QMessageBox::Ok);

		QString scrtext = textScript->toPlainText();
		textScript->clear();
		textScript->setText(scrtext);

		int position = err.pos;
		int pos_hl1 = 0;
		int pos_hl2;
		while (position)
		{
			pos_hl1 = scrtext.indexOf(' ', pos_hl1 + 1);
			position--;
		}
		pos_hl2 = pos_hl1;
		pos_hl2 = scrtext.indexOf(' ', pos_hl2 + 1);
		if (pos_hl2 == -1)
			pos_hl2 = scrtext.size();

		QTextCharFormat fmt;
		fmt.setBackground(Qt::red);

		QTextCursor cursor(textScript->document());
		cursor.setPosition(pos_hl1, QTextCursor::MoveAnchor);
		cursor.setPosition(pos_hl2, QTextCursor::KeepAnchor);
		cursor.setCharFormat(fmt);
		qApp->processEvents();
	}
	btnRun->setEnabled(true);
}

void MainWindow::slotSpeechRec()
{
	SpeechDlg *dlg = new SpeechDlg(this);
	if (dlg->exec() == QDialog::Accepted)
	{
		textScript->setText(dlg->getResult());
		slotRunScript();
	}
	delete dlg;
}

void MainWindow::slotPressConnect()
{
	if (m_scr->connect())
	{
		lblStatus->setText("V");
		activateButtons(true);
		for (auto it : m_scr->getSavedScripts())
			lstScripts->addItem(QString::fromLocal8Bit(it.c_str()));
	}
	else
		QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка соединения"), QString::fromLocal8Bit("Не удается соединиться с моделью или зарегистрировать все двигатели"), QMessageBox::Ok, QMessageBox::Ok);
}