#include "TravelManipulator.h"

TravelManipulator::TravelManipulator(osgViewer::Viewer* viewer)
	: view(viewer)
{
	mPosition = osg::Vec3(0, 0, 50);
	mRotation = osg::Vec3(0, 0, 0);

	m_rButtonDown = false;
	lbuttonDown = false;
	m_leftX = 0;
	m_leftY = 0;
	m_rightX = 0;
	m_rightY = 0;
}

TravelManipulator::~TravelManipulator()
{
}

void TravelManipulator::setByMatrix(const osg::Matrixd& matrix)
{

}

void TravelManipulator::setByInverseMatrix(const osg::Matrixd& matrix)
{

}

osg::Matrixd TravelManipulator::getMatrix() const
{
	osg::Matrixd mat;
	mat.makeTranslate(mPosition);
	return mat * osg::Matrixd::rotate(mRotation[0], osg::X_AXIS, mRotation[1], osg::Y_AXIS, mRotation[2], osg::Z_AXIS);
}

osg::Matrixd TravelManipulator::getInverseMatrix() const
{
	osg::Matrixd mat;
	mat.makeTranslate(mPosition);
	return osg::Matrixd::inverse(mat * osg::Matrixd::rotate(mRotation[0], osg::X_AXIS, mRotation[1], osg::Y_AXIS, mRotation[2], osg::Z_AXIS));
}

bool TravelManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{

	switch (ea.getEventType()) {
	case osgGA::GUIEventAdapter::KEYDOWN:
		if (ea.getKey() == 'w') {
			mPosition[2] += 2;
		}
		else if (ea.getKey() == 's') {
			mPosition[2] -= 2;
		}
		else if (ea.getKey() == 'a') {
			mPosition[0] -= 2;
		}
		else if (ea.getKey() == 'd') {
			mPosition[0] += 2;
		}
		break;

	case osgGA::GUIEventAdapter::PUSH:
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			osg::Vec3 vec1 = screen2World(ea.getX(), ea.getY());
			m_leftX = vec1.x();
			m_leftY = vec1.y();
			m_leftZ = vec1.z();

			lbuttonDown = true;
		}

		if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			m_rightX = ea.getX();
			m_rightY = ea.getY();
			m_rButtonDown = true;
		}
		return false;
	}
	case osgGA::GUIEventAdapter::DRAG:
	{
		if (lbuttonDown)
		{
			osg::Vec3 vec1 = screen2World(ea.getX(), ea.getY());
			float ix = vec1.x() - m_leftX;
			float iy = vec1.y() - m_leftY;
			float iz = vec1.z() - m_leftZ;
			mPosition[2] += 0.1 * iz;
			mPosition[1] -= 0.1 * iy;
			mPosition[0] -= 0.1 * ix;
		}

		if (m_rButtonDown)
		{
			float ix = ea.getX() - m_rightX;
			float iy = ea.getY() - m_rightY;
			mRotation[2] += osg::DegreesToRadians(0.1 * ix);
			mRotation[0] -= osg::DegreesToRadians(0.1 * iy);

		}
		return false;
	}

	case osgGA::GUIEventAdapter::RELEASE:
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			lbuttonDown = false;
		}

		if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			m_rButtonDown = false;
		}
	}
	default:
		break;
	}
	return false;
}


osg::Vec3 TravelManipulator::screen2World(float x, float y)
{
	osg::Vec3 vec3;
	osg::ref_ptr<osg::Camera> camera = view->getCamera();
	osg::Vec3 vScreen(x, y, 0);
	osg::Viewport* vp = camera->getViewport();
	osg::Matrix mVPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
	osg::Matrix invertVPW;
	invertVPW.invert(mVPW);
	vec3 = vScreen * invertVPW;
	return vec3;
}