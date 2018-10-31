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
	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;
	class OutOfRange : public std::exception
	{
	public:
		OutOfRange(void);
		virtual ~OutOfRange() throw();
		char const * what(void) const throw();
	};

	class PopException : public std::exception
	{
	public:
		PopException(void);
		virtual ~PopException() throw();
		char const * what(void) const throw();
	};

	class AssertException : public std::exception
	{
	public:
		AssertException(void);
		virtual ~AssertException() throw();
		char const * what(void) const throw();
	};

	class StackException : public std::exception
	{
	public:
		StackException(void);
		virtual ~StackException() throw();
		char const * what(void) const throw();
	};	

	class PrintException : public std::exception
	{
	public:
		PrintException(void);
		virtual ~PrintException() throw();
		char const * what(void) const throw();
	};

	class ExitException : public std::exception
	{
	public:
		ExitException(void);
		virtual ~ExitException() throw();
		char const * what(void) const throw();
	};

	class InvalidInput : public std::exception
	{
	public:
		InvalidInput(void);
		virtual ~InvalidInput() throw();
		char const * what(void) const throw();
	};

	class InvalidArgument : public std::exception
	{
	public:
		InvalidArgument(void);
		virtual ~InvalidArgument() throw();
		char const * what(void) const throw();
	};

	class NotEnough : public std::exception
	{
	public:
		NotEnough(void);
		virtual ~NotEnough() throw();
		char const * what(void) const throw();
	};

	class CurrentException : public std::exception
	{
	public:
		CurrentException(void);
		virtual ~CurrentException() throw();
		char const * what(void) const throw();
	};

	class LogarithmException : public std::exception
	{
	public:
		LogarithmException(void);
		virtual ~LogarithmException() throw();
		char const * what(void) const throw();
	};

	class EndException : public std::exception
	{
	public:
		EndException(void);
		virtual ~EndException() throw();
		char const * what(void) const throw();
	};

};

#endif
