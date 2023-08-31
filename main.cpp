// Your First C++ Program

#include <iostream>
#include <DeckOfCards.hpp>

int main() {
	DeckOfCards deck;
	deck.populate40();
	deck.shuffle();

    	std::cout << "Remaining cards in the deck: " << deck.cardsRemaining() << std::endl;
    	
    	auto pair = deck.split_deck();
    	auto deck1 = pair.first;
    	auto deck2 = pair.second;
    	
    	std::cout << "Remaining cards in the deck1: " << pair.first.cardsRemaining() << std::endl;
    	std::cout << "Remaining cards in the deck2: " << pair.second.cardsRemaining() << std::endl;

    	for (int i = 0; i < 5; ++i) {
        	Card card = pair.first.dealCard();
        	std::cout << "Dealt card: " << card.toString() << std::endl;
    	}
	
    	std::cout << "Remaining cards in the deck1: " << pair.first.cardsRemaining() << std::endl;
    	
    	std::cout << "deck1: " << std::endl;
    	deck1.print_deck();
    	
    	std::cout << "deck2: " << std::endl;
    	deck2.print_deck();
    	
    	deck1.tiraSu(deck2);
    	
    	std::cout << "deck1: " << std::endl;
    	deck1.print_deck();
    
	return 0;
}

