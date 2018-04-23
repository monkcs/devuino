#ifndef OUTPUT_H
#define OUTPUT_H

class Output {
	public:
		virtual void off() = 0;
		virtual void on() = 0;
		void toggle();
	protected:
		bool active = false;
};

#endif
