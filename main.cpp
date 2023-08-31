// Your First C++ Program

#include <iostream>
#include <DeckOfCards.hpp>
#include <Partita.hpp>

int main() {

	Partita partita;
	partita.initialize_game();
	
	std::cout << "deck1: " << std::endl;
    partita.player1.deck.print_deck();
    std::cout << "\n" << std::endl;

	std::cout << "deck2: " << std::endl;
    partita.player2.deck.print_deck();
    std::cout << "\n" << std::endl;

	std::cout << "here" << std::endl;
    	
    partita.spoglio();
    	
    std::cout << "deck1: " << std::endl;
    partita.player1.deck.print_deck();
    std::cout << "\n" << std::endl;

	std::cout << "deck2: " << std::endl;
    partita.player2.deck.print_deck();
    std::cout << "\n" << std::endl;
    
	return 0;
}

