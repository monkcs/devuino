#ifndef LIGHT_H
#define LIGHT_H

typedef unsigned char byte; /* Remove before shipping */

class Light {
	public:
		byte brightness();
		void brightness(float percent);
		virtual void brightness(byte value) = 0;
	protected:
	    byte bright = 0;
};

#endif
