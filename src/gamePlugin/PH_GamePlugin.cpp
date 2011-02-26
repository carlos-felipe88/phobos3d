/*
Phobos 3d
  February 2011

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
#include "PH_GamePlugin.h"

#include <boost/foreach.hpp>

#include <PH_Core.h>
#include <PH_CoreModuleManager.h>
#include <PH_ProcVector.h>

namespace Phobos
{	
	GamePlugin_c &GamePlugin_c::GetInstance()
	{
		static GamePlugin_c plugin;

		return plugin;
	}

	void GamePlugin_c::Init()
	{
		ipManager = CoreModuleManager_c::Create("GamePlugin");

		Core_c::GetInstance()->AddModule(ipManager);	

		BOOST_FOREACH(Register_s &info, vecModules)
		{
			ipManager->AddModule(info.pfnCreate());
		}

		ipManager->LaunchBootModule("game.cfg");
	}

	void GamePlugin_c::Finalize()
	{
		Core_c::GetInstance()->RemoveModule(*ipManager);		

		BOOST_FOREACH(Register_s &info, vecModules)
		{
			info.pfnRelease();
		}

		ipManager.reset();
	}

	void GamePlugin_c::AddModule(const Register_s &module)
	{
		vecModules.push_back(module);
	}

	GamePlugin_c::Register_s::Register_s(CreateInstanceProc_t createProc, ReleaseInstanceProc_t releaseProc):
		pfnCreate(createProc),
		pfnRelease(releaseProc)
	{
		GamePlugin_c::GetInstance().AddModule(*this);
	}

	GamePlugin_c::Register_s::Register_s(const Register_s &rhs):
		pfnCreate(rhs.pfnCreate),
		pfnRelease(rhs.pfnRelease)
	{
		//empty
	}
}