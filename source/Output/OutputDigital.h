#ifndef OUTPUTDIGITAL_H
#define OUTPUTDIGITAL_H

namespace devuino
{
    class OutputDigital
    {
      public:
        virtual void off() = 0;
        virtual void on() = 0;
        void toggle();

      protected:
        bool active = false;
    };
}

#endif