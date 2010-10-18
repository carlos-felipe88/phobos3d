/*
Phobos 3d
  October 2010

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

#ifndef PH_BUTTON_H
#define PH_BUTTON_H

#include <PH_Types.h>
#include <PH_ContextCmd.h>

#include "PH_InputAPI.h"

namespace Phobos
{	
	class IContext_c;

	class PH_INPUT_API Button_c
	{
		public:
			Button_c(const String_c &up, const String_c &down, const String_c &update, IContext_c *context = NULL);		

			inline Float_t GetValue(void) const
			{
				return(fValue);
			}

			void Enable(IContext_c &context);
			void Disable();

		private:
			void CmdProc(const StringVector_t &args, Context_c & );

		private:
			Float_t fValue;

			ContextCmd_c cmdUp;
			ContextCmd_c cmdDown;
			ContextCmd_c cmdUpdate;
	};

	class PH_INPUT_API AxisButton_c
	{
		public:
			AxisButton_c(const String_c &upA, const String_c &downA, const String_c &updateA, const String_c &upB, const String_c &downB, const String_c &updateB, IContext_c *context = NULL);

			void Enable(IContext_c &context);
			void Disable();

			inline Float_t GetValue() const
			{
				return(clButtonB.GetValue() - clButtonA.GetValue());
			}

		private:		
			Button_c	clButtonA;
			Button_c	clButtonB;
	};
}

#endif
