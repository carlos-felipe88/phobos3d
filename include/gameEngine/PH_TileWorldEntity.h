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


#ifndef PH_TILE_WORLD_ENTITY_H
#define PH_TILE_WORLD_ENTITY_H

#include "PH_BaseOgreWorldEntity.h"

#include <vector>

namespace Phobos
{
	PH_DECLARE_NODE_PTR(TileWorldEntity);

	class MapLoader_c;

	class PH_GAME_ENGINE_API TileWorldEntity_c: public BaseOgreWorldEntity_c
	{
		public:
			static EntityPtr_t Create(const String_c &name);

			TileWorldEntity_c(const String_c &name);
			~TileWorldEntity_c();

			void LoadMap(const MapLoader_c &loader);

		private:			
			StaticObject_s CreateFloorMesh(int row, int col, const String_c &meshName, Float_t tileScale, Float_t tileSize);

		private:
			std::vector<StaticObject_s> vecObjects;
	};
}

#endif