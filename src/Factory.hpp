// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Factory.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ysushkov <ysushkov@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/18 16:46:00 by ysushkov          #+#    #+#             //
//   Updated: 2018/10/18 16:46:02 by ysushkov         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FACTORY_HPP
# define FACTORY_HPP

# include <iostream>
# include "IOperand.hpp"
# include "Operand.hpp"

class Factory
{
public:
	Factory();
	~Factory();
	Factory(Factory const &src);
	Factory &operator=(Factory const &rhs); 
	IOperand const * createOperand(eOperandType, std::string const & value) const;

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
	class OutOfRange : public std::exception
	{
	public:
		OutOfRange(void){};
		virtual ~OutOfRange() throw(){};
		char const * what(void) const throw()
		{
			return "Impossible value.";
		}
	};

	class PopException : public std::exception
	{
	public:
		PopException(void){};
		virtual ~PopException() throw(){};
		char const * what(void) const throw()
		{
			return "Cannot pop an empty stack!";
		}
	};

	class AssertException : public std::exception
	{
	public:
		AssertException(void){};
		virtual ~AssertException() throw(){};
		char const * what(void) const throw()
		{
			return "The values are not equal. Program is stopped.";
		}
	};

	class StackException : public std::exception
	{
	public:
		StackException(void){};
		virtual ~StackException() throw(){};
		char const * what(void) const throw()
		{
			return "stack is empty.";
		}
	};	

	class PrintException : public std::exception
	{
	public:
		PrintException(void){};
		virtual ~PrintException() throw(){};
		char const * what(void) const throw()
		{
			return "The top value of the stack is not an 8-bit integer. Program is stopped.";
		}
	};	

	class ExitException : public std::exception
	{
	public:
		ExitException(void){};
		virtual ~ExitException() throw(){};
		char const * what(void) const throw()
		{
			return "'exit' command line is not present. Program is stopped.";
		}
	};

	class InvalidInput : public std::exception
	{
	public:
		InvalidInput(void){};
		virtual ~InvalidInput() throw(){};
		char const * what(void) const throw()
		{
			return "Invalid input.";
		}
	};

	class InvalidArgument : public std::exception
	{
	public:
		InvalidArgument(void){};
		virtual ~InvalidArgument() throw(){};
		char const * what(void) const throw()
		{
			return "Invalid argument.";
		}
	};

	class NotEnough : public std::exception
	{
	public:
		NotEnough(void){};
		virtual ~NotEnough() throw(){};
		char const * what(void) const throw()
		{
			return "Not enough elements in stack.";
		}
	};
};

#endif
