#pragma once

#include "../Utilities/Array/Array.hpp"
#include "../Utilities/Move/Move.hpp"
#include "Digital.hpp"
#include "Pin.hpp"

#include <stdint.h>

namespace devuino::onboard
{
	using devuino::pin::Resistor;
	using devuino::utilities::Array;

	template<typename T1, typename T2>
	class MatrixInputNode;

	template<unsigned int Width,
			 unsigned int Height,
			 typename DigitalInputBackend = devuino::onboard::DigitalInput,
			 typename DigitalOutputBackend = devuino::onboard::DigitalOutput>
	class MatrixInput
	{
		static_assert(Width > 0, "Width of matrix cannot be zero");
		static_assert(Height > 0, "Height of matrix cannot be zero");

		Array<DigitalInputBackend, Width> inputs;
		Array<DigitalOutputBackend, Height> outputs;

	  public:
		MatrixInput(Array<DigitalInputBackend, Width>&& inputs, Array<DigitalOutputBackend, Height>&& outputs) :
			inputs {devuino::move(inputs)}, outputs {devuino::move(outputs)}
		{
			for (auto& pin : this->inputs)
			{
				pin.resistor(Resistor::PullUp);
			}

			for (auto& pin : this->outputs)
			{
				pin = true;
			}
		}

		MatrixInputNode<DigitalInputBackend, DigitalOutputBackend> node(const unsigned int x, const unsigned int y)
		{
			return {inputs[x], outputs[y]};
		}
	};

	template<typename DigitalInputBackend, typename DigitalOutputBackend>
	class MatrixInputNode
	{
		DigitalInputBackend& input;
		DigitalOutputBackend& output;

		Resistor pull;

		explicit MatrixInputNode(DigitalInputBackend& input, DigitalOutputBackend& output) : input {input}, output {output} { }

	  public:
		template<unsigned int Width, unsigned int Height, typename T1, typename T2>
		friend class MatrixInput;

		operator bool() const
		{
			output.digital(false);
			const bool reading = input.digital();
			output.digital(true);

			return (pull == Resistor::PullUp) ? reading : !reading;
		}

		void resistor(const Resistor pull) { this->pull = pull; }
	};
}