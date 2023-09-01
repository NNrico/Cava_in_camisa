#ifndef DECK_OF_CARDS_HPP_
#define DECK_OF_CARDS_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::random_shuffle
#include <ctime>     // For std::time
#include <cstdlib>   // For std::rand and std::srand

class Card {
public:
    enum Rank { ASSO = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, FANTE, CAVALLO, RE };
    enum Suit { SPADE, BASTONI, COPPE, DENARI };

    Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

    int getDebt() const
    { 
    	int debt;
    	switch (rank)
    	{
            case ASSO: debt = 1; break;
            case FANTE: debt = 2; break;
            case CAVALLO: debt = 3; break;
            case RE: debt = 4; break;
            default: debt = 0; break;
        }
        
        return debt;
    }
  

    std::string toString() const {
        std::string rankStr;
        switch (rank) {
            case ASSO: rankStr = "ASSO"; break;
            case FANTE: rankStr = "FANTE"; break;
            case CAVALLO: rankStr = "CAVALLO"; break;
            case RE: rankStr = "RE"; break;
            default: rankStr = std::to_string(rank); break;
        }

        std::string suitStr;
        switch (suit) {
            case SPADE: suitStr = "SPADE"; break;
            case BASTONI: suitStr = "BASTONI"; break;
            case COPPE: suitStr = "COPPE"; break;
            case DENARI: suitStr = "DENARI"; break;
        }

        return rankStr + " di " + suitStr;
    }

    Rank rank;
    Suit suit;
};

class DeckOfCards {
public:
    void populate40() //populate a deck with 40 cards
    {
    	// inserire check se è vuoto popula altrimenti errore
        for (int suit = Card::SPADE; suit <= Card::DENARI; ++suit) {
            for (int rank = Card::ASSO; rank <= Card::RE; ++rank) {
                cards.push_back(Card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit)));
            }
        }
        
        //std::cout << "Deck populated with 40 cards" << std::endl;
    }
    
    DeckOfCards() //constructor for empty deck;
    {
        //std::cout << "Empty Deck created" << std::endl;
    }
    
    std::pair<DeckOfCards, DeckOfCards> split_deck() {
        if (cards.size() % 2 != 0) {
            throw std::runtime_error("Deck size must be even to split it into two equal decks.");
        }

        size_t halfSize = cards.size() / 2;

        std::vector<Card> firstHalf(cards.begin(), cards.begin() + halfSize);
        std::vector<Card> secondHalf(cards.begin() + halfSize, cards.end());

        DeckOfCards firstDeck;
        firstDeck.cards = firstHalf;

        DeckOfCards secondDeck;
        secondDeck.cards = secondHalf;
        
        //std::cout << "Deck splitted" << std::endl;

        return std::make_pair(firstDeck, secondDeck);
    }
    
    void tiraSu(const DeckOfCards& otherDeck) 
    {
        cards.insert(cards.begin(), otherDeck.cards.rbegin(), otherDeck.cards.rend());
        //otherDeck.clear();
    }
    
    void carta_nel_mazzo(const Card& card) 
    {
        cards.push_back(card);
    }

    void shuffle()
    {
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Use Fisher-Yates shuffle algorithm
        for (size_t i = cards.size() - 1; i > 0; --i)
        {
            size_t j = std::rand() % (i + 1); // Generate a random index between 0 and i
            std::swap(cards[i], cards[j]);   // Swap the elements at indices i and j
        }
        
        //std::cout << "Deck shuffled" << std::endl;
    }

    Card dealCard()
    {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

    size_t cardsRemaining() const {
        return cards.size();
    }
    
    void print_deck() const 
    {
        for (const Card& card : cards) {
            std::cout << card.toString() << std::endl;
        }
    }

private:
    std::vector<Card> cards;
};

#endif

