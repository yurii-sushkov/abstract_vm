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

void	validation(std::vector<std::string> v)
{
	Parser *p = new Parser(v);

	delete p;
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

void	readconsole(void)
{
	std::string		buff_string;
	std::vector<std::string> queue;

	while (!std::cin.fail() && buff_string.find(";;"))
	{
		std::getline(std::cin, buff_string);
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
