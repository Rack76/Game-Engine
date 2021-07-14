#ifndef INCLUDED_EVENTS_HPP
#define INCLUDED_EVENTS_HPP

namespace Engine {
	namespace Events {
		struct Quit { };

		struct Mouse_motion {
			int new_x, new_y;
		};

		struct Mouse_click {
			enum struct Action { up, down } action;
			enum struct Button { left, middle, right } button;
		};
	}
}

#endif