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

#ifndef PH_LINEAR_MOVER_COMPONENT_H
#define PH_LINEAR_MOVER_COMPONENT_H

#include "PH_MoverComponent.h"

namespace Phobos
{
	class TransformProperty_c;

	class LinearMoverComponent_c: public MoverComponent_c
	{
		public:
			static EntityComponent_c *Create(const String_c &name, Entity_c &owner);	

			~LinearMoverComponent_c();		

			virtual void FixedUpdate();

		protected:
			LinearMoverComponent_c(const String_c &name, Entity_c &owner);					

			virtual void OnLoad(const Register::Table_c &table);

		protected:
			PH_DECLARE_ENTITY_OUTPUT_MANAGER;

		private:			
			PH_DECLARE_ENTITY_OUTPUT(PositionChanged);

			TransformProperty_c *pprpTransform;
	};
}


#endif