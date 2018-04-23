#ifndef SWITCH_H
#define SWITCH_H
#include <Output.h>

class Switch : public Output  {
	public:
		Switch(int pin);
		~Switch();
		void off();
		void on();
	private:
		int pin;
		void change(bool state);
};

#endif
