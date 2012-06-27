/*
Phobos 3d
June 2012
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

#include "PH_RigidBody.h"

#include "PH_PhysicsManager.h"
#include "PH_PhysicsUtil.h"

namespace Phobos
{	
	namespace Physics
	{
		RigidBody_c::RigidBody_c(const btRigidBody::btRigidBodyConstructionInfo &info, btDefaultMotionState *motionState, CollisionShapePtr_t shape):
			spRigidBody(new btRigidBody(info)),
			spCollisionShape(shape),
			spMotionState(motionState)
		{
			//empty
		}

		RigidBody_c::~RigidBody_c()
		{
			if(spRigidBody->isInWorld())
				this->Unregister();
		}

		void RigidBody_c::Register()
		{
			PhysicsManager_c::GetInstance()->RegisterRigidBody(*spRigidBody);
		}
		
		void RigidBody_c::Unregister()
		{
			PhysicsManager_c::GetInstance()->UnregisterRigidBody(*spRigidBody);
		}

		Transform_c RigidBody_c::GetTransform() const
		{
			btTransform bodyTransform;
			spMotionState->getWorldTransform(bodyTransform);

			return MakeTransform(bodyTransform);
		}
	}
}