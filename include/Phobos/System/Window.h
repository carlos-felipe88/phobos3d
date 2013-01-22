/*
Phobos 3d
February 2010
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


#ifndef PH_SYSTEM_WINDOW_H
#define PH_SYSTEM_WINDOW_H

#include <PH_Node.h>

#include "Phobos/System/SystemAPI.h"

namespace Phobos
{
	namespace System
	{
		PH_DECLARE_NODE_PTR(Window);	

		class EventManager_c;

		class PH_SYSTEM_API Window_c: public Node_c
		{
			public:
				static WindowPtr_t Create(const String_c &name);

				virtual void Open(const String_c &name, const Rect_s<size_t> &rect, void *parentWindow = NULL) = 0;
				virtual void *GetHandler() const = 0;
				virtual bool HasGLContext() = 0;	

				virtual size_t GetWidth(void) const = 0;
				virtual size_t GetHeight(void) const = 0;

			protected:
				Window_c(const String_c &name);		
		};
	}

};

#endif
