/*
Phobos 3d
May 2011
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

#ifndef PH_SYSTEM_MOUSE_INPUT_DEVICE_SDL_H
#define PH_SYSTEM_MOUSE_INPUT_DEVICE_SDL_H

#include "Phobos/System/MouseInputDevice.h"

#include "Phobos/System/EventListener.h"

#include <SDL.h>

namespace Phobos
{
	namespace System
	{
		class MouseInputDeviceSDL: public MouseInputDevice, private EventListener
		{
			public:
				static InputDevicePtr_t Create(const String_t &name);

				MouseInputDeviceSDL(const String_t &name);
				~MouseInputDeviceSDL(void);

				virtual void Update(void) override;

				virtual void ClipToWindow() override;
				virtual void Unclip(void) override;

				virtual void ShowCursor() override;
				virtual void HideCursor() override;

				virtual short GetX() override;
				virtual short GetY() override;

			private:
				virtual void OnEvent(struct Event_s &event) override;

				void Enable();
				void Disable();

			private:
				class SytemEventListner: EventListener
				{
					public:
						SytemEventListner();

						inline void SetOwner(MouseInputDeviceSDL *owner);

					private:
						virtual void OnEvent(struct Event_s &event) override;

					private:
						MouseInputDeviceSDL *m_pclOwner;
				};

				friend class SytemEventListner;

				SytemEventListner m_clSystemListener;

				//RECT		stOldClipRect;
				//bool		fHasClipRect;

				int			iWindowCenter[2];
				int			iPreviousMousePosition[2];
				bool		fClipToWindow;
				bool		fAppActive;
				SDL_Event event;
		};
	}
}

#endif
