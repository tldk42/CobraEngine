#pragma once

#include "../Common/CommonInclude.h"

namespace Cobra
{
	namespace Events
	{
		enum class EEventType
		{
			KeyPressed  = 1 << 0,
			KeyReleased = 1 << 1,

			MousePressed  = 1 << 2,
			MouseReleased = 1 << 3,
			MouseMoved    = 1 << 4,

			WindowResize = 1 << 5
		};

		class Event
		{
		public:
			Event(EEventType EventType);

			inline bool       IsHandled() const { return bHandled; }
			inline EEventType GetEventType() const { return mEventType; }

			virtual std::string ToString() const;
			virtual std::string EventTypeToString(EEventType EventType);

		protected:
			bool       bHandled;
			EEventType mEventType;

		private:
			friend class EventDispatcher;
		};
	}
}
