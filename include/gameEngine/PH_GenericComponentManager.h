/*
Phobos 3d
July 2011
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

#ifndef PH_GENERIC_COMPONENT_MANAGER_H
#define PH_GENERIC_COMPONENT_MANAGER_H

#include <PH_CoreModule.h>
#include <PH_Exception.h>

#include "PH_GameEngineAPI.h"
#include "PH_WorldManager.h"

namespace Phobos
{			
	template <typename T>
	class PH_GAME_ENGINE_API GenericComponentManager_c: public CoreModule_c
	{
		//PH_DECLARE_SINGLETON_METHODS(GenericComponentManager_c);

		public:
			void Register(T &comp)
			{
				UInt_t index = comp.GetEntityHandle().u12Index;
				if(arpclComponents[index] != NULL)
					PH_RAISE(INVALID_OPERATION_EXCEPTION, "[ModelRendererManager_c::Register]", "Slot already in use");

				arpclComponents[index] = &comp;
			}

			void Unregister(T &comp)
			{
				UInt_t index = comp.GetEntityHandle().u12Index;

				if(arpclComponents[index] != &comp)
					PH_RAISE(INVALID_PARAMETER_EXCEPTION, "[ModelRendererManager_c::Unregister]", "Slot contains another component");

				arpclComponents[index] = NULL;
			}

		protected:
			GenericComponentManager_c(const String_c &name):
				CoreModule_c(name)
			{
				memset(arpclComponents, 0, sizeof(arpclComponents));
			}

			void CallForAll(void (T::*proc)())
			{
				UInt_t count = 0;
				UInt_t total = WorldManager_c::GetInstance()->GetNumActiveEntities();

				for(int i = 0;i < EntityManager_c::MAX_ENTRIES && count < total; ++i)
				{
					if(arpclComponents[i] == NULL)
						continue;

					(arpclComponents[i]->*proc)();
					++count;
				}
			}

			~GenericComponentManager_c()
			{
				//empty
			}

		protected:
			T *arpclComponents[EntityManager_c::MAX_ENTRIES];
	};
}

#endif
