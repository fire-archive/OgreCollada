#ifndef _TOOLS_OGRECOLLADAVIEWER_H
#define _TOOLS_OGRECOLLADAVIEWER_H

#include <QMainWindow>
#include <QUiLoader>
#include "OgreCOLLADAViewer.ui.h"

class OgreCOLLADAViewer : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

	public:
		/**
		  * Default constructor for Main application window
		  */
		OgreCOLLADAViewer();
	private slots:
		void on_actionOpen_activated();
		void on_actionQuit_activated();

};

#endif