#include "entity.h"
#include "types.h"
#include "event.h"
#include "enumerations.h"

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

		void RenderCustom(float interpolation, int xOffset = 0, int yOffset = 0);

		bool InWindow(vec2<int> pos);
		bool InTitleBar(vec2<int> pos);

		void Focus();
		void Unfocus();
		/*
		 * Get Methods
		 */
		vec2<int> size();
		bool focus();
		bool grabbed();
		bool screenBound();
		bool followCamera();

		/*
		 * Set Methods
		 */
		void SetSize(vec2<int> size);
		void SetScreenBound(bool screenBound);
		void SetFollowCamera(bool followCamera);

		/*
		 * Public Attributes
		 */
		std::string title;
		PanelType type;		
		vec4<float> bgColor;
		vec4<float> barColor;
		bool locked;

	private:

		/*
		 * Private Attributes
		 */
		vec2<int> _size;

		int _barHeight;
		int _focus;
		bool _grabbed;
		bool _screenBound;
		bool _followCamera;
		vec2<int> _offset;
};
