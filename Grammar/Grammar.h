#pragma once
#include<iostream>
#include<vector>
#include<string>
#include <map>
#include"FiniteAutomaton.h"

class Grammar
{
private:
	std::vector<char> terminals;
	std::vector<char> neterminals;
	char start_symbol;
	std::map<std::string, std::vector<std::string>> production;

public:
	Grammar() = default;
	Grammar(std::vector<char> terminals, std::vector<char> neterminals, char start_symbol,
		std::map<std::string, std::vector<std::string>> production);
	std::vector<char> getVn();
	std::vector<char> getVt();
	char getS();
	std::map<std::string, std::vector<std::string> >getP();
	bool find(std::vector<char> v, char c);
	bool VerifyGrammar();
	bool IsRegular();
	std::string GenerateWord();
	friend std::istream& operator>>(std::istream& in, Grammar& gramm);
	friend std::ostream& operator<<(std::ostream& out, const Grammar& gramm);

	FiniteAutomaton TransformareGramaticaAutomat();
	
};

