/*
Phobos 3d
February 2011
Copyright (c) 2005-2013 Bruno Sanches  http://code.google.com/p/phobos3d

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "PH_EntityComponent.h"

namespace Phobos
{
	EntityComponent_c::EntityComponent_c(const String_t &name, Entity_c &owner):
		EntityIO_c(name),
		rclEntity(owner)
	{
		//empty
	}

	void EntityComponent_c::Load(const Register::Table_c &table)
	{
		this->OnLoad(table);
	}		

	void EntityComponent_c::LoadFinished()
	{
		this->OnLoadFinished();
	}
}
