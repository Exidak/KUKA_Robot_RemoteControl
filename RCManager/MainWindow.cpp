#include "stdafx.h"
#include "tmp\moc_MainWindow.cpp"
#include "ScriptParser.h"

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

	connect(btnConnect, &QPushButton::clicked, this, &MainWindow::slotPressConnect);
	connect(btnBrowse, &QPushButton::clicked, this, &MainWindow::slotBrowseScript);
	connect(btnFileLoad, &QPushButton::clicked, this, &MainWindow::slotLoadFileScript);
	connect(btnScrLoad, &QPushButton::clicked, this, &MainWindow::slotLoadSavedScript);
	connect(btnRun, &QPushButton::clicked, this, &MainWindow::slotRunScript);

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

void MainWindow::slotBrowseScript()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Открыть скрипт"), "", QString::fromLocal8Bit("Скрипт (*.txt)"));
	leFileScript->setText(fileName);
}

void MainWindow::slotLoadFileScript()
{
	QFile file(leFileScript->text());
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"), QString::fromLocal8Bit("Не удается открыть файл"), QMessageBox::Ok, QMessageBox::Ok);

	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		textScript->append(line);
	}
}

void MainWindow::slotLoadSavedScript()
{
	QListWidgetItem *cur = lstScripts->currentItem();
	if (cur)
	{
		std::string scr_path = "script\\" + cur->text().toStdString();
		m_scr->runScript(scr_path, true);
	}
	else
		QMessageBox::warning(this, QString::fromLocal8Bit("Ошибка"), QString::fromLocal8Bit("Выберите снчала скрипт"), QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::slotRunScript()
{
	// TODO
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