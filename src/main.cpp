// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ysushkov <ysushkov@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/17 11:44:28 by ysushkov          #+#    #+#             //
//   Updated: 2018/10/17 12:40:20 by ysushkov         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <exception>
#include "Parser.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include "Factory.hpp"
#include "mutantstack.hpp"
#define BUFFSIZE 1000
/*
void	operations(std::vector<std::string> ret)
{
	MutantStack<const IOperand *> ms;

	Factory f;

	for (unsigned long i = 0; i < ret.size(); i++)
	{
		if (ret[i].compare(0, 10, "push int8(") == 0)
		{
			try
			{
				ms.push(f.createOperand(Int8, ret[i].substr(10, ret[i].length() - 11)));
				long long int buff = std::stoi(ret[i].substr(10, ret[i].length() - 11));

				if (buff <= -128 || buff >= 127 || ret[i].substr(10, ret[i].length() - 11).length() > 10)
					throw (Factory::OutOfRange());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
		}
		else if (ret[i].compare(0, 11, "push int16(") == 0)
		{
			try
			{
				ms.push(f.createOperand(Int16, ret[i].substr(11, ret[i].length() - 12)));
				long long int buff = std::stoi(ret[i].substr(11, ret[i].length() - 12));

				if (buff <= -32768 || buff >= 32767)
					throw (Factory::OutOfRange());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
		}
		else if (ret[i].compare(0, 11, "push int32(") == 0)
		{
			try
			{
				ms.push(f.createOperand(Int32, ret[i].substr(11, ret[i].length() - 12)));
				long long int buff = std::stoi(ret[i].substr(11, ret[i].length() - 12));

				if (buff <= -2147483648 || buff >= 2147483647)
					throw (Factory::OutOfRange());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
		}
		else if (ret[i].compare(0, 11, "push float(") == 0)
		{
			try
			{
				ms.push(f.createOperand(Float, ret[i].substr(11, ret[i].length() - 12)));
				long double buff = std::stod(ret[i].substr(11, ret[i].length() - 12));

				if (buff <= 1.2E-38 || buff >= 3.4E+38 || ret[i].substr(11, ret[i].length() - 12).length() > 7)
					throw (Factory::OutOfRange());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
		}
		else if (ret[i].compare(0, 12, "push double(") == 0)
		{
			try
			{
				ms.push(f.createOperand(Double, ret[i].substr(12, ret[i].length() - 13)));
				double buff = std::stod(ret[i].substr(12, ret[i].length() - 13));

				if (buff <= 2.3E-308 || buff >= 1.7E+308 || ret[i].substr(12, ret[i].length() - 13).length() > 15)
					throw (Factory::OutOfRange());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
		}
		else if (ret[i].compare("pop") == 0)
		{
			try
			{
				if (ms.size() > 0)
					ms.pop();
				else if (ms.size() == 0)
					throw (Factory::PopException());
			}
			catch (std::exception &e)
			{
				std::cout << "Error : " << e.what() << std::endl;
				return ;
			}
		}
		else if (ret[i].compare("add") == 0)
		{
			try
			{
				if (ms.size() < 2)
					throw (Factory::NotEnough());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
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
				return ;
			}
		}
		else if (ret[i].compare("sub") == 0)
		{
			try
			{
				if (ms.size() < 2)
					throw (Factory::NotEnough());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			const IOperand *t1 = ms.top();
			ms.pop();
			const IOperand *t2 = ms.top();
			ms.pop();
			ms.push(*t2 - *t1);
		}
		else if (ret[i].compare("mul") == 0)
		{
			try
			{
				if (ms.size() < 2)
					throw (Factory::NotEnough());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			const IOperand *t1 = ms.top();
			ms.pop();
			const IOperand *t2 = ms.top();
			ms.pop();
			try
			{
				ms.push(*t2 * *t1);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				return ;
			}
		}
		else if (ret[i].compare("div") == 0)
		{
			try
			{
				if (ms.size() < 2)
					throw (Factory::NotEnough());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
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
				return ;
			}
		}
		else if (ret[i].compare("mod") == 0)
		{
			try
			{
				if (ms.size() < 2)
					throw (Factory::NotEnough());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
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
				return ;
			}
		}
		else if (ret[i].compare("dump") == 0)
		{
			MutantStack<const IOperand *>copy = ms;
			while (copy.size() != 0)
			{
				std::cout << copy.top()->toString() << std::endl;
				copy.pop();
			}
		}
		else if (ret[i].compare(0, 7, "assert ") == 0)
		{
			if (ms.size() == 0)
			{
				std::cout << "ERROR : impossible operation." << std::endl;
				return ;
			}
			if (ret[i].compare(0, 12, "assert int8(") == 0)
			{
				const IOperand * tmp;

				try
				{
					tmp = (f.createOperand(Int8, ret[i].substr(12, ret[i].length() - 13)));
					long long int buff = std::stoi(ret[i].substr(12, ret[i].length() - 13));
					if (buff <= -128 || buff >= 127)
						throw (Factory::OutOfRange());
					else if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
						throw (Factory::AssertException());
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
			}
			else if (ret[i].compare(0, 13, "assert int16(") == 0)
			{
				const IOperand * tmp;

				try
				{ 
					tmp = (f.createOperand(Int16, ret[i].substr(13, ret[i].length() - 14)));
					long long int buff = std::stoi(ret[i].substr(13, ret[i].length() - 14));
					if (buff <= -32768 || buff >= 32767)
						throw (Factory::OutOfRange());
					else if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
						throw (Factory::AssertException());
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
			}
			else if (ret[i].compare(0, 13, "assert int32(") == 0)
			{
				const IOperand * tmp;

				try
				{
					tmp = (f.createOperand(Int32, ret[i].substr(13, ret[i].length() - 14)));
					long long int buff = std::stoi(ret[i].substr(13, ret[i].length() - 14));

					if (buff <= -2147483648 || buff >= 2147483647)
						throw (Factory::OutOfRange());
					else if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
						throw (Factory::AssertException());
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
			}
			else if (ret[i].compare(0, 13, "assert float(") == 0)
			{
				const IOperand * tmp;

				try
				{
					tmp = (f.createOperand(Float, ret[i].substr(13, ret[i].length() - 14)));
					long double buff = std::stod(ret[i].substr(13, ret[i].length() - 14));
					if (buff <= 1.2E-38 || buff >= 3.4E+38)
						throw (Factory::OutOfRange());
					else if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
						throw (Factory::AssertException());
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
			}
			else if (ret[i].compare(0, 14, "assert double(") == 0)
			{
				const IOperand * tmp;

				try
				{
					tmp = (f.createOperand(Double, ret[i].substr(14, ret[i].length() - 15)));
					long double buff = std::stod(ret[i].substr(14, ret[i].length() - 15));
					if (buff <= 2.3E-308 || buff >= 1.7E+308)
						throw (Factory::OutOfRange());
					else if (tmp->getType() != ms.top()->getType() || tmp->toString() != ms.top()->toString())
						throw (Factory::AssertException());
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
			}
		}
		else if (ret[i].compare("print") == 0)
		{
			try
			{
				if (ms.size() == 0)
					throw (Factory::StackException());
				else if (ms.top()->getType() == Int8)
				{
					std::cout << "The top value of the stack is an 8-bit integer. Corresponding character: ";
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
				return ;
			}
		}
		else if (ret[i].compare("exit") == 0)
			break ;
	}
}

void	validation(std::vector<std::string> queue)
{
	std::vector<std::string>	ret;
	bool						exit = false;

	for (unsigned long i = 0; i < queue.size(); i++)
	{
		if (queue[i].compare(0, 10, "push int8(") == 0)
		{
			std::string	q;
			int			j = 10;
			int			c = 0;

			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || (queue[i][j] == '-' && c == 0)))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(10, c);
			ret.push_back("push int8(" + q + ")");
		}
		else if (queue[i].compare(0, 11, "push int16(") == 0)
		{
			std::string	q;
			int			j = 11;
			int			c = 0;
			
			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || (queue[i][j] == '-' && c == 0)))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(11, c);
			ret.push_back("push int16(" + q + ")");
		}
		else if (queue[i].compare(0, 11, "push int32(") == 0)
		{
			std::string	q;
			int			j = 11;
			int			c = 0;

			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || (queue[i][j] == '-' && c == 0)))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(11, c);
			ret.push_back("push int32(" + q + ")");
		}
		else if (queue[i].compare(0, 11, "push float(") == 0)
		{
			std::string	q;
			int			j = 11;
			int			c = 0;

			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (c == 0 && (!(queue[i][j] >= '0' && queue[i][j] <= '9') || queue[i][j] == '-'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || queue[i][j] == '.'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(11, c);
			ret.push_back("push float(" + q + ")");
		}
		else if (queue[i].compare(0, 12, "push double(") == 0)
		{
			std::string	q;
			int			j = 12;
			int			c = 0;

			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (c == 0 && (!(queue[i][j] >= '0' && queue[i][j] <= '9') || queue[i][j] == '-'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || queue[i][j] == '.'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(12, c);
			ret.push_back("push double(" + q + ")");
		}
		else if (queue[i].compare(0, 12, "assert int8(") == 0)
		{
			std::string	q;
			int			j = 12;
			int			c = 0;

			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || (queue[i][j] == '-' && c == 0)))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(12, c);
			ret.push_back("assert int8(" + q + ")");
		}
		else if (queue[i].compare(0, 13, "assert int16(") == 0)
		{
			std::string	q;
			int			j = 13;
			int			c = 0;
			
			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || (queue[i][j] == '-' && c == 0)))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(13, c);
			ret.push_back("assert int16(" + q + ")");
		}
		else if (queue[i].compare(0, 13, "assert int32(") == 0)
		{
			std::string	q;
			int			j = 13;
			int			c = 0;

			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (!(queue[i][j] >= '0' && queue[i][j] <= '9'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(13, c);
			ret.push_back("assert int32(" + q + ")");
		}
		else if (queue[i].compare(0, 13, "assert float(") == 0)
		{
			std::string	q;
			int			j = 13;
			int			c = 0;

			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (c == 0 && (!(queue[i][j] >= '0' && queue[i][j] <= '9') || queue[i][j] == '-'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || queue[i][j] == '.'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
				j++;
				c++;
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(13, c);
			ret.push_back("assert float(" + q + ")");
		}
		else if (queue[i].compare(0, 14, "assert double(") == 0)
		{
			std::string	q;
			int			j = 14;
			int			c = 0;

			while (queue[i][j] != ')' && queue[i][j] != 0)
			{
				try
				{
					if (c == 0 && (!(queue[i][j] >= '0' && queue[i][j] <= '9') || queue[i][j] == '-'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
					if (!((queue[i][j] >= '0' && queue[i][j] <= '9') || queue[i][j] == '.'))
					{
						throw (Factory::InvalidArgument());
						break ;
					}
					j++;
					c++;
				}
				catch (std::exception &e)
				{
					std::cout << "ERROR : " << e.what() << std::endl;
					return ;
				}
			}
			try
			{
				if (queue[i][j] != ')' && c == 0)
					throw (Factory::InvalidInput());
			}
			catch (std::exception &e)
			{
				std::cout << "ERROR : " << e.what() << std::endl;
				return ;
			}
			q = queue[i].substr(14, c);
			ret.push_back("assert double(" + q + ")");
		}
		else if (queue[i].compare(0, 3, "pop") == 0 && (queue[i][3] == 0 || queue[i][3] == ';' || queue[i][3] == ' '))
			ret.push_back("pop");
		else if (queue[i].compare(0, 4, "dump") == 0 && (queue[i][4] == 0 || queue[i][4] == ';' || queue[i][4] == ' '))
			ret.push_back("dump");
		else if (queue[i].compare(0, 3, "add") == 0 && (queue[i][3] == 0 || queue[i][3] == ';' || queue[i][3] == ' '))
			ret.push_back("add");
		else if (queue[i].compare(0, 3, "sub") == 0 && (queue[i][3] == 0 || queue[i][3] == ';' || queue[i][3] == ' '))
			ret.push_back("sub");
		else if (queue[i].compare(0, 3, "mul") == 0 && (queue[i][3] == 0 || queue[i][3] == ';' || queue[i][3] == ' '))
			ret.push_back("mul");
		else if (queue[i].compare(0, 3, "div") == 0 && (queue[i][3] == 0 || queue[i][3] == ';' || queue[i][3] == ' '))
			ret.push_back("div");
		else if (queue[i].compare(0, 3, "mod") == 0 && (queue[i][3] == 0 || queue[i][3] == ';' || queue[i][3] == ' '))
			ret.push_back("mod");
		else if (queue[i].compare(0, 5, "print") == 0 && (queue[i][5] == 0 || queue[i][5] == ';' || queue[i][5] == ' '))
			ret.push_back("print");
		else if (queue[i].compare(0, 4, "exit") == 0 && (queue[i][4] == 0 || queue[i][4] == ';' || queue[i][4] == ' '))
		{
			exit = true;
			ret.push_back("exit");
		}
		else if (queue[i][0] == ';')
		{
			if (queue[i][1] == ';')
				ret.push_back(";;");
		}
		else
		{
			std::cout << "ERROR : Invalid input" << std::endl;
			return ;
		}
	}
	try
	{
		if (exit == false)
		{
			throw (Factory::ExitException());
		}
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
		return ;
	}
	operations(ret);
}
*/

void	validation(std::vector<std::string> v)
{
	Parser p(v);

	p.exit();
}

void	readfile(std::string s)
{
	std::ifstream	file;
	std::string		tmp;
	std::vector<std::string> queue;
	size_t c = 0;

	file.open(s);
	if (file.is_open() && std::getline(file, tmp, '\0'))
	{
		while (tmp.find('\0') != std::string::npos)
			c++;
	}
	else
	{
		std::cout << "File descriptor is incorrect" << std::endl;;
		return ;
	}
	file.close();
	if (tmp[c] != '\n')
		tmp += '\n';
	size_t pos = 0;
	std::string token;
	while ((pos = tmp.find('\n')) != std::string::npos)
	{
		queue.push_back(tmp.substr(0, pos));
		tmp.erase(0, pos + 1);
	}
	validation(queue);
}

bool	containsWhites(std::string buff_string)
{
	int i;

	i = 0;
	while (buff_string[i])
	{
		if (buff_string[i] != ' ' && buff_string[i] != '\t')
			return false;
		i++;
	}
	return true;
}

void	readconsole(void)
{
	std::string		buff_string;
	std::vector<std::string> queue;

	while (!std::cin.fail())
	{
		std::getline(std::cin, buff_string);
		if (buff_string != "" && !containsWhites(buff_string))
			queue.push_back(buff_string);
		if (buff_string.find(";;") != std::string::npos)
			break ;
	}
	validation(queue);
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		readfile(argv[1]);
	else if (argc == 1)
		readconsole();
	return 0;
}
