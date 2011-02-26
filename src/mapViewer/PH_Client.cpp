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

#include "PH_Client.h"

#include <PH_Console.h>
#include <PH_ContextUtils.h>
#include <PH_Error.h>
#include <PH_Exception.h>
#include <PH_Kernel.h>
#include <PH_MouseInputDevice.h>
#include <PH_PointEntity.h>
#include <PH_Render.h>
#include <PH_Window.h>
#include <PH_WorldManager.h>

PH_GAME_PLUGIN_ENTRY_POINT;

namespace Phobos
{
	PH_DEFINE_DEFAULT_SINGLETON(Client);	

	PH_GAME_PLUGIN_REGISTER_MODULE(Client);

	PH_GAME_PLUGIN_CREATE_MODULE_PROC_IMPL(Client);

	Client_c::Client_c():
		CoreModule_c("Client"),		
		cmdNullMouseThumb(PH_MOUSE_THUMB_CMD_NAME),
		cmdToggleMouseCursorClip("toggleMouseCursorClip"),
		varMouseSensitivity("dvMouseSensitivity", "0.1"),
		varSpectatorMoveSpeed("dvSpectatorMoveSpeed", "2.0"),
		varSpectatorTurnSpeed("dvSpectatorTurnSpeed", "45.0"),
		fMapLoaded(false),
		fMouseClipped(false)
	{				
		cmdToggleMouseCursorClip.SetProc(PH_CONTEXT_CMD_BIND(&Client_c::CmdToggleMouseCursorClip, this));
		cmdNullMouseThumb.SetProc(PH_CONTEXT_CMD_BIND(&Client_c::CmdNullMouseThumb, this));

		varSpectatorMoveSpeed.SetCallback(PH_CONTEXT_VAR_BIND(&Client_c::VarSpectatorMoveSpeedChanged, this));
		varSpectatorTurnSpeed.SetCallback(PH_CONTEXT_VAR_BIND(&Client_c::VarSpectatorTurnSpeedChanged, this));
		varMouseSensitivity.SetCallback(PH_CONTEXT_VAR_BIND(&Client_c::VarMouseSensitivityChanged, this));
	}

	void Client_c::OnRenderReady()
	{		
	}

	void Client_c::OnFixedUpdate()
	{
		if(!fMapLoaded)
			return;

		clSpectatorCamera.FixedUpdate();
	}

	void Client_c::OnUpdate()
	{
		if(!fMapLoaded)
			return;

		clSpectatorCamera.Update();
	}

	void Client_c::OnPrepareToBoot()
	{
		ConsolePtr_t console = Console_c::GetInstance();
		
		console->AddContextCmd(cmdToggleMouseCursorClip);
		console->AddContextCmd(cmdNullMouseThumb);

		console->AddContextVar(varMouseSensitivity);
		console->AddContextVar(varSpectatorMoveSpeed);
		console->AddContextVar(varSpectatorTurnSpeed);

		WorldManager_c::GetInstance()->AddListener(*this);
	}

	struct ConfigInfo_s
	{
		MouseInputDevicePtr_t ipMouse;
		void *pWindowHandler;
	};

	ConfigInfo_s Client_c::GetConfig()
	{
		ConfigInfo_s info;

		info.pWindowHandler = Render_c::GetInstance()->GetWindowHandler();
		info.ipMouse = boost::static_pointer_cast<MouseInputDevice_c>(InputManager_c::GetInstance()->GetDevice(INPUT_DEVICE_MOUSE));

		return info;
	}
	
	void Client_c::ClipMouseCursor()
	{		
		ConfigInfo_s info = this->GetConfig();

		info.ipMouse->ClipToWindow(info.pWindowHandler);

		cmdNullMouseThumb.Unlink();
		clSpectatorCamera.EnableMouse();
		fMouseClipped = true;
	}

	void Client_c::UnclipMouseCursor()
	{
		ConfigInfo_s info = this->GetConfig();

		info.ipMouse->Unclip();

		clSpectatorCamera.DisableMouse();
		Console_c::GetInstance()->AddContextCmd(cmdNullMouseThumb);
		fMouseClipped = false;
	}

	void Client_c::OnMapUnloaded()
	{		
		if(fMapLoaded)
		{
			fMapLoaded = false;
			clSpectatorCamera.DisableController();
		}
	}

	void Client_c::OnMapLoaded()
	{			
		WorldManagerPtr_t worldManager = WorldManager_c::GetInstance();
		PointEntityPtr_t player = boost::static_pointer_cast<PointEntity_c>(worldManager->TryGetEntityByType("InfoPlayerStart"));
		if(!player)
		{
			Kernel_c::GetInstance().LogMessage("[CmdLoadMap] World does not contais InfoPlayerStart entity");
		}
		else
		{
			clSpectatorCamera.SetTransform(player->GetTransform());
		}

		fMapLoaded = true;
		clSpectatorCamera.EnableController();

		if(!fMouseClipped)
			this->ClipMouseCursor();		
	}

	void Client_c::CmdNullMouseThumb(const StringVector_t &, Context_c &  )
	{
		//empty
	}

	void Client_c::CmdToggleMouseCursorClip(const StringVector_t &, Context_c &  )
	{
		if(fMouseClipped)
			this->UnclipMouseCursor();
		else
			this->ClipMouseCursor();		
	}	

	void Client_c::VarSpectatorMoveSpeedChanged(const class ContextVar_c &var, const String_c &oldValue, const String_c &newValue)
	{		
		clSpectatorCamera.SetMoveSpeed(StringToFloat(newValue));
	}
	
	void Client_c::VarSpectatorTurnSpeedChanged(const class ContextVar_c &var, const String_c &oldValue, const String_c &newValue)
	{
		clSpectatorCamera.SetTurnSpeed(StringToFloat(newValue));
	}
	
	void Client_c::VarMouseSensitivityChanged(const class ContextVar_c &var, const String_c &oldValue, const String_c &newValue)
	{
		clSpectatorCamera.SetMouseSensitivity(StringToFloat(newValue));
	}
}
