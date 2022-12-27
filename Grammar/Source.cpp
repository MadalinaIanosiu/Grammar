#include"Grammar.h"
#include"FiniteAutomaton.h"
#include<fstream>

int main()
{
	std::ifstream fin("input.txt");
	Grammar grammar;
	fin >> grammar;

	FiniteAutomaton automaton;

	std::cout << "\n";
	std::cout << "						GRAMATICA - AUTOMAT\n";
	std::cout << "\n";
	std::cout << "	Pentru afisarea gramaticii apasati 1\n";
	std::cout << "	Pentru generarea unui cuvant random apasati 2\n";
	std::cout << "	Pentru a obtine automatul echivalent cu gramatica apasati 3\n";
	std::cout << "	Pentru a verifica daca cuvantul dat este acceptat sau nu de automat apasati 4\n";
	std::cout << "	Pentru generarea unui cuvant randomn in G si verificarea daca este acceptat apasati 5\n";
	std::cout << "\n";
	std::cout << " Introduceti o tasta:\n";
	int n;
	std::cin >> n;
	if (grammar.VerifyGrammar() && grammar.IsRegular()) {
		while (n != 6) {
			switch (n)
			{
			case 1:
				std::cout << grammar;
				std::cout << std::endl;
				break;

			case 2:
					grammar.GenerateWord();
				std::cout << std::endl << std::endl;
				break;

			case 3:
				automaton = grammar.TransformareGramaticaAutomat();
				std::cout << automaton;
				std::cout << std::endl << std::endl;
				break;

			case 4: {
				std::string word;
				std::cout << "Introduceti cuvantul: ";
				std::cin >> word;
				if (automaton.CheckWord(word))
					std::cout << "Acceptat\n";
				else
					std::cout << "Nu este acceptat\n";
				std::cout << std::endl;
				break;
			}
			case 5: {
				std::string randomWord = grammar.GenerateWord();
				std::cout << std::endl;
				if (automaton.CheckWord(randomWord))
					std::cout << "Cuvant nu este acceptat\n";
				else
				    std::cout << "Cuvant acceptat\n";
				std::cout << std::endl;
				break;
			}
			default:
				std::cout << "Alegere invalida";
				break;
			}
			std::cout << "Introduceti o tasta:\n";
			std::cin >> n;
		}
	}

	return 0;
}