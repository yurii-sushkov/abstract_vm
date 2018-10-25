// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Parser.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ysushkov <ysushkov@student.unit.ua>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/24 14:37:56 by ysushkov          #+#    #+#             //
//   Updated: 2018/10/24 14:37:57 by ysushkov         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <vector>
# include <limits>
# include "mutantstack.hpp"
# include "Factory.hpp"

static const std::string names[20] = {
		"push int8(",
		"push int16(",
		"push int32(",
		"push float(",
		"push double(",
	};

class Parser
{
private:
	std::vector<std::string>		_v;
	Factory							_f;
	MutantStack<const IOperand *>	ms;
	bool							_exit;
	bool							_error;
	unsigned long					i;
public:
	Parser();
	Parser(std::vector<std::string> v);
	~Parser();
	void	push(std::string push);

	void	add();
	void	sub();
	void	mul();
	void	div();
	void	mod();

	void	top();

	void	dump();

	void	assert(std::string assert);
	void	pop();
	void	print();
	void	exit();
};

#endif
