// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Parser.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ysushkov <ysushkov@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/24 14:38:01 by ysushkov          #+#    #+#             //
//   Updated: 2018/10/24 14:38:02 by ysushkov         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Parser.hpp"

void	Parser::push(std::string push)
{
	if (push.substr(5, 5).compare("int8(") == 0) //push int8
	{
		int c = 0;
		int j = 10;

		try
		{
			while (push[j] != ')' && push[j] != 0)
			{
				if (!((push[j] >= '0' && push[j] <= '9') || (push[j] == '-' && c == 0)))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (push[j] != ')' || c == 0)
			{
				throw (Factory::InvalidInput());
			}
			if (c > 4)//push.substr(10, c).length() > 4) //push.length() - 11).length() > 4)
			{
				throw (Factory::OutOfRange());
			}
			long long int buff = std::stol(push.substr(10, c)); //push.length() - 11));
			if (buff < -128 || buff > 127)
			{
				throw (Factory::OutOfRange());
			}
			ms.push(this->_f.createOperand(Int8, push.substr(10, c)));//push.length() - 11)));
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
	else if (push.substr(5, 6) == "int16(") //push int16
	{
		int c = 0;
		int j = 11;

		try
		{
			while (push[j] != ')' && push[j] != 0)
			{
				if (!((push[j] >= '0' && push[j] <= '9') || (push[j] == '-' && c == 0)))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (push[j] != ')' || c == 0)
				throw (Factory::InvalidInput());
			if (c > 6)//push.substr(11, c).length() > 6)//push.length() - 12).length() > 6)
				throw (Factory::OutOfRange());
			long long int buff = std::stol(push.substr(11, c));//push.length() - 12));
			if (buff < -32768 || buff > 32767)
				throw (Factory::OutOfRange());
			ms.push(this->_f.createOperand(Int16, push.substr(11, c)));
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
	else if (push.substr(5, 6) == "int32(") //push int32
	{
		int c = 0;
		int j = 11;

		try
		{
			while (push[j] != ')' && push[j] != 0)
			{
				if (!((push[j] >= '0' && push[j] <= '9') || (push[j] == '-' && c == 0)))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (push[j] != ')' || c == 0)
				throw (Factory::InvalidInput());
			if (push[11] == '-' && c > 11) //push.length() - 12).length() > 11)
				throw (Factory::OutOfRange());
			else if (push[11] != '-' && c > 10) //push.substr(11, push.length() - 12).length() > 10)
				throw (Factory::OutOfRange());
			if (std::numeric_limits<int>::max() < std::stoll(push.substr(11, c)))
				throw (Factory::OutOfRange());
			if (std::numeric_limits<int>::min() > std::stoll(push.substr(11, c)))
				throw (Factory::OutOfRange());
			//long long int buff = std::stol(push.substr(11, push.length() - 12));
			//if (buff <= -2147483648 || buff >= 2147483647)
			//	throw (Factory::OutOfRange());
			ms.push(this->_f.createOperand(Int32, push.substr(11, c)));
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
	else if (push.substr(5, 6) == "float(") //push float
	{
		int c = 0;
		int j = 11;

		try
		{
			while (push[j] != ')' && push[j] != 0)
			{
				if (c == 0 && (!((push[j] >= '0' && push[j] <= '9') || push[j] == '-')))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				else if (c > 0 && (!((push[j] >= '0' && push[j] <= '9') || push[j] == '.')))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (push[j] != ')' || c == 0)
					throw (Factory::InvalidInput());
			//if (push.substr(11, push.length() - 12).length() > 7)
			//	throw (Factory::OutOfRange());
			//long double buff = std::stod(push.substr(11, push.length() - 12));
			//if (buff <= 1.2E-38 || buff >= 3.4E+38)
			if (std::stod(push.substr(11, c)) > std::numeric_limits<float>::max())
				throw (Factory::OutOfRange());
			if (std::stod(push.substr(11, c)) < std::numeric_limits<float>::lowest())
				throw (Factory::OutOfRange());
			ms.push(this->_f.createOperand(Float, push.substr(11, c)));
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
	else if (push.substr(5, 7) == "double(") //push float
	{
		int c = 0;
		int j = 12;
		//std::cout << push.substr(12, push.length() - 13) << std::endl;
		try
		{
			while (push[j] != ')' && push[j] != 0)
			{
				if (c == 0 && (!((push[j] >= '0' && push[j] <= '9') || push[j] == '-')))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				if (c > 0 && (!((push[j] >= '0' && push[j] <= '9') || push[j] == '.')))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (push[j] != ')' || c == 0)
					throw (Factory::InvalidInput());
			if (std::stod(push.substr(12, c)) > std::numeric_limits<double>::max())
				throw (Factory::OutOfRange());
			if (std::stod(push.substr(12, c)) < std::numeric_limits<double>::lowest())
				throw (Factory::OutOfRange());
			/*if (push.substr(12, push.length() - 13).length() > 15)
				throw (Factory::OutOfRange());
			long double buff = std::stod(push.substr(12, push.length() - 13));
			if (buff <= 2.3E-308 || buff >= 1.7E+308)
				throw (Factory::OutOfRange());*/
			ms.push(this->_f.createOperand(Double, push.substr(12, c)));
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
}

void	Parser::add()
{
	try
	{
		if (ms.size() < 2)
			throw (Factory::NotEnough());
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
		this->_error = true;
		return ;
	}
	const IOperand *t1 = ms.top();
	ms.pop();
	const IOperand *t2 = ms.top();
	ms.pop();
	try
	{
		ms.push(*t1 + *t2);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		this->_error = true;
		return ;
	}
}

void	Parser::sub()
{
	try
	{
		if (ms.size() < 2)
			throw (Factory::NotEnough());
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
		this->_error = true;
		return ;
	}
	const IOperand *t1 = ms.top();
	ms.pop();
	const IOperand *t2 = ms.top();
	ms.pop();
	try
	{
		ms.push(*t2 - *t1);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		this->_error = true;
		return ;
	}
}

void	Parser::mul()
{
	try
	{
		if (ms.size() < 2)
			throw (Factory::NotEnough());
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
		this->_error = true;
		return ;
	}
	const IOperand *t1 = ms.top();
	ms.pop();
	const IOperand *t2 = ms.top();
	ms.pop();
	try
	{
		ms.push(*t1 * *t2);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		this->_error = true;
		return ;
	}
}

void	Parser::div()
{
	try
	{
		if (ms.size() < 2)
			throw (Factory::NotEnough());
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
		this->_error = true;
		return ;
	}
	const IOperand *t1 = ms.top();
	ms.pop();
	const IOperand *t2 = ms.top();
	ms.pop();
	try
	{
		ms.push(*t2 / *t1);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		this->_error = true;
		return ;
	}
}

void	Parser::mod()
{
	try
	{
		if (ms.size() < 2)
			throw (Factory::NotEnough());
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
		this->_error = true;
		return ;
	}
	const IOperand *t1 = ms.top();
	ms.pop();
	const IOperand *t2 = ms.top();
	ms.pop();
	try
	{
		ms.push(*t2 % *t1);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		this->_error = true;
		return ;
	}
}

void	Parser::top()
{
	try
	{
		if (ms.size() == 0)
			throw (Factory::StackException());
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
		this->_error = true;
		return ;
	}

	std::cout << this->ms.top() << std::endl;
}

void	Parser::dump()
{
	MutantStack<const IOperand *>copy = this->ms;

	while (copy.size() != 0)
	{
		std::cout << copy.top()->toString() << std::endl;
		copy.pop();
	}
}

void	Parser::assert(std::string assert)
{
	if (assert.substr(7, 5).compare("int8(") == 0) //assert int8
	{
		int c = 0;
		int j = 12;
		const IOperand *tmp;

		try
		{
			while (assert[j] != ')' && assert[j] != 0)
			{
				if (!((assert[j] >= '0' && assert[j] <= '9') || (assert[j] == '-' && c == 0)))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (assert[j] != ')' || c == 0)
				throw (Factory::InvalidInput());
			if (c > 4)
				throw (Factory::OutOfRange());
			long long int buff = std::stol(assert.substr(12, c));
			if (buff < -128 || buff > 127)
				throw (Factory::OutOfRange());
			tmp = this->_f.createOperand(Int8, assert.substr(12, c));
			if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
				throw (Factory::AssertException());
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
	else if (assert.substr(7, 6) == "int16(") //assert int16
	{
		int c = 0;
		int j = 13;
		const IOperand *tmp;

		try
		{
			while (assert[j] != ')' && assert[j] != 0)
			{
				if (!((assert[j] >= '0' && assert[j] <= '9') || (assert[j] == '-' && c == 0)))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (assert[j] != ')' || c == 0)
				throw (Factory::InvalidInput());
			if (c > 6)
				throw (Factory::OutOfRange());
			long long int buff = std::stol(assert.substr(13, c));
			if (buff < -32768 || buff > 32767)
				throw (Factory::OutOfRange());
			tmp = this->_f.createOperand(Int16, assert.substr(13, c));
			if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
				throw (Factory::AssertException());
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
	else if (assert.substr(7, 6) == "int32(") //assert int32
	{
		int c = 0;
		int j = 13;
		const IOperand *tmp;

		try
		{
			while (assert[j] != ')' && assert[j] != 0)
			{
				if (!((assert[j] >= '0' && assert[j] <= '9') || (assert[j] == '-' && c == 0)))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (assert[j] != ')' || c == 0)
				throw (Factory::InvalidInput());
			if (assert[13] == '-' && c > 11)
				throw (Factory::OutOfRange());
			else if(assert[13] != '-' && c > 10)
				throw (Factory::OutOfRange());
			//long long int buff = std::stoll(assert.substr(13, assert.length() - 14));
			//if (buff < -2147483648 || buff > 2147483647)
			if (std::numeric_limits<int>::max() < std::stoll(assert.substr(13, c)))
				throw (Factory::OutOfRange());
			tmp = this->_f.createOperand(Int32, assert.substr(13, c));
			if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
				throw (Factory::AssertException());
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
	else if (assert.substr(7, 6) == "float(") //assert float
	{
		int c = 0;
		int j = 13;
		const IOperand *tmp;

		try
		{
			while (assert[j] != ')' && assert[j] != 0)
			{
				if (c == 0 && (!((assert[j] >= '0' && assert[j] <= '9') || assert[j] == '-')))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				if (c > 0 && (!((assert[j] >= '0' && assert[j] <= '9') || assert[j] == '.')))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (assert[j] != ')' || c == 0)
					throw (Factory::InvalidInput());
			if (std::stod(assert.substr(13, c)) > std::numeric_limits<float>::max())
				throw (Factory::OutOfRange());
			if (std::stod(assert.substr(13, c)) < std::numeric_limits<float>::lowest())
				throw (Factory::OutOfRange());
			//long double buff = std::stod(assert.substr(13, assert.length() - 14));
			//if (buff < 1.2E-38 || buff > 3.4E+38 || assert.substr(13, assert.length() - 14).length() > 9)
			//	throw (Factory::OutOfRange());
			tmp = this->_f.createOperand(Float, assert.substr(13, c));
			if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
				throw (Factory::AssertException());
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
	else if (assert.substr(7, 7) == "double(") //assert double
	{
		int c = 0;
		int j = 14;
		const IOperand * tmp;

		try
		{
			while (assert[j] != ')' && assert[j] != 0)
			{
				if (c == 0 && (!((assert[j] >= '0' && assert[j] <= '9') || assert[j] == '-')))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				if (c > 0 && (!((assert[j] >= '0' && assert[j] <= '9') || assert[j] == '.')))
				{
					throw (Factory::InvalidArgument());
					break ;
				}
				c++;
				j++;
			}
			if (assert[j] != ')' || c == 0)
				throw (Factory::InvalidInput());
			//long double buff = std::stod(assert.substr(14, assert.length() - 15));
			//if (buff < 2.3E-308 || buff > 1.7E+308 || assert.substr(14, assert.length() - 15).length() > 15)
			//	throw (Factory::OutOfRange());
			if (std::stod(assert.substr(14, c)) > std::numeric_limits<double>::max())
				throw (Factory::OutOfRange());
			if (std::stod(assert.substr(14, c)) < std::numeric_limits<double>::lowest())
				throw (Factory::OutOfRange());
			tmp = this->_f.createOperand(Double, assert.substr(14, c));
			if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
				throw (Factory::AssertException());
		}
		catch (std::exception &e)
		{
			std::cout << "ERROR : " << e.what() << std::endl;
			this->_error = true;
			return ;
		}
	}
}

void	Parser::pop()
{
	try
	{
		if (ms.size() == 0)
			throw (Factory::PopException());
		else
			this->ms.pop();
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
		return ;
	}
}

void	Parser::print()
{	
	try
	{
		if (ms.size() == 0)
			throw (Factory::StackException());
		else if (ms.top()->getType() == Int8)
		{
			char temp = std::stoi(ms.top()->toString());
			if (temp >= 32 && temp <= 126)
				std::cout << "'" << temp << "'." << std::endl;
			else
				std::cout << "Not printable." << std::endl;
		}
		else
			throw (Factory::PrintException());
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
		this->_error = true;
		return ;
	}
}

void	Parser::exit()
{
	this->_exit = true;
}

Parser::Parser(){}

Parser::~Parser(){}

Parser::Parser(std::vector<std::string> v)
{
	this->_v = v;
	this->_exit = false;
	this->_error = false;

	for (this->i = 0; i < _v.size(); i++)
	{
		if (_v[i].compare(0, 4, "exit") == 0)
			this->exit();
	}
	try
	{
		if (this->_exit == false)
			throw (Factory::ExitException());
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
		return ;
	}
	for (this->i = 0; i < _v.size(); i++)
	{
		if (this->_error == true)
			break ;
		if (_v[i].compare(0, 5, "push ") == 0)
			this->push(_v[i]);
		else if (_v[i].compare(0, 4, "dump") == 0)
			this->dump();
		else if (_v[i].compare(0, 7, "assert ") == 0)
		{
			try
			{
				if (ms.size() == 0)
					throw (Factory::StackException());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : line : " << i  + 1 << " : " << e.what() << std::endl;
				this->_error = true;
				return ;
			}
			this->assert(_v[i]);
		}
		else if (_v[i].compare(0, 5, "print") == 0)
			this->print();
		else if (_v[i].compare(0, 3, "pop") == 0)
			this->pop();
		else if (_v[i].compare(0, 3, "add") == 0)
			this->add();
		else if (_v[i].compare(0, 3, "sub") == 0)
			this->sub();
		else if (_v[i].compare(0, 3, "mul") == 0)
			this->mul();
		else if (_v[i].compare(0, 3, "div") == 0)
			this->div();
		else if (_v[i].compare(0, 3, "mod") == 0)
			this->mod();
		else
		{
			try
			{
				if (_v[i] != ";;" && _v[i][0] != ';' && _v[i] != "" && _v[i].compare(0, 4, "exit") != 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : line : " << i + 1 << " : " << e.what() << std::endl;
				this->_error = true;
				return ;
			}
		}
	}
}

