// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ysushkov <ysushkov@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/18 16:11:27 by ysushkov          #+#    #+#             //
//   Updated: 2018/10/24 14:03:44 by ysushkov         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Operand.hpp"

template<class T> int add_overflow(T x, T y)
{
	if ((x < 0) && (y < 0))
	{
		if (x < 0 && (x + y) > y)
			return 1;
		else if ((x + y) < y)
			return 2;
	}
	return 0;
}

template<class T> int mul_overflow(T x, T y)
{
	T x1;
	T y1;

	if (x < 0)
		x1 = x * -1;
	else
		x1 = x;
	if (y < 0)
		y1 = y * -1;
	else
		y1 = y;
	if (x1 > std::numeric_limits<T>::max() / y1)
	{
		if ((x < 0) && (y < 0))
			return 2;
		else if ((x > 0) && (y > 0))
			return 2;
		else return 1;
	}
	return 0;
}

template<class T> Operand<T>::Operand( void )
{
	this->_value = std::to_string(static_cast<T>(0));
}

template<class T> Operand<T>::Operand(Operand<T> const & src)
{
	*this = src;
}

template<class T> Operand<T>::~Operand( void ){}

template<class T> Operand<T> & Operand<T>::operator=(Operand<T> const & rhs)
{
	this->_value = rhs._value; return *this;
}

template<class T> Operand<T>::Operand(T value)
{
	this->_value = std::to_string(value);
}

template<class T> Operand<T>::Operand(std::string str)
{
	this->_value = std::to_string(static_cast<T>(std::stod(str)));
}

template<class T> IOperand const * Operand<T>::operator+(IOperand const & rhs) const
{
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	T lval = static_cast<T>(std::stod(this->_value));
	T rval = static_cast<T>(std::stod(rhs.toString()));
	if (add_overflow<T>(lval, rval) == 1)
		throw (Operand::UnderflowException());
	else if (add_overflow<T>(lval, rval) == 2)
		throw (Operand::OverflowException());
	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(this->getType(), std::to_string(static_cast<T>(std::stod(this->_value)) + rval));
	delete factory;
	return res;
}

template<class T> IOperand const * Operand<T>::operator-(IOperand const & rhs) const
{
//	if (this->getPrecision() < rhs.getPrecision())
//	{
//		return (rhs - *this);
	//}
	T lval = static_cast<T>(std::stod(this->_value));
	T rval = static_cast<T>(std::stod(rhs.toString()));
	if (add_overflow<T>(lval, rval * -1) == 1)
		throw (Operand::UnderflowException());
	if (add_overflow<T>(lval, rval * -1) == 2)
		throw (Operand::OverflowException());
	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(this->getType(), std::to_string(lval - rval));
	delete factory;
	return res;
}

template<class T> IOperand const * Operand<T>::operator*(IOperand const & rhs) const
{
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs * *this);
	T lval = static_cast<T>(std::stod(this->_value));
	T rval = static_cast<T>(std::stod(rhs.toString()));
	if (mul_overflow<T>(lval, rval) == 1)
		throw (Operand::UnderflowException());
	else if (mul_overflow<T>(lval, rval) == 2)
		throw (Operand::OverflowException());
	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(this->getType(), std::to_string(lval * rval));
	delete factory;
	return res;
}

template<class T> IOperand const * Operand<T>::operator/(IOperand const & rhs) const
{
	double lval = stod(this->toString());
	double rval  = stod(rhs.toString());

	if (rval == 0)
		throw (Operand::DivideByZero());
	
	eOperandType t;

	if (this->getPrecision() < rhs.getPrecision())
		t = rhs.getType();
	else
		t = this->getType();

	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(t, std::to_string(lval / rval));
	delete factory;
	return res;
}

template<class T> IOperand const * Operand<T>::operator%(IOperand const & rhs) const
{
	long lval = stol(this->toString());
	long rval  = stol(rhs.toString());

	if (rval == 0)
		throw (Operand::DivideByZero());

	eOperandType t;

	if (this->getPrecision() < rhs.getPrecision())
		t = rhs.getType();
	else
		t = this->getType();

	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(t, std::to_string(lval % rval));
	delete factory;
	return res;
}

template<class T> std::string const & Operand<T>::toString() const
{
	return this->_value;
}

template<> int			Operand<int8_t>::getPrecision() const
{
	return Int8;
}

template<> eOperandType	Operand<int8_t>::getType() const
{
	return Int8;
}

template class Operand<int8_t>;

template<> int			Operand<int16_t>::getPrecision() const
{
	return Int16;
}

template<> eOperandType	Operand<int16_t>::getType() const
{
	return Int16;
}

template class Operand<int16_t>;

template<> int			Operand<int32_t>::getPrecision() const
{
	return Int32;
}

template<> eOperandType	Operand<int32_t>::getType() const
{
	return Int32;
}

template class Operand<int32_t>;

template<> int			Operand<float>::getPrecision() const
{
	return Float;
}

template<> eOperandType	Operand<float>::getType() const
{
	return Float;
}

template class Operand<float>;

template<> int			Operand<double>::getPrecision() const
{
	return Double;
}

template<> eOperandType	Operand<double>::getType() const
{
	return Double;
}

template class Operand<double>;
