// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Factory.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ysushkov <ysushkov@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/18 16:45:56 by ysushkov          #+#    #+#             //
//   Updated: 2018/10/18 16:45:57 by ysushkov         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Factory.hpp"

Factory::Factory(){}

Factory::~Factory(){}

Factory::Factory(Factory const & src)
{
	static_cast<void>(src);
}

Factory &Factory::operator=(Factory const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	return new Operand<int8_t>(std::stoi(value));
}

IOperand const * Factory::createInt16( std::string const & value ) const
{
	return new Operand<int16_t>(std::stoi(value));
}

IOperand const * Factory::createInt32( std::string const & value ) const
{
	return new Operand<int32_t>(std::stoi(value));
}

IOperand const * Factory::createFloat( std::string const & value ) const
{
	return new Operand<float>(std::stof(value));
}

IOperand const * Factory::createDouble( std::string const & value ) const
{
	return new Operand<double>(std::stod(value));
}	

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const
{
	const IOperand *(Factory::*func[5])(std::string const & value) const = {
		&Factory::createInt8, 
		&Factory::createInt16,
		&Factory::createInt32,
		&Factory::createFloat,
		&Factory::createDouble
	};
	IOperand const * newOperand = (this->*func[type])(value);
	return newOperand;
}

Factory::OutOfRange::OutOfRange(){}

Factory::OutOfRange::~OutOfRange() throw(){}

char const * Factory::OutOfRange::what(void) const throw()
{
	return "Impossible value.";
}

Factory::PopException::PopException(){}

Factory::PopException::~PopException() throw(){}

char const * Factory::PopException::what(void) const throw()
{
	return "Cannot pop an empty stack!";
}

Factory::AssertException::AssertException(){}

Factory::AssertException::~AssertException() throw(){}

char const * Factory::AssertException::what(void) const throw()
{
	return "The values are not equal. Program is stopped.";
}

Factory::StackException::StackException(){}

Factory::StackException::~StackException() throw(){}

char const * Factory::StackException::what(void) const throw()
{
	return "stack is empty.";
}

Factory::PrintException::PrintException(){}

Factory::PrintException::~PrintException() throw(){}

char const * Factory::PrintException::what(void) const throw()
{
	return "The top value of the stack is not an 8-bit integer. Program is stopped.";
}

Factory::ExitException::ExitException(){}

Factory::ExitException::~ExitException() throw(){}

char const * Factory::ExitException::what(void) const throw()
{
	return "'exit' command line is not present. Program is stopped.";
}

Factory::InvalidInput::InvalidInput(){}

Factory::InvalidInput::~InvalidInput() throw(){}

char const * Factory::InvalidInput::what(void) const throw()
{
	return "Invalid input.";
}

Factory::InvalidArgument::InvalidArgument(){}

Factory::InvalidArgument::~InvalidArgument() throw(){}

char const * Factory::InvalidArgument::what(void) const throw()
{
	return "Invalid argument.";
}

Factory::NotEnough::NotEnough(){}

Factory::NotEnough::~NotEnough() throw(){}

char const * Factory::NotEnough::what(void) const throw()
{
	return "Not enough elements in stack.";
}

Factory::CurrentException::CurrentException(){}

Factory::CurrentException::~CurrentException() throw(){}

char const * Factory::CurrentException::what(void) const throw()
{
	return "Sorry, currently this option is not allowed. Program is stopped.";
}
