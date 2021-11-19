#pragma once
#include "../Tools/Array.hpp"
#include "Pin.hpp"

#include <stdint.h>

namespace devuino::pin
{
	using devuino::tools::Array;

	template<class Type>
	class MatrixNode;

	template<class Type, unsigned int Width, unsigned int Height>
	class Matrix
	{
		Array<Type, Width> inputs;
		Array<Type, Height> outputs;

	  public:
		Matrix(const Array<Type, Width> inputs, const Array<Type, Height> outputs) : inputs {inputs}, outputs {outputs}
		{
			for (auto& pin : this->inputs)
			{
				pin.initiate(Input::Digital, Resistor::PullUp);
			}

			for (auto& pin : this->outputs)
			{
				pin.initiate(Output::Digital);
				pin.digital(true);
			}
		};

		MatrixNode<Type> node(const unsigned int x, const unsigned int y) { return MatrixNode<Type> {inputs[x], outputs[y]}; };
	};

	template<class Type>
	class MatrixNode
	{
		Type& input;
		Type& output;

		mutable Resistor pull;

		explicit MatrixNode(Type& input, Type& output) : input {input}, output {output} {};

	  public:
		template<class T, unsigned int Width, unsigned int Height>
		friend class Matrix;

		bool digital() const
		{
			output.digital(false);
			const bool reading = input.digital();
			output.digital(true);

			return (pull == Resistor::PullUp) ? reading : !reading;
		};

		/* void digital(const bool value) const {}; */

		/* Only for compability */
		void initiate([[maybe_unused]] const Input mode, const Resistor pull = Resistor::None) const { this->pull = pull; };
		// void initiate(const Output mode) const {};
	};
}