#ifndef DECK_OF_CARDS_HPP_
#define DECK_OF_CARDS_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <ctime>     // For std::time
#include <cstdlib>   // For std::rand and std::srand
#include <fstream>  // This is for ifstream


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
    
     // A static method to create a Card object from a string
    static Card fromString(const std::string& cardStr) {
        // Initialize default values
        Rank rank = ASSO;
        Suit suit = SPADE;

        // Define mappings for rank and suit strings
        std::vector<std::string> rankStrings = { "ASSO", "2", "3", "4", "5", "6", "7", "FANTE", "CAVALLO", "RE" };
        std::vector<std::string> suitStrings = {  "SPADE",  "BASTONI","COPPE", "DENARI"};

        // Parse the card string
        for (size_t i = 0; i < rankStrings.size(); ++i) {
            if (cardStr.find(rankStrings[i]) != std::string::npos) {
                rank = static_cast<Rank>(i + 1); // Rank values start from 1
                break;
            }
        }

        for (size_t i = 0; i < suitStrings.size(); ++i) {
            if (cardStr.find(suitStrings[i]) != std::string::npos) {
                suit = static_cast<Suit>(i);
                break;
            }
        }

        return Card(rank, suit);
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
        std::cout << "\n" << std::endl;
    }
    
    const std::vector<Card>& getCards() const
    {
        return cards;
    }
    
     // A method to load cards from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream inputFile(filename);

        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open the file for reading." << std::endl;
            return;
        }

        cards.clear(); // Clear the current deck

        std::string line;
        while (std::getline(inputFile, line)) {
            if (line.find("deck1:") != std::string::npos) {
            
                // Start reading cards for deck1
                while (std::getline(inputFile, line)) {
                    if (line.find("deck2:") != std::string::npos) {
                        // Found the start of deck2, exit the loop
                        break;
                    }
                    // Parse and add cards for deck1
                    cards.push_back(Card::fromString(line));
                }
            } else if (line.find("deck2:") != std::string::npos) {
                // Start reading cards for deck2
                while (std::getline(inputFile, line)) {
                    // Parse and add cards for deck2
                    cards.push_back(Card::fromString(line));
                }
            }
        }

        inputFile.close();
    }

private:
    std::vector<Card> cards;
};

#endif

