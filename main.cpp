// Your First C++ Program

#include <iostream>
#include <DeckOfCards.hpp>

int main() {
	DeckOfCards deck;
	deck.populate40();
	deck.shuffle();

    	std::cout << "Remaining cards in the deck: " << deck.cardsRemaining() << std::endl;
    	
    	auto pair = deck.split_deck();
    	
    	std::cout << "Remaining cards in the deck1: " << pair.first.cardsRemaining() << std::endl;
    	std::cout << "Remaining cards in the deck2: " << pair.second.cardsRemaining() << std::endl;

    	for (int i = 0; i < 5; ++i) {
        	Card card = pair.first.dealCard();
        	std::cout << "Dealt card: " << card.toString() << std::endl;
    	}
	
    	std::cout << "Remaining cards in the deck1: " << pair.first.cardsRemaining() << std::endl;
    
	return 0;
}

