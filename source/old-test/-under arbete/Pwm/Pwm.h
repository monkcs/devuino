#ifndef PWM_H
#define PWM_H

class Pwm {
	protected:
		void dutycycle(int pin, int value);
	private:
		int duty = 0;
};

#endif
