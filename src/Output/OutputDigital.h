#ifndef OUTPUTDIGITAL_H
#define OUTPUTDIGITAL_H

namespace devuino
{
    class OutputDigital
    {
        public:
            void off() const
            {
                set(false);
            }

            void on() const
            {
                set(true);
            }

            void operator= (const bool value) const
            {
                set(value);
            };

            void toggle() const
            {
                set(!status());
            };

        protected:
            virtual void set(const bool value) = 0;
            virtual bool status() const = 0;
    };
}

#endif
