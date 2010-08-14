#ifndef PH_INPUT_MAPPER_H
#define PH_INPUT_MAPPER_H

#include <boost/ptr_container/ptr_map.hpp>

#include <PH_Context.h>
#include <PH_Node.h>

#include "PH_InputDevice.h"
#include "PH_InputManager.h"

namespace Phobos
{
	class InputMapper_c;

	typedef boost::intrusive_ptr<InputMapper_c> InputMapperPtr_t;

	class PH_INPUT_API InputMapper_c: public Node_c, private InputManagerListener_c
	{		
		private:
			// =====================================================
			// PRIVATE TYPES
			// =====================================================
			struct ActionBind_s
			{
				inline ActionBind_s()
				{
				}

				inline ActionBind_s(const String_c &command, const String_c &actionName, UInt_t action):
					strCommand(command),
					strActionName(actionName),
					uDeviceAction(action)
				{
					//empty
				}

				String_c	strCommand;
				String_c	strActionName;			
				UInt_t		uDeviceAction;
			};

			typedef std::map<UInt_t, ActionBind_s> ActionBindMap_t;
			typedef ActionBindMap_t::value_type ActionBindMapPair_t;			

			class DeviceMapper_c: private InputDeviceListener_c
			{
				public:
					DeviceMapper_c(InputMapper_c &mapper, InputDevicePtr_t device);
					DeviceMapper_c(const DeviceMapper_c &rhs);

					DeviceMapper_c &operator =(const DeviceMapper_c &rhs);

					void Bind(const String_c &actionName, const String_c &cmd);
					void Unbind(const String_c &actionName);

				private:
					virtual void InputEvent(const InputEvent_s &event);

					void OnInputEventButton(const InputEvent_s &event);
					void OnInputEventThumb(const InputEvent_s &event);
					void AddEventButtonInfo(std::stringstream &stream, const InputEvent_s &event) const;

					UInt_t GetActionId(const String_c &name);

				private:
					ActionBindMap_t					mapActions;

					InputDevicePtr_t				ipInputDevice;
					InputMapper_c					&rclInputMapper;				
			};				

		public:
			// =====================================================
			// PUBLIC METHODS
			// =====================================================
			static InputMapperPtr_t Create(const String_c &name, Context_c &context);

			void Bind(const String_c &devicePathName, const String_c &actionName, const String_c &cmd);
			void Unbind(const String_c &devicePathName, const String_c &actionName);						

			inline void Disable();
			inline void Enable();
			inline bool IsDisabled() const;

			void Execute(const std::string &cmd);

		private:
			// =====================================================
			// PRIVATE METHODS
			// =====================================================
			InputMapper_c(const String_c &name, Context_c &context);
			~InputMapper_c(void);

			void OnDeviceAttached(InputDevicePtr_t &device);
			void OnDeviceDetached(InputDevicePtr_t &device);

			void AddEventButtonInfo(std::stringstream &stream, InputEvent_s &event, DeviceMapper_c &info) const;

			void OnInputEventButton(InputEvent_s &event, DeviceMapper_c &info);		
			void OnInputEventThumb(InputEvent_s &event, DeviceMapper_c &info);
			
			DeviceMapper_c &GetDeviceMapper(const String_c &deviceName);

			void InputManagerEvent(const InputManagerEvent_s &event);			

			void CmdUnbind(const StringVector_t &args, Context_c &);
			void CmdBind(const StringVector_t &args, Context_c &);			

		private:
			// =====================================================
			// PRIVATE ATRIBUTES
			// =====================================================			
			typedef std::map<String_c, DeviceMapper_c> InputDeviceMap_t;
			InputDeviceMap_t		mapInputDevices;

			Context_c				&rclContext;

			bool					fDisable;				

			ContextCmd_c			cmdBind;
			ContextCmd_c			cmdUnbind;
	};

	inline void InputMapper_c::Disable()
	{
		fDisable = true;
	}

	inline void InputMapper_c::Enable()
	{
		fDisable = false;
	}

	inline bool InputMapper_c::IsDisabled() const
	{
		return(fDisable);
	}
}

#endif