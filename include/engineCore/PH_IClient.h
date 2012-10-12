/*
Phobos 3d
October 2012
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

#ifndef PH_ICLIENT_H
#define PH_ICLIENT_H

#include "PH_EngineCoreAPI.h"

#include "PH_IEscHandler.h"
#include "PH_IPlayerCommandProducer.h"

namespace Phobos
{
	class PH_ENGINE_CORE_API IClient_c: public IEscHandler_c
	{
		public:
			virtual ~IClient_c() {};

			virtual void SetPlayerCmd(IPlayerCmdPtr_t cmd) = 0;
	};
}

#endif