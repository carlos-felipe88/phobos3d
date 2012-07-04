/*
Phobos 3d
July 2012
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

#include "PH_TileGameWorld.h"

#include <PH_Dictionary.h>
#include <PH_Transform.h>

#include "PH_EntityKeys.h"
#include "PH_GameDictionaryUtils.h"
#include "PH_TileGameWorld.h"
#include "PH_WorldManager.h"

namespace Phobos
{
	void EntityLoadTransform(Transform_c &transform, const Dictionary_c &dictionary)
	{
		if(dictionary.TryGetString(PH_ENTITY_KEY_TILE_ROW))
		{						
			const TileGameWorld_c *tileWorld = static_cast<const TileGameWorld_c *>(WorldManager_c::GetInstance()->GetGameWorld());
			tileWorld->LoadTileTransform(transform, dictionary);
		}
		else
		{
			transform.SetOrigin(DictionaryGetVector3(dictionary, PH_ENTITY_KEY_POSITION));
			transform.SetRotation(DictionaryGetQuaternion(dictionary, PH_ENTITY_KEY_ORIENTATION));
		}
	}
}