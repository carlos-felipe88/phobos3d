/*
Phobos 3d
May 2010
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

#ifndef PH_CONSOLE_H
#define PH_CONSOLE_H

#include <Overlay/OgreOverlayContainer.h>

#include <OgrePrerequisites.h>
#include <OgreRectangle2D.h>

#include <Phobos/Engine/Console.h>

#include "Phobos/OgreEngine/OgreEngineAPI.h"

namespace Phobos
{	
	namespace OgreEngine
	{
		class Console;

		PH_DECLARE_NODE_PTR(Console);	

		class PH_OGRE_ENGINE_API Console: 
			public Engine::Console		
		{
			public:
				// =====================================================
				// PUBLIC METHODS
				// =====================================================		
				static Console &CreateInstance(void);

				~Console(void);
			protected:
				// =====================================================
				// PROTECTED METHODS
				// =====================================================
				Console(void);			
			
				virtual void OnUpdate() override;
				virtual void OnRenderReady() override;
				virtual void OnFinalize() override;

				virtual void OnToggleConsole() override;
				virtual void OnEditBoxChanged() override;
				virtual void OnTextListChanged() override;

			private:
				// =====================================================
				// PRIVATE METHODS
				// =====================================================
				void UpdateRenderInfo();
			
			private:
				// =====================================================
				// PRIVATE ATTRIBUTES
				// =====================================================			
				Ogre::OverlayContainer		*m_pclRect;		
				Ogre::OverlayElement		*m_pclTextBox;
				Ogre::Overlay				*m_pclOverlay;				
				Ogre::Overlay				*m_pclRenderInfoOverlay;

				Float_t						m_fpHeight;			

				Shell::Variable				m_varMaterialName;
				Shell::Variable				m_varShowRenderInfo;			
												
				bool m_fUIMoved;
				bool m_fEditBoxChanged;
				bool m_fTextBufferChanged;
		};	
	}
}

#endif
