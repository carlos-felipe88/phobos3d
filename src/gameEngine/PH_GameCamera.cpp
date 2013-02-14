/*
Phobos 3d
October 2011
Copyright (c) 2005-2011 Bruno Sanches  http://code.google.com/p/phobos3d

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "PH_GameCamera.h"

#include <PH_Render.h>
#include <PH_Transform.h>

namespace Phobos
{
	GameCamera::GameCamera():
		m_iViewportZOrder(-1),
		m_fpNearPlane(1)
	{
		Render &render = Render::GetInstance();
				
		m_pclRootNode = render.CreateSceneNode();

		this->CreateCamera();
	}

	GameCamera::~GameCamera()
	{
		Render &render = Render::GetInstance();

		if(m_iViewportZOrder >= 0)
			render.RemoveViewport(m_iViewportZOrder);

		if(m_pclCamera)
			render.DestroyCamera(m_pclCamera);

		if(m_pclRootNode)
			render.DestroySceneNode(m_pclRootNode);
	}

	void GameCamera::EnableViewport(int ZOrder)
	{
		Render &render = Render::GetInstance();

		if(m_iViewportZOrder >= 0)
			render.RemoveViewport(m_iViewportZOrder);

		m_iViewportZOrder = ZOrder;

		if(m_iViewportZOrder >= 0)
			render.AddViewport(m_pclCamera, ZOrder);
	}

	void GameCamera::SetTransform(const Transform &t)
	{		
		m_pclRootNode->setPosition(t.GetOrigin());
		m_pclRootNode->setOrientation(t.GetRotation());
	}

	void GameCamera::SetCameraTransform(const Transform &t)
	{
		m_pclCamera->setPosition(t.GetOrigin());
		m_pclCamera->setOrientation(t.GetRotation());
	}

	void GameCamera::EnableFixedYawAxis(const Ogre::Vector3 &axis)
	{
		m_pclCamera->setFixedYawAxis(true, axis);
	}

	void GameCamera::SetNearClipDistance(const Float_t distance)
	{
		m_fpNearPlane = distance;
		m_pclCamera->setNearClipDistance(distance);
	}

	void GameCamera::SetFarClipDistance(const Float_t distance)
	{
		m_fpFarPlane = distance;
		m_pclCamera->setFarClipDistance(distance);
	}

	void GameCamera::SetFov(Ogre::Degree angle)
	{
		m_pclCamera->setFOVy(Ogre::Radian(angle));
	}

	void GameCamera::Enable()
	{
		//PH_ASSERT(pclCamera == NULL);

		//this->CreateCamera();
		this->EnableViewport(m_iViewportZOrder);
	}
	
	void GameCamera::Disable()
	{
		Render &render = Render::GetInstance();
		/*
		pclRootNode->detachObject(pclCamera);
		
		if(iViewportZOrder >= 0)
			render->RemoveViewport(iViewportZOrder);

		if(pclCamera)
			render->DestroyCamera(pclCamera);

		pclCamera = NULL;
		*/
		if(m_iViewportZOrder >= 0)
			render.RemoveViewport(m_iViewportZOrder);
	}

	void GameCamera::AddCameraListener(Ogre::Camera::Listener &listener)
	{
		m_pclCamera->addListener(&listener);
	}

	void GameCamera::CreateCamera()
	{
		Render &render = Render::GetInstance();
		
		m_pclCamera = render.CreateCamera();	

		m_pclRootNode->attachObject(m_pclCamera);

		if(m_iViewportZOrder >= 0)
			render.AddViewport(m_pclCamera, m_iViewportZOrder);

		m_pclCamera->setOrientation(Ogre::Quaternion(Ogre::Angle(180), Ogre::Vector3::UNIT_Y));	
		m_pclCamera->setNearClipDistance(m_fpNearPlane);
		
		this->SetFov(Ogre::Degree(75));
	}
}
