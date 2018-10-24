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

template<class T> int add_overflow(T a, T b)
{
	if ((a < 0) && (b < 0))
	{
		if (a < 0 && (a + b) > b)
			return 1;
		else if ((a + b) < b)
			return 2;
	}
	return 0;
}

template<class T> int mul_overflow(T a, T b)
{
	T a1;
	T b1;

	if (a < 0)
		a1 = a * -1;
	else
		a1 = a;
	if (b < 0)
		b1 = b * -1;
	else
		b1 = b;
	if (a1 > std::numeric_limits<T>::max() / b1)
	{
		if ((a < 0) && (b < 0))
			return 2;
		else if ((a > 0) && (b > 0))
			return 2;
		else return 1;
	}
	return 0;
}

template<class T> Operand<T>::Operand( void )
{
	this->_value = std::to_string(static_cast<T>(0));
}

template<class T> Operand<T>::Operand( Operand<T> const & obj )
{
	*this = obj;
}

template<class T> Operand<T>::~Operand( void ){}

template<class T> Operand<T> & Operand<T>::operator=( Operand<T> const & rhs )
{
	this->_value = rhs._value; return *this;
}

template<class T> Operand<T>::Operand( T value )
{
	this->_value = std::to_string(value);
}

template<class T> Operand<T>::Operand( std::string str )
{
	this->_value = std::to_string(static_cast<T>(stod(str)));
}

template<class T> IOperand const * Operand<T>::operator+( IOperand const & rhs ) const
{
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	T lval = static_cast<T>(stod(this->_value));
	T rval = static_cast<T>(stod(rhs.toString()));
	if (add_overflow<T>(lval, rval) == 1)
		throw (Operand::UnderflowException());
	else if (add_overflow<T>(lval, rval) == 2)
		throw (Operand::OverflowException());
	Factory * factory = new Factory();
	IOperand const * ret_val = factory->createOperand(this->getType(), std::to_string(static_cast<T>(stod(this->_value)) + rval));
	delete factory;
	return ret_val;
}

template<class T> IOperand const * Operand<T>::operator-( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs - *this);
	T lval = static_cast<T>(stod(this->_value));
	T rval = static_cast<T>(stod(rhs.toString()));
	if (add_overflow<T>(lval, rval * -1) == 1)
		throw (Operand::UnderflowException());
	if (add_overflow<T>(lval, rval * -1) == 2)
		throw (Operand::OverflowException());
	Factory * factory = new Factory();
	IOperand const * ret_val = factory->createOperand(this->getType(), std::to_string(lval - rval));
	delete factory;
	return ret_val;
}

template<class T> IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
	if (this->getPrecision() < rhs.getPrecision()) return (rhs * *this);
	T lval = static_cast<T>(stod(this->_value));
	T rval = static_cast<T>(stod(rhs.toString()));
	if (mul_overflow<T>(lval, rval) == 1)
		throw (Operand::UnderflowException());
	else if (mul_overflow<T>(lval, rval) == 2)
		throw (Operand::OverflowException());
	Factory * factory = new Factory();
	IOperand const * ret_val = factory->createOperand(this->getType(), std::to_string(lval * rval));
	delete factory;
	return ret_val;
}

template<class T> IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
	double lval = stod(this->toString());
	double rval  = stod(rhs.toString());

	if (rval == 0)
		throw (Operand::DivideByZero());
	eOperandType final_type = (this->getPrecision() < rhs.getPrecision() ? rhs.getType() : this->getType());
	Factory * factory = new Factory();
	IOperand const * ret_val = factory->createOperand(final_type, std::to_string(lval / rval));
	delete factory;
	return ret_val;
}

template<class T> IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
	long lval = stol(this->toString());
	long rval  = stol(rhs.toString());

	if (rval == 0)
		throw (Operand::DivideByZero());
	eOperandType final_type = (this->getPrecision() < rhs.getPrecision() ? rhs.getType() : this->getType());
	Factory * factory = new Factory();
	IOperand const * ret_val = factory->createOperand(final_type, std::to_string(lval % rval));
	delete factory;
	return ret_val;
}

template<class T> std::string const & Operand<T>::toString( void ) const {
	return this->_value;
}

template<> int			Operand<int8_t>::getPrecision( void ) const
{
	return Int8;
}

template<> eOperandType	Operand<int8_t>::getType( void ) const
{
	return Int8;
}

template<> int			Operand<int16_t>::getPrecision( void ) const
{
	return Int16;
}

template<> eOperandType	Operand<int16_t>::getType( void ) const
{
	return Int16;
}

template<> int			Operand<int32_t>::getPrecision( void ) const
{
	return Int32;
}

template<> eOperandType	Operand<int32_t>::getType( void ) const
{
	return Int32;
}

template<> int			Operand<float>::getPrecision( void ) const
{
	return Float;
}

template<> eOperandType	Operand<float>::getType( void ) const
{
	return Float;
}

template<> int			Operand<double>::getPrecision( void ) const
{
	return Double;
}

template<> eOperandType	Operand<double>::getType( void ) const
{
	return Double;
}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
