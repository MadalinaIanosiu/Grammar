#include "FiniteAutomaton.h"

FiniteAutomaton::FiniteAutomaton(std::vector<char> states, std::vector<char> alphabet, char initialState,
	std::unordered_map<std::pair<char, char>, std::vector<char>, pair_hash> transition, std::vector<char> finalStates) :
	alphabet{alphabet}, states{states}, initialState{initialState}, transition{transition}, finalStates{finalStates}
{}

void FiniteAutomaton::PrintAutomaton(std::ostream& out) const
{
	out << "Stari: ";
	for (unsigned i = 0; i < states.size(); i++)
	{
		out << states[i];
		if (i != states.size() - 1)
		{
			out << ", ";
		}
		else
		{
			out << std::endl;
		}
	}
	out << "Alfabet de intrare: ";
	for (unsigned i = 0; i < alphabet.size(); i++)
	{
		out << alphabet[i];
		if (i != alphabet.size() - 1)
		{
			out << ", ";
		}
		else
		{
			out << std::endl;
		}
	}
	out << "Starea initiala: " << initialState << std::endl;
	out << "Stari finale: ";
	for (unsigned i = 0; i < finalStates.size(); i++)
	{
		out << finalStates[i];
		if (i != finalStates.size() - 1)
		{
			out << ", ";
		}
		else
		{
			out << std::endl;
		}
	}
	out << "Functia de tranzitie:\n";
	for (auto it = transition.begin(); it != transition.end(); it++)
	{
		out << "f(" << it->first.first << ", " << it->first.second << ") = {";
		for (unsigned i = 0; i < it->second.size(); i++)
		{
			out << it->second[i];
			if (i != it->second.size() - 1)
			{
				out << ", ";
			}
			else
			{
				out << "}\n";
			}
		}
	}
}

bool FiniteAutomaton::IsState(char symbol)
{
	for (char state : states)
	{
		if (symbol == state)
		{
			return true;
		}
	}
	return false;
}

bool FiniteAutomaton::IsAlphabetSymbol(char symbol)
{
	for (char alphabetSymbol : alphabet)
	{
		if (symbol == alphabetSymbol)
		{
			return true;
		}
	}
	return false;
}

bool FiniteAutomaton::IsFinalState(char state) //functie folosita pentru checkWord
{
	for (char finalState : finalStates)
	{
		if (state == finalState)
		{
			return true;
		}
	}
	return false;
}

bool FiniteAutomaton::VerifyAutomaton()
{
	if (states.empty()) { //Q - mult finita nevida
		return false;
	}
	if (alphabet.empty()) { //Alfabet de intrare - mult finita nevida
		return false;
	}
	if (!IsState(initialState)) { //q0 apartine lui Q - stare initiala
		return false;
	}
	for (char finalState : finalStates) //F apartine lui Q - stare finala
	{
		if (!IsState(finalState))
		{
			return false;
		}
	}
	for (auto it = transition.begin(); it != transition.end(); it++)
	{
		if (!IsState(it->first.first)) //q apartine Q
		{
			return false;
		}
		if (!IsAlphabetSymbol(it->first.second)) // a apartine alfabetului de intrare
		{
			return false;
		}
		for (char outputState : it->second) // o stare p apartine lui Q
		{
			if (!IsState(outputState))
			{
				return false;
			}
		}
	}
	return true;
}

bool FiniteAutomaton::CheckWord(std::string word)
{
	std::reverse(word.begin(), word.end());
	std::vector<char> outputStates; //vector de stari rezultate
	outputStates.push_back(initialState);
	while (!word.empty()) 
	{
		char symbol = word[word.size() - 1]; //extrag primul caracter din cuvant
		word.pop_back();
		std::vector<char> currentStates; //vector de stari curente
		for (char outputState : outputStates) 
		{
			for (char state : transition[{outputState, symbol}])                                      
			{                                                 
				currentStates.push_back(state); 
			}
		}
		outputStates = currentStates;
	}
	for (char state : outputStates) //parcurgem starile rezultate si daca ajungem intr o stare finala => cuv acceptat
	{
		if (IsFinalState(state))
		{
			return true;
		}
	}
	return false;
}

bool FiniteAutomaton::IsDeterministic()
{
	for (auto it = transition.begin(); it != transition.end(); it++)
	{
		if (it->second.size() > 1)
		{
			return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& out, const FiniteAutomaton& finiteAutomaton)
{
	finiteAutomaton.PrintAutomaton(out);
	return out;
}
