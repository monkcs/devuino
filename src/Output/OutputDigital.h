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
                if (value)
                {
                    on();
                }
                else
                {
                    off();
                }
            };

            void toggle()
            {
                active = !active;

                if (active)
                {
                    on();
                }
                else
                {
                    off();
                }
            };

        protected:
            bool active = false;
    };
}

#endif
