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

#ifndef PH_DICTIONARY_HIVE_H
#define PH_DICTIONARY_HIVE_H

#include <PH_Node.h>

#include "PH_DictionaryAPI.h"
#include "PH_DictionaryFwd.h"

namespace Phobos
{
	class Parser_c;

	PH_DECLARE_NODE_PTR(DictionaryHive);

	class PH_DICTIONARY_API DictionaryHive_c: public Node_c
	{
		public:
			static DictionaryHivePtr_t Create(const String_c &name);

			void Load(Parser_c &parser);

			DictionaryPtr_t GetDictionary(const String_c &name);
			DictionaryPtr_t TryGetDictionary(const String_c &name);

			void AddDictionary(DictionaryPtr_t dict);

	
		private:
			DictionaryHive_c(const String_c &name);
			~DictionaryHive_c();
	};
}

#endif