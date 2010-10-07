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

#include <PH_Node.h>
#include <PH_DynamicLibrary.h>

namespace Phobos
{
	class Plugin_c;

	typedef ::boost::intrusive_ptr<Plugin_c> PluginPtr_t;	

	class IPluginInstance_c
	{
		public:
			virtual void Init() = 0;
			virtual void Finalize() = 0;			
	};

	typedef IPluginInstance_c *(*PluginEntryPointProc_t)();

	class Plugin_c: public Node_c
	{
		public:
			static PluginPtr_t Create(const String_c &name);

			void Init();

		private:
			Plugin_c(const String_c &name);
			~Plugin_c();

		private:
			DynamicLibrary_c	clLibrary;
			IPluginInstance_c	*pclPlugin;
	};
}