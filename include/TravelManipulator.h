#pragma once
#include <iostream>
#include <osg/Node>
#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Light>
#include <osg/Group>
#include <osg/LightSource>
#include <osg/BoundingSphere>
#include <osg/BoundingBox>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgUtil/Optimizer>
#include <osg/MatrixTransform>
#include <osg/StateSet>
#include <osgGA/CameraManipulator>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventHandler>
#include <osgViewer/ViewerEventHandlers>

class TravelManipulator :public osgGA::CameraManipulator
{
public:
	TravelManipulator(osgViewer::Viewer* viewer = nullptr);
	~TravelManipulator();

public:
	//���õ�ǰ�ӿ�
	virtual void setByMatrix(const osg::Matrixd& matrix);

	//���õ�ǰ�ӿ�
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);

	//�õ���ǰ����
	virtual osg::Matrixd getMatrix() const;

	//�õ���ǰ����
	virtual osg::Matrixd getInverseMatrix() const;

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

	osg::Vec3 screen2World(float x, float y);


private:
	//�ӵ�
	osg::Vec3 mPosition;
	//����
	osg::Vec3 mRotation;

	osg::ref_ptr<osgViewer::View> view;

	bool lbuttonDown;
	bool m_rButtonDown;

	float m_leftX;
	float m_leftY;
	float m_leftZ;

	float m_rightX;
	float m_rightY;
	float m_rightZ;
};