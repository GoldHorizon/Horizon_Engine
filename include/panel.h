#include "entity.h"
#include "types.h"
#include "event.h"

#include <string>

class Panel : public Entity
{
	public:
		/*
		 * Constructors/Destructors
		 */
		Panel();
		~Panel();

		/*
		 * Class Methods
		 */
		void HandleEvents(Event&);
		void Update();
		void Render(float interpolation, int xOffset = 0, int yOffset = 0);

		void RenderCustom(float interpolation, int xOffset = 0, int yOffset = 0);

		/*
		 * Get Methods
		 */
		std::string title();
		vec2<int> dim();
		vec4<float> bgColor();
		vec4<float> barColor();
		bool focused();
		bool grabbed();

		/*
		 * Set Methods
		 */
		void SetTitle(std::string title);
		void SetPos(vec2<int> dim);
		void SetBgColor(vec4<float> color);
		void SetBarColor(vec4<float> color);

	private:
		std::string _title;
		vec2<int> _dim;
		int _barHeight;

		vec4<float> _bgColor;
		vec4<float> _barColor;

		bool _focused;
		bool _grabbed;
};
