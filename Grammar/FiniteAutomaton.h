#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

class FiniteAutomaton{

private:
	std::vector<char> states; //Q
	std::vector<char> alphabet; 
	char initialState; //q0
	std::vector<char> finalStates; //F
	std::unordered_map<std::pair<char, char>, std::vector<char>, pair_hash> transition;

public:
	FiniteAutomaton() = default;
	FiniteAutomaton(std::vector<char> states, std::vector<char> alphabet, char initialState,
		std::unordered_map<std::pair<char, char>, std::vector<char>, pair_hash> transition, std::vector<char> finalStates);

	void PrintAutomaton(std::ostream& out) const;
	bool IsState(char symbol);
	bool IsAlphabetSymbol(char symbol);
	bool IsFinalState(char state);
	bool VerifyAutomaton(); 
	bool CheckWord(std::string word); 
	bool IsDeterministic();
	friend std::ostream& operator<<(std::ostream& out, const FiniteAutomaton& finiteAutomaton);
};

