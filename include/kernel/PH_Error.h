/*
Phobos 3d
  version 0.0.1, January 2010

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

#ifndef PH_ERROR_H
#define PH_ERROR_H

#ifdef PH_CHECK_ASSERT
#	if (defined PH_MSVC)
#		include <crtdbg.h>
#		define PH_ASSERT(EXP) _ASSERTE(EXP)
#		define PH_ASSERT_MSG(EXP, MSG) _ASSERT_EXPR(EXP, _CRT_WIDE(MSG))
#		define PH_ASSERT_VALID(VALUE) _ASSERTE(VALUE != NULL)
#		define PH_ASSERT_VALID_MSG(VALUE, MSG) _ASSERT_EXPR(VALUE != NULL, _CRT_WIDE(MSG))

#		define PH_VERIFY(EXP) PH_ASSERT(EXP)

#		define PH_ASSERT_ADDRESS_ALIGN_SIZE(VAR, SIZE) PH_ASSERT((SIZE != 0) && (((PH_Size_t) VAR) % SIZE) == 0)
#		define PH_ASSERT_ADDRESS_ALIGN(VAR) PH_ASSERT_ADDRESS_ALIGN_SIZE(VAR, sizeof(*VAR))
#		define PH_ASSERT_ALIGN(VAR) PH_ASSERT_ADDRESS_ALIGN_SIZE(&VAR, sizeof(VAR))
#   elif(defined PH_GCC)
#		define PH_ASSERT(EXP)
#		define PH_ASSERT_MSG(EXP, MSG)
#		define PH_ASSERT_VALID(VALUE)
#		define PH_ASSERT_VALID_MSG(VALUE, MSG)
#		define PH_ASSERT_ADDRESS_ALIGN(VALUE)
#		define PH_VERIFY(EXP) if(EXP){};
#	endif
#else
#		define PH_ASSERT(EXP)
#		define PH_ASSERT_MSG(EXP, MSG)
#		define PH_ASSERT_VALID(VALUE)
#		define PH_ASSERT_VALID_MSG(VALUE, MSG)
#		define PH_ASSERT_ADDRESS_ALIGN(VALUE)
#		define PH_VERIFY(EXP) if(EXP){};
#endif

#endif
