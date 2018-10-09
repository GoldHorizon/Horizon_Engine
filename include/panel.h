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

		bool InWindow(vec2<int> pos);
		bool InTitleBar(vec2<int> pos);

		void Focus();
		void Unfocus();
		/*
		 * Get Methods
		 */
		std::string title();
		vec2<int> dim();
		vec4<float> bgColor();
		vec4<float> barColor();
		bool focus();
		bool grabbed();
		bool locked();
		bool screenBound();
		bool followCamera();

		/*
		 * Set Methods
		 */
		void SetTitle(std::string title);
		void SetPos(vec2<int> dim);
		void SetBgColor(vec4<float> color);
		void SetBarColor(vec4<float> color);
		void SetLocked(bool locked);
		void SetScreenBound(bool screenBound);
		void SetFollowCamera(bool followCamera);

	private:
		std::string _title;
		vec2<int> _dim;
		int _barHeight;

		vec4<float> _bgColor;
		vec4<float> _barColor;

		int _focus;
		bool _grabbed;
		bool _locked;
		bool _screenBound;
		bool _followCamera;
		vec2<int> _offset;
};
