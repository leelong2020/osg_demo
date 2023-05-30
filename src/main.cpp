#include "TravelManipulator.h"

#include<osgGA/GUIEventHandler>
#include <QDebug>

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> root = new osg::Group;

	root->addChild(osgDB::readNodeFile("cow.osg"));
	viewer->setSceneData(root.get());

	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 80;
	traits->y = 80;
	traits->width = 960;
	traits->height = 680;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;


	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc.get());
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);

	viewer->addSlave(camera.get());


	viewer->realize();
	viewer->run();

	return 0;
}
