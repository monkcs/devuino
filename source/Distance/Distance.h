#ifndef DISTANCE_H
#define DISTANCE_H

typedef unsigned char byte; /* Remove before shipping */

class Distance {
	public:
        virtual float metre() = 0;
        float decimetre();
        float centimetre();
        float millimetre();
        float micrometre();
        float yard();
        float foot();
        float inch();
};

#endif
