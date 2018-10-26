// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ysushkov <ysushkov@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/18 16:11:23 by ysushkov          #+#    #+#             //
//   Updated: 2018/10/18 16:11:24 by ysushkov         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERAND_HPP
# define OPERAND_HPP
/*
# ifndef OPERAND_T_DEFINED
    #  define OPERAND_T_DEFINED
    template<class T> class Operand;
    #  include "Factory.hpp"
# endif
*/
# include "Factory.hpp"
# include "IOperand.hpp"
# include <exception>
# include <string>
# include <limits>

template<class T> class Operand : public IOperand
{
protected:
	std::string _value;
public:
	Operand(void);
	Operand(T value);
	Operand(std::string str);
	Operand(Operand const & src);
	~Operand(void);
	Operand & operator=(Operand const & rhs);
	int getPrecision(void) const;
	eOperandType getType(void) const;
	IOperand const * operator+(IOperand const & rhs) const;
	IOperand const * operator-(IOperand const & rhs) const;
	IOperand const * operator*(IOperand const & rhs) const;
	IOperand const * operator/(IOperand const & rhs) const;
	IOperand const * operator%(IOperand const & rhs) const;
	std::string const & toString(void) const;

	class DivideByZero : public std::exception
	{
	public:
		DivideByZero(void){};
		virtual ~DivideByZero() throw(){};
		char const * what(void) const throw()
		{
			return "ERROR : Impossible divide by zero.";
		}
	};

	class UnderflowException : public std::exception
	{
	public:
		UnderflowException(void){};
		virtual ~UnderflowException() throw(){};
		char const * what(void) const throw()
		{
			return "ERROR : Underflow Exception.";
		}
	};

	class OverflowException : public std::exception
	{
	public:
		OverflowException(void){};
		virtual ~OverflowException() throw(){};
		char const * what(void) const throw()
		{
			return "ERROR : Overflow Exception.";
		}
	};
};

#endif
