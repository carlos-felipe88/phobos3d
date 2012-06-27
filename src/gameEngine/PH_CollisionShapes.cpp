#include "PH_CollisionShapes.h"

#include <OgreMesh.h>
#include <OgreVector3.h>

#include <PH_Error.h>

#include "PH_CollisionMesh.h"

namespace Phobos
{
	namespace Physics
	{
		inline int CompareVectors(const Float_t a[], const Float_t b[])
		{
			for(int i = 0;i < 3; ++i)
			{
				if(a[i] == b[i])
					continue;

				return a[i] < b[i] ? -1 : 1;
			}

			return 0;
		}

		BoxCollisionShape_c::BoxCollisionShape_c(const Ogre::Vector3 &dimensions):
			BaseCollisionShape_c(CST_BOX),
			clBoxShape(btVector3(dimensions.x * 0.5f, dimensions.y * 0.5f, dimensions.z * 0.5f))
		{
			//empty
		}

		int BoxCollisionShape_c::Compare(const BaseCollisionShape_c &other) const
		{
			PH_ASSERT(other.GetType() == this->GetType());

			const BoxCollisionShape_c &bbox = static_cast<const BoxCollisionShape_c&>(other);

			return CompareVectors(clBoxShape.getHalfExtentsWithoutMargin(), bbox.clBoxShape.getHalfExtentsWithoutMargin());
		}				

		int BoxCollisionShape_c::Compare(const Key_s &other) const
		{			
			const btVector3 extents = this->clBoxShape.getHalfExtentsWithoutMargin() * 2;

			return CompareVectors(clBoxShape.getHalfExtentsWithoutMargin(), extents);
		}

		btCollisionShape &BoxCollisionShape_c::GetCollisionShape()
		{
			return clBoxShape;
		}

		//
		//
		//
		//
		//

		
		ScaledMeshCollissionShape_c::ScaledMeshCollissionShape_c(CollisionMeshPtr_t collisionMesh, const Ogre::Vector3 &localScale):
			BaseCollisionShape_c(CST_MESH),
			spOriginalMesh(collisionMesh),
			clScaleTriangleMeshShape(&collisionMesh->GetTriangleMeshShape(), btVector3(localScale.x, localScale.y, localScale.z))
		{
			//empty
		}

		int ScaledMeshCollissionShape_c::Compare(const BaseCollisionShape_c &other) const
		{
			PH_ASSERT(other.GetType() == this->GetType());			

			const ScaledMeshCollissionShape_c &otherMesh = static_cast<const ScaledMeshCollissionShape_c&>(other);

			int cmp = this->spOriginalMesh->GetName().compare(otherMesh.spOriginalMesh->GetName());
			if(cmp == 0)
			{
				return CompareVectors(this->clScaleTriangleMeshShape.getLocalScaling(), otherMesh.clScaleTriangleMeshShape.getLocalScaling());
			}			
			else
				return cmp;
		}				

		int ScaledMeshCollissionShape_c::Compare(const Key_s &other) const
		{			
			PH_ASSERT(other.eType == this->GetType());						

			int cmp = this->spOriginalMesh->GetName().compare(other.pclMesh->getName());
			if(cmp == 0)
			{
				return CompareVectors(this->clScaleTriangleMeshShape.getLocalScaling(), btVector3(other.v3MeshScale.x, other.v3MeshScale.y, other.v3MeshScale.z));
			}			
			else
				return cmp;
		}

		btCollisionShape &ScaledMeshCollissionShape_c::GetCollisionShape()
		{
			return clScaleTriangleMeshShape;
		}
			
	}
}