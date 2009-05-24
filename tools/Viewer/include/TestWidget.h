#ifndef TestWidget_H
#define TestWidget_H
//
// --- Includes ---
//
#include "QOgreWidget.h"
//
// --- Class Definition ---
//
class TestWidget : public QOgreWidget {
	Q_OBJECT
public:
	//
	// ########## Public functions ##########
	//
	//
	// --- Constructors ---
	//
	TestWidget(QWidget* parent);
	~TestWidget(void);
protected:
	//
	// ########## Protected functions ##########
	//
	void resizeEvent(QResizeEvent *e);
	void paintEvent(QPaintEvent *e);
	void timerEvent(QTimerEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void createScene(void);
	void setupResources(void);
	void setupScene(void);
	//
	// ########## Private variables ##########
	//
	bool m_mousePressed;
	QPoint m_mousePressPos;
	Ogre::Quaternion m_orientationPressed;
	Ogre::SceneNode *m_mainNode;
	Ogre::SceneManager *m_sceneMgr;
	Ogre::Camera *m_camera;
	Ogre::Viewport *m_vp;
	//
	// ########## Private constants ##########
	//
	static const float m_RADIUS;
};
//
//
//
#endif
