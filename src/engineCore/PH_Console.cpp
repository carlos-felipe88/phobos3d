/*
Phobos 3d
May 2012
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

#include "PH_Console.h"

#include <boost/foreach.hpp>

#include <PH_ContextUtils.h>
#include <PH_Exception.h>
#include <PH_Kernel.h>
#include <PH_Path.h>

#include <Phobos/Register/Table.h>
#include <Phobos/Register/Manager.h>

#include <Phobos/System/InputActions.h>
#include <Phobos/System/InputEvent.h>

#define CONSOLE_HISTORY_COUNT 32

#define CONSOLE_LINE_COUNT 15

namespace Phobos
{
	ConsolePtr_t Console_c::ipInstance_gl;
	
	Console_c &Console_c::GetInstance(void)
	{
		return *ipInstance_gl;
	}

	void Console_c::ReleaseInstance(void)
	{
		ipInstance_gl.reset();
	}
			
	Console_c::Console_c(const String_t &name, UInt32_t flags):
		CoreModule_c(name, flags),
		cmdLs("ls"),
		cmdCd("cd"),
		cmdDumpTable("dumpTable"),		
		lstText(CONSOLE_LINE_COUNT),
		lstHistory(CONSOLE_HISTORY_COUNT),
		strCurrentNodePathName("/"),
		fActive(true)
	{
		Kernel_c::GetInstance().AddLogListener(*this);				

		cmdLs.SetProc(PH_CONTEXT_CMD_BIND(&Console_c::CmdLs, this));
		cmdCd.SetProc(PH_CONTEXT_CMD_BIND(&Console_c::CmdCd, this));
		cmdDumpTable.SetProc(PH_CONTEXT_CMD_BIND(&Console_c::CmdDumpTable, this));		

		clContext.AddContextCmd(cmdLs);
		clContext.AddContextCmd(cmdCd);
		clContext.AddContextCmd(cmdDumpTable);
	}

	Console_c::~Console_c()
	{
		//empty
	}

	void Console_c::UpdateInstance(ConsolePtr_t console)
	{
		ipInstance_gl = console;
	}

	const String_t &Console_c::EditBoxStr() const
	{
		return clEditBox.GetStr();
	}

	void Console_c::Execute(const String_t &cmdLine)
	{
		this->QueueCommand(cmdLine);
	}

	void Console_c::ExecuteFromFile(const String_t &fileName)
	{
		clContext.ExecuteFromFile(fileName);
	}

	void Console_c::OnChar(Char_t ch)
	{		
		switch(ch)
		{
			case System::KB_BACKSPACE:
				clEditBox.Backspace();
				break;

			case System::KB_ENTER:
				this->OnEnter();
				break;

			case System::KB_ESCAPE:
				//ignore
				break;

			default:
				clEditBox.AddChar(ch);
				break;
		}

		this->OnEditBoxChanged();
	}

	void Console_c::OnEnter(void)
	{
		const String_t &cmdLine = clEditBox.GetStr();

		Kernel_c::GetInstance().LogStream() << "> " << cmdLine;
		
		this->QueueCommand(cmdLine);		

		this->AddToHistory(cmdLine);

		clEditBox.Clear();
	}

	void Console_c::QueueCommand(const String_t &cmd)
	{
		clCommandBuffer << cmd << std::endl;
	}

	void Console_c::FlushCommandBuffer()
	{
		String_t buffer = clCommandBuffer.str();
		clCommandBuffer.str(String_t());
		clCommandBuffer.clear();

		clContext.Execute(buffer);				
	}

	void Console_c::AddToHistory(const String_t &str)
	{
		if(!lstHistory.empty() && lstHistory.front().compare(str) == 0)
			return;

		lstHistory.push_front(str);
		itPrevCmd = lstHistory.begin();
	}

	bool Console_c::GetPreviousCommand(String_t &str)
	{
		if(!lstHistory.empty() && (itPrevCmd != lstHistory.end()))
		{
			str = *itPrevCmd;
			++itPrevCmd;

			return(true);
		}

		return(false);
	}

	bool Console_c::GetNextCommand(String_t &str)
	{
		if(!lstHistory.empty() && (itPrevCmd != lstHistory.begin()))
		{
			--itPrevCmd;
			str = *itPrevCmd;

			return(true);
		}

		return(false);
	}

	void Console_c::OnPreviousCommand(void)
	{
		String_t tmp;

		if(this->GetPreviousCommand(tmp))
		{			
			clEditBox.SetStr(tmp);

			this->OnEditBoxChanged();
		}
	}

	void Console_c::OnNextCommand(void)
	{
		String_t tmp;

		if(this->GetNextCommand(tmp))
		{			
			clEditBox.SetStr(tmp);

			this->OnEditBoxChanged();
		}
	}	

	void Console_c::Print(const String_t &str)
	{
		String_t line;
		size_t splitPos = 0;

		while(StringSplitBy(line, str, '\n', splitPos, &splitPos))
		{
			lstText.push_back(line);
		}

		this->OnTextListChanged();		
	}

	bool Console_c::HandleInputEvent(const System::InputEvent_s &event)
	{
		switch(event.eType)
		{
			case System::INPUT_EVENT_CHAR:
				if(this->IsActive())
				{
					this->OnChar(static_cast<Char_t>(event.stChar.u16Char));
					return true;
				}
				break;

			case System::INPUT_EVENT_BUTTON:
				if(event.stButton.eState == System::BUTTON_STATE_DOWN)
				{
					if(this->IsActive())
					{
						if(event.stButton.uId == System::KB_UP_ARROW)
						{
							this->OnPreviousCommand();
							return true;
						}
						else if(event.stButton.uId == System::KB_DOWN_ARROW)
						{
							this->OnNextCommand();
							return true;
						}
					}
				}
				break;

            default:
                break;
		}

		return false;
	}

	void Console_c::Message(const String_t &msg)
	{
		this->Print(msg);
	}

	void Console_c::ToggleConsole(void)
	{
		const Char_t *msg;

		//if just turning on
		fActive = !fActive;
		if(fActive)
		{			
			msg = "enabled";					
		}
		else
		{
			msg = "disabled";
		}

		std::string tmp("Console ");
		tmp.append(msg);
		Kernel_c::GetInstance().LogMessage(tmp);

		this->OnToggleConsole();
	}	

	void Console_c::CmdLs(const StringVector_t &args, Context_c &)
	{
		Kernel_c	&kernel = Kernel_c::GetInstance();
		Node_c		*currentNode;

		if(args.size() > 1)
		{
			Path_c path(args[1]);

			if(path.IsRelative())
			{
				path = strCurrentNodePathName;
				path.AddName(args[1]);
			}

			try
			{
				currentNode = &kernel.LookupObject(path);
			}
			catch(ObjectNotFoundException_c &)
			{
				kernel.LogStream() << "[OgreConsole_c::CmdLs] Invalid path: " << path.GetStr();

				return;
			}
		}
		else
		{
			try
			{
				currentNode = &kernel.LookupObject(Path_c(strCurrentNodePathName));
			}
			catch(ObjectNotFoundException_c &)
			{
				kernel.LogStream() << "[OgreConsole_c::CmdLs] Invalid node (" << strCurrentNodePathName << "), going to root";

				strCurrentNodePathName = "/";
				return;
			}
		}

		std::stringstream stream;

		stream << "\t.\n\t..\n";
		BOOST_FOREACH(const Node_c::NodeMapPair_t &pair, currentNode->GetNodes())
		{
			stream << "\t" << pair.second->GetName() << "\n";
		}

		kernel.LogMessage(stream.str());
	}

	void Console_c::CmdCd(const StringVector_t &args, Context_c &)
	{
		if(args.size() == 2)
		{
			Kernel_c	&kernel = Kernel_c::GetInstance();
			Node_c		*currentNode;
			Path_c		path(args[1]);

			if(path.IsRelative())
			{
				path = strCurrentNodePathName;
				path.AddName(args[1]);
			}

			try
			{
				currentNode = &kernel.LookupObject(path);
				currentNode->GetThisPath(path);

				//if we are at root, we set the path manually, otherwise the path will be empty
				if(currentNode->GetParent() == NULL)
					strCurrentNodePathName = '/';
				else
					strCurrentNodePathName = path.GetStr();
			}
			catch(const Exception_c &)
			{
				kernel.LogStream() << "[OgreConsole_c::CmdCd] Invalid dir " << args[1];
			}
		}
		else
			Kernel_c::GetInstance().LogMessage("[OgreConsole_c::CmdCd] Insuficient parameters");
	}

	void Console_c::CmdDumpTable(const StringVector_t &args, Context_c &)
	{
		Log_c::Stream_c stream = Kernel_c::GetInstance().LogStream();

		try
		{
			Register::Table_c *table;
			if(args.size() == 2)
			{
				table = &Register::GetTable(Path_c(args[1]));
				stream << "Values on " << args[1] << '\n';
			}
			else if(args.size() == 3)
			{
				table = &Register::GetTable(args[1], args[2]);
				stream << "Values on " << args[2];
			}
			else
			{
				stream << "[OgreConsole_c::CmdDumpTable] Insuficient parameters, usage: dumpTable <path>\n";
				return;
			}

			stream << "FIXME\n";
			/*
			for(Dictionary_c::StringMapConstIterator_t it = dict->begin(), end = dict->end(); it != end; ++it)
			{
				stream << it->first << " = " << it->second << "\n";
			}
			*/
		}
		catch(std::exception &e)
		{
			stream << e.what();
		}
	}

	//
	//
	//EDIT BOX
	//
	//
	inline Console_c::EditBox_c::EditBox_c(void):
		uCursorPos(0)
	{

	}

	inline void Console_c::EditBox_c::AddChar(Char_t ch)
	{
		strStr.insert(uCursorPos, 1, ch);

		++uCursorPos;
	}


	inline void Console_c::EditBox_c::RetreatCursor(void)
	{
		if(uCursorPos > 0)
			--uCursorPos;
	}

	inline void Console_c::EditBox_c::AdvanceCursor(void)
	{
		if(uCursorPos <= strStr.length())
			++uCursorPos;
	}

	inline void Console_c::EditBox_c::Backspace(void)
	{
		if(uCursorPos > 0)
		{
			--uCursorPos;
			strStr.erase(uCursorPos, 1);
		}
	}

	inline void Console_c::EditBox_c::Clear(void)
	{
		strStr.clear();
		uCursorPos = 0;
	}

	inline void Console_c::EditBox_c::SetStr(const String_t &str)
	{
		strStr = str;

		uCursorPos = strStr.length();
	}

	inline const String_t &Console_c::EditBox_c::GetStr(void) const
	{
		return(strStr);
	}
}
