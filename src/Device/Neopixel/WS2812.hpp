#pragma once

namespace devuino
{
	namespace device
	{
		struct WS2812 final
		{
			struct one final
			{
				static const unsigned int high = 900;
				static const unsigned int low = 600;
			};

			struct zero final
			{
				static const unsigned int high = 400;
				static const unsigned int low = 900;
			};
		};

		struct WS2812B final
		{
			struct one final
			{
				static const unsigned int high = 800;
				static const unsigned int low = 450;
			};

			struct zero final
			{
				static const unsigned int high = 400;
				static const unsigned int low = 850;
			};
		};
	}
}