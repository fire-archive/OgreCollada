#include <QApplication>
#include "OgreCOLLADAViewer.h"

int main(int argc, char **argv) 
{
	QApplication app(argc, argv);
	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

	OgreCOLLADAViewer* viewer = new OgreCOLLADAViewer();
	viewer->show();
	//connect(menu, SIGNAL(actionOpened()),

	return app.exec();
}