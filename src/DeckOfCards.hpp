#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::random_shuffle
#include <ctime>     // For std::time
#include <cstdlib>   // For std::rand and std::srand

class Card {
public:
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, JACK, QUEEN, KING };
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

    int getDebt() const
    { 
    	int debt;
    	switch (rank)
    	{
            case ACE: debt = 1; break;
            case JACK: debt = 2; break;
            case QUEEN: debt = 3; break;
            case KING: debt = 4; break;
            default: debt = 0; break;
        }
        
        return debt;
    }
  

    std::string toString() const {
        std::string rankStr;
        switch (rank) {
            case ACE: rankStr = "Ace"; break;
            case JACK: rankStr = "Jack"; break;
            case QUEEN: rankStr = "Queen"; break;
            case KING: rankStr = "King"; break;
            default: rankStr = std::to_string(rank); break;
        }

        std::string suitStr;
        switch (suit) {
            case CLUBS: suitStr = "Clubs"; break;
            case DIAMONDS: suitStr = "Diamonds"; break;
            case HEARTS: suitStr = "Hearts"; break;
            case SPADES: suitStr = "Spades"; break;
        }

        return rankStr + " of " + suitStr;
    }

    Rank rank;
    Suit suit;
};

class DeckOfCards {
public:
    void populate40() //populate a deck with 40 cards
    {
    	// inserire check se è vuoto popula altrimenti errore
        for (int suit = Card::CLUBS; suit <= Card::SPADES; ++suit) {
            for (int rank = Card::ACE; rank <= Card::KING; ++rank) {
                cards.push_back(Card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit)));
            }
        }
        
        std::cout << "Deck populated with 40 cards" << std::endl;
    }
    
    DeckOfCards() //constructor for empty deck;
    {
        std::cout << "Empty Deck created" << std::endl;
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
        
        std::cout << "Deck splitted" << std::endl;

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
        
        std::cout << "Deck shuffled" << std::endl;
    }

    Card dealCard() {
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



