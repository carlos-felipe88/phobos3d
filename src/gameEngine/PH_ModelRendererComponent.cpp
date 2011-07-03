/*
Phobos 3d
February 2011
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

#include "PH_ModelRendererComponent.h"

#include <OgreEntity.h>

#include <PH_Dictionary.h>
#include <PH_Render.h>
#include <PH_TransformProperty.h>

#include "PH_GameDictionaryUtils.h"
#include "PH_EntityComponentFactory.h"
#include "PH_EntityKeys.h"
#include "PH_ModelRendererManager.h"
#include "PH_WorldEntity.h"

namespace Phobos
{
	PH_FULL_ENTITY_COMPONENT_CREATOR("ModelRenderer", ModelRendererComponent_c);

	EntityInputManager_c ModelRendererComponent_c::clInputManager_gl;
		
	ModelRendererComponent_c::ModelRendererComponent_c(const String_c &name, Entity_c &owner):
		EntityComponent_c(name, owner),
		pclSceneNode(NULL),
		pclMeshEntity(NULL)
	{		
		ModelRendererManager_c::GetInstance()->Register(*this);
	}

	ModelRendererComponent_c::~ModelRendererComponent_c()
	{
		RenderPtr_t render = Render_c::GetInstance();

		render->DestroyEntity(pclMeshEntity);
		render->DestroySceneNode(pclSceneNode);

		ModelRendererManager_c::GetInstance()->Unregister(*this);
	}

	void ModelRendererComponent_c::OnLoad(const Dictionary_c &dictionary)
	{
		const String_c &meshName = dictionary.GetValue(PH_ENTITY_KEY_MESH_FILE);

		RenderPtr_t render = Render_c::GetInstance();

		pclSceneNode = render->CreateSceneNode(this->GetName());
		pclMeshEntity = render->CreateEntity(meshName);

		pclSceneNode->attachObject(pclMeshEntity);

		pclSceneNode->setPosition(DictionaryGetVector3(dictionary, PH_ENTITY_KEY_POSITION));
		pclSceneNode->setScale(DictionaryGetVector3(dictionary, PH_ENTITY_KEY_SCALE));
		pclSceneNode->setOrientation(DictionaryGetQuaternion(dictionary, PH_ENTITY_KEY_ORIENTATION));

		strParentNode = dictionary.GetValue(PH_ENTITY_KEY_PARENT_NODE);
	}

	void ModelRendererComponent_c::OnLoadFinished()
	{
		EntityComponent_c::OnLoadFinished();

		if(strParentNode != PH_WORLD_SCENE_MANAGER_NAME)
		{
			RenderPtr_t render = Render_c::GetInstance();

			pclSceneNode->getParent()->removeChild(pclSceneNode);

			render->GetSceneNode(strParentNode)->addChild(pclSceneNode);
		}
	}

	void ModelRendererComponent_c::Update()
	{
		TransformProperty_c &prop = this->GetCustomEntityProperty<TransformProperty_c>("transform");

		pclSceneNode->setPosition(prop.GetOrigin());
		pclSceneNode->setOrientation(prop.GetRotation());
	}

	PH_BEGIN_ENTITY_INPUT(ModelRendererComponent_c, SetPosition)
	{

	}
}
