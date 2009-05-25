
#include <QMainWindow>
#include <QUiLoader>
#include <QFileInfo>
#include <QFileDialog>
#include <QString>
#include <QFrame>
#include <QMenu>
#include <iostream>

#include "OgreCOLLADAViewer.h"
#include "OgreCOLLADAViewer.ui.h"
#include "TestWidget.h"

/*****************************************************************************/

OgreCOLLADAViewer::OgreCOLLADAViewer()
{
	//Setup the UI from the compiled code.
	setupUi(this);
// 	const QMetaObject* metaobj = metaObject();
// 	metaobj->connectSlotsByName(this);
 
// 	QUiLoader loader(this);
// 	QFile file(":/OgreCOLLADAViewer-ui"); //Load from the embedded QT resource data
// 	file.open(QFile::ReadOnly);
// 	QWidget *myForm = load(&file, this);
// 	file.close();

// 	QMainWindow *window = dynamic_cast<QMainWindow*>(myForm);

	TestWidget *test = new TestWidget(this);

	setCentralWidget(test);

// 	QMenu* menu = window->findChild<QMenu*>("menuFile");
}

/*****************************************************************************/

void OgreCOLLADAViewer::on_actionOpen_activated()
{
	std::cout << "actionOpen - clicked!" << std::endl;
// 	const QString  fileName = QFileDialog::getOpenFileName(this,
//      tr("Open Image"), "~", tr("Ogre Mesh Files (*.mesh);;Collada Files (*.dae);;All files (*.*)"));

	QFileDialog dialog(this);

	std::cout << "Initialize dialog state here." << std::endl;
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter( tr("Ogre Mesh Files (*.mesh);;Collada Files (*.dae);;All files (*.*)") );
	dialog.setViewMode(QFileDialog::Detail);
	dialog.setDirectory("~");

	if (dialog.exec())
	{
		QStringList files = dialog.selectedFiles();
		for (int i=0; i < files.length(); i++)
			std::cout << "fileName " << i << ": " << files[i].toStdString() << std::endl;
		//This is a single-file-select dialog, so only open the first file
	}
}

/*****************************************************************************/

void OgreCOLLADAViewer::on_actionQuit_activated()
{
	std::cout << "[Quit] Gracefully leaving OgreCOLLADAViewer." << std::endl;
	close();
}

/*****************************************************************************/