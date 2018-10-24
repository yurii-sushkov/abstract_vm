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
