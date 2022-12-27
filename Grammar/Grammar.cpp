#include "Grammar.h"
#include <stdlib.h>
#include <time.h>

Grammar::Grammar(std::vector<char> terminals, std::vector<char> neterminals, char start_symbol, std::map<std::string,
	std::vector<std::string>> production) : terminals{ terminals }, neterminals{ neterminals }, start_symbol{ start_symbol },
	production{ production }
{}

std::vector<char> Grammar::getVn()
{
	return neterminals;

}

std::vector<char> Grammar::getVt()
{
	return terminals;
}

char Grammar::getS()
{
	return start_symbol;
}

std::map<std::string, std::vector<std::string> >Grammar::getP()
{
	return production;
}

bool Grammar::find(std::vector<char> vector, char symbol)
{
	bool ok = 0;
	for (auto x : vector) {
		if (x == symbol)
			ok = 1;
	}
	return ok;
}

bool Grammar::VerifyGrammar()
{
	//VN inters. VT = mulț. vidă
	for (auto x : terminals)
		for (auto y : neterminals)
			if (x == y) {
				return false;
			}
	//S apartine VN
	int ok = 0;
	for (auto x : neterminals)
		if (x == start_symbol) {
			ok = 1;
			break;
		}
	if (ok == 0) {
		return false;
	}

	//pentru fiecare regulă, membrul stâng conține cel puțin un neterminal
	for (auto x : production) {
		ok = 0;
		for (auto z : x.first) {
			for (auto y : neterminals)
				if (z == y)
					ok = 1;
		}
	}
	if (ok == 0) {
		return false;
	}

	// există cel puțin o producție care are în stânga doar S
	ok = 0;
	for (auto x : production) {
		for (auto y : x.first)
			if (y == start_symbol)
				ok = 1;
	}
	if (ok == 0) {
		return false;
	}

	// fiecare producție conține doar elemente din VN și VT
	for (auto x : production) {
		for (auto y : x.first) {
			if (!find(getVn(), y) && !find(getVt(), y))
				return false;
		}
		for (auto f : x.second) {
			for (auto g : f) {
				if (!find(getVn(), g) && !find(getVt(), g))
					return false;
			}
		}
	}
	return true;
}

bool Grammar::IsRegular() // verifica daca gramatica este regulata sau nu
{
	if (this->VerifyGrammar() == false)
		return false;
	for (auto it = production.begin(); it != production.end(); it++)
	{
		if (it->first.size() != 1)
			return false;
		if (!find(getVn(), it->first[0]))
			return false;
		for (int i = 0; i < it->second.size(); i++)
		{
			if (it->second[i].length() > 2)
				return false;
			if (it->second[i].length() == 1)
				if (!find(getVt(), it->second[i][0]))
					return false;
			if (it->second[i].length() == 2)
				if ((!find(getVt(), it->second[i][0])) || !find(getVn(), it->second[i][1]))
					return false;
		}
	}
	return true;
}

std::string Grammar::GenerateWord()
{
	std::string word;
	word = getS();
	std::cout << word;
	srand((unsigned)time(NULL));
	int randomNumber = rand() % production[word].size();
	word = production[word][randomNumber];
	std::cout << " -> " << word;
	std::string aux;
	srand((unsigned)time(NULL));
	while (find(getVn(), word[word.length() - 1])) 
	{
		aux = word[word.length() - 1];
		int random = rand() % production[aux].size();
		word.pop_back(); 
		word += production[aux][random];
		std::cout << " -> " << word;
	}
	return word;
}

FiniteAutomaton Grammar::TransformareGramaticaAutomat()
{
	//Q = Vn reunit T
	char symbol = 'X';
	std::vector<char> states = neterminals; 
	states.push_back(symbol);

	//alphabet = Vt
	std::vector<char> alphabet = terminals; 

	//q0 = S
	char initialState = start_symbol;

	//F = T
	std::vector<char> finalStates;
	finalStates.push_back(symbol);

	//std::map<std::string, std::vector<std::string>> production
	std::unordered_map<std::pair<char, char>, std::vector<char>, pair_hash> transitionFunction;
	for (auto x : production) {
		for (auto y : x.second) { //verificam fiecare element din vectorul de string-uri, pentru cele 2 cazuriz
			if (y.size() == 1) { //neterminal -> terminal
				char state = x.first[0];
				char alphabet = y[0];
				transitionFunction[{state, alphabet}].push_back(symbol);
			}
			if (y.size() == 2) { //terminal -> terminal,neterminal
				char state = x.first[0];
				char alphabet = y[0];
				char final = y[1];
				transitionFunction[{state, alphabet}].push_back(final);
			}
		}
	}
	FiniteAutomaton automaton(states, alphabet, initialState, transitionFunction, finalStates);

	return automaton;
}

std::istream& operator>>(std::istream& in, Grammar& gramm)
{
	bool end = false;
	while (!end) {
		char neterm;
		in >> neterm;
		if (neterm == '/')
			end = true;
		else
			gramm.neterminals.push_back(neterm);
	}
	bool end1 = false;
	while (!end1) {
		char term;
		in >> term;
		if (term == '/')
			end1 = true;
		else
			gramm.terminals.push_back(term);
	}
	in >> gramm.start_symbol;

	std::string left, right;
	while (in >> left >> right) {
		auto it = gramm.production.find(left);
		if (it == gramm.production.end()) 
		{
			std::vector<std::string> v;
			v.push_back(right);
			std::pair<std::string, std::vector<std::string>>pair = std::make_pair(left, v);
			gramm.production.insert(pair);
		}
		else
			gramm.production[left].push_back(right);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Grammar& gramm)
{
	out << "Vn = { ";
	for (auto x : gramm.neterminals)
		out << x << " ";
	out << "}" << "\n";
	out << "Vt = { ";
	for (auto y : gramm.terminals)
		out << y << " ";
	out << "}" << "\n";
	out << "S = { " << gramm.start_symbol << " }" << "\n";
	out << "P: " << "\n";
	for (auto z : gramm.production)
		for (auto v : z.second)
			out << z.first << "->" << v << "\n";
	return out;
}
