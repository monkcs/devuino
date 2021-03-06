#ifndef OUTPUTDIGITAL_H
#define OUTPUTDIGITAL_H

namespace devuino
{
    class OutputDigital
    {
        public:
            virtual void off() = 0;
            virtual void on() = 0;

            void set(const bool value) const
            {
                value ? on() : off();
            };

            bool toggle()
            {
                active = !active;
                set(active);

                return active;
            };

        protected:
            bool active = false;
    };
}

#endif
