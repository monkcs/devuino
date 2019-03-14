#ifndef INPUTDIGITAL_H
#define INPUTDIGITAL_H

namespace devuino
{
    class InputDigital
    {
      public:
        InputDigital(const bool debounce)
            : debounce(debounce){};
        virtual bool value() = 0;

      protected:
        const bool debounce;
    };
}

#endif
