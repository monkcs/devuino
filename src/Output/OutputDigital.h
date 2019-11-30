#ifndef OUTPUTDIGITAL_H
#define OUTPUTDIGITAL_H

namespace devuino
{
    class OutputDigital
    {
        public:
            virtual void off() = 0;
            virtual void on() = 0;

            void operator= (const bool value) const
            {
                set(value);
            };

            void toggle()
            {
                set(!status());
            };

        protected:
            void set(const bool value) const
            {
                value ? on() : off();
            };

            virtual bool status() const = 0;
    };
}

#endif
