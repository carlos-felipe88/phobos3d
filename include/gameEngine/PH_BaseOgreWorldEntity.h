/*
Phobos 3d
May 2012
Copyright (c) 2005-2012 Bruno Sanches  http://code.google.com/p/phobos3d

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef PH_BASE_OGRE_WORLD_ENTITY_H
#define PH_BASE_OGRE_WORLD_ENTITY_H

#include "PH_WorldEntity.h"

#include <OgrePrerequisites.h>

#include "PH_PhysicsManager.h"

namespace Phobos
{
	PH_DECLARE_NODE_PTR(BaseOgreWorldEntity);

	class PH_GAME_ENGINE_API BaseOgreWorldEntity_c: public WorldEntity_c
	{
		protected:
			struct StaticObject_s
			{
				String_c strParent;

				Ogre::SceneNode *pclSceneNode;
				Ogre::Entity *pclEntity;
				Ogre::Light *pclLight;

				Physics::PhysicsManager_c::CollisionShapeSharedPtr_t spCollisionShape;
				btRigidBody *pclRigidBody;

				inline StaticObject_s():
					pclSceneNode(NULL),
					pclEntity(NULL),
					pclLight(NULL),
					pclRigidBody(NULL)
				{
					//empty
				}
			};

			struct TempStaticObject_s
			{
				Ogre::Entity *pclEntity;
				Ogre::SceneNode *pclSceneNode;
				Ogre::Light *pclLight;		

				bool fParent;
				String_c strName;

				TempStaticObject_s():
					pclEntity(NULL),
					pclSceneNode(NULL),
					pclLight(NULL),						
					fParent(false)
				{
				}

				inline void Commit(StaticObject_s &object)
				{
					object.pclEntity = pclEntity;
					object.pclSceneNode = pclSceneNode;
					object.pclLight = pclLight;						

					pclEntity = NULL;
					pclLight = NULL;
					pclSceneNode = NULL;			
				}

				~TempStaticObject_s();
			};

			BaseOgreWorldEntity_c(const String_c &name);
	};
}

#endif