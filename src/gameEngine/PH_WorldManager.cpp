/*
Phobos 3d
  September 2010

  Copyright (C) 2005-2010 Bruno Crivelari Sanches

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Bruno Crivelari Sanches bcsanches@gmail.com
*/

#include "PH_WorldManager.h"

#include <boost/bind.hpp>

#include <PH_Console.h>
#include <PH_ContextUtils.h>
#include <PH_Dictionary.h>
#include <PH_DictionaryManager.h>
#include <PH_Error.h>
#include <PH_Exception.h>
#include <PH_Kernel.h>

#include "PH_EntityFactory.h"
#include "PH_EntityKeys.h"
#include "PH_WorldEntity.h"

namespace Phobos
{	
	PH_DEFINE_DEFAULT_SINGLETON(WorldManager);	

	WorldManager_c::WorldManager_c():
		CoreModule_c("WorldManager", PRIVATE_CHILDREN),
		cmdLoadMap("loadMap")
	{
		cmdLoadMap.SetProc(PH_CONTEXT_CMD_BIND(&WorldManager_c::CmdLoadMap, this));
	}

	WorldManager_c::~WorldManager_c()
	{

	}

	void WorldManager_c::LoadMap(const String_c &mapName)
	{
		this->RemoveAllChildren();

		std::for_each(lstListeners.begin(), lstListeners.end(), boost::bind(&WorldManagerListener_c::OnMapUnloaded, _1));

		clMapLoader.LoadOgitor(mapName);

		WorldEntityPtr_t world = boost::static_pointer_cast<WorldEntity_c>(WorldEntity_c::Create("WorldSpawn"));
		world->Load(clMapLoader);
		this->AddPrivateChild(world);

		this->LoadEntities();

		std::for_each(lstListeners.begin(), lstListeners.end(), boost::bind(&WorldManagerListener_c::OnMapLoaded, _1));
	}	

	void WorldManager_c::CmdLoadMap(const StringVector_t &args, Context_c &)
	{
		if(args.size() < 2)
		{
			Kernel_c::GetInstance().LogMessage("[CmdLoadMap] Insuficient parameters, usage: loadMap <mapName>");

			return;
		}

		try
		{			
			this->LoadMap(args[1]);			
		}
		catch(Exception_c &ex)
		{
			Kernel_c::GetInstance().LogMessage(ex.what());			
		}
	}

	void WorldManager_c::LoadEntities()
	{
		DictionaryHivePtr_t hive = clMapLoader.GetDynamicEntitiesHive();
		EntityFactory_c &factory = EntityFactory_c::GetInstance();		

		for(Node_c::const_iterator it = hive->begin(), end = hive->end(); it != end; ++it)
		{
			DictionaryPtr_t dict = boost::static_pointer_cast<Dictionary_c>(it->second);

			EntityPtr_t ptr = factory.Create(dict->GetValue(PH_ENTITY_KEY_CLASS_NAME), dict->GetName());
			ptr->Load(*dict);

			this->AddPrivateChild(ptr);
		}
	}

	EntityPtr_t WorldManager_c::TryGetEntityByType(const String_c &className)
	{
		for(Node_c::const_iterator it = this->begin(), end = this->end(); it != end; ++it)
		{
			EntityPtr_t entity = boost::static_pointer_cast<Entity_c>(it->second);
			if(entity->GetClassName().compare(className) == 0)
				return entity;
		}

		return EntityPtr_t();
	}

	void WorldManager_c::OnPrepareToBoot()
	{
		ConsolePtr_t console = Console_c::GetInstance();

		console->AddContextCmd(cmdLoadMap);
	}

	void WorldManager_c::OnBoot()
	{
		clMapLoader.OnBoot();
	}

	void WorldManager_c::OnFinalize()
	{
		this->RemoveAllChildren();
	}

	PH_DEFINE_LISTENER_PROCS(WorldManager_c, WorldManagerListener_c, lstListeners);
}