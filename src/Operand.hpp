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

#ifndef OPERAND_T
# define OPERAND_T

# ifndef OPERAND_T_DEFINED
    #  define OPERAND_T_DEFINED
    template<class T> class Operand;
    #  include "Factory.hpp"
# endif

# include "IOperand.hpp"
//# include "AbstractVM.hpp"
# include <exception>
# include <string>
# include <limits>

// enum eOperandType {Int8, Int16, Int32, Float, Double};

//****************************
// CLASS TEMPLATE DECLARATION
//****************************

template<class T> class Operand : public IOperand {
public:
	Operand( void );
	Operand( T value );
	Operand( std::string str );
	Operand( Operand const & obj );
	~Operand( void );
	Operand & operator=( Operand const & rhs );
	int getPrecision( void ) const; // Precision of the type of the instance
	eOperandType getType( void ) const; // Type of the instance
	IOperand const * operator+( IOperand const & rhs ) const; // Sum
	IOperand const * operator-( IOperand const & rhs ) const; // Difference
	IOperand const * operator*( IOperand const & rhs ) const; // Product
	IOperand const * operator/( IOperand const & rhs ) const; // Quotient
	IOperand const * operator%( IOperand const & rhs ) const; // Modulo
	std::string const & toString( void ) const; // String representation of the instance

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

protected:
	std::string _value;
};

#endif
