#include "Event.h"

namespace Cobra
{
	Events::Event::Event(EEventType EventType)
		: mEventType(EventType),
		  bHandled(false)
	{
	}

	std::string Events::Event::ToString() const
	{
		return {};
	}

	std::string Events::Event::EventTypeToString(EEventType EventType)
	{
		switch (EventType)
		{
		case EEventType::KeyPressed:
			return "KeyPressed";
		case EEventType::KeyReleased:
			return "KeyReleased";
		case EEventType::MousePressed:
			return "MousePressed";
		case EEventType::MouseReleased:
			return "MouseReleased";
		case EEventType::MouseMoved:
			return "MouseMoved";
		case EEventType::WindowResize:
			return "WindowResize";
		}

		return "Invalid Event Type";
	}
}
