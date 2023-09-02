#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <DeckOfCards.hpp>
#include <Partita.hpp>


int main() {
    DeckOfCards deck1;
    DeckOfCards deck2;
    
    deck1.loadFromFile("deck1.txt");
    deck2.loadFromFile("deck2.txt"); // Load deck1 and deck2 from the file
    
    Partita partita;
    partita.initialize_game(deck1,deck2);
    partita.game();
    
    std::cout << "carte giocate: " << partita.info.num_carte_giocate << std::endl;

    return 0;
}
