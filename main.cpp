

#include <iostream>
#include <DeckOfCards.hpp>
#include <Partita.hpp>

int main() {

	int num_partite=100;
	int max_length = 0;
	DeckOfCards deck1;
	DeckOfCards deck2;
	
	for(int i=0;i<num_partite;i++)
	{
		Partita partita;
		partita.initialize_game();
		partita.game();
		if(max_length<partita.info.num_carte_giocate)
		{
			max_length = partita.info.num_carte_giocate;
			deck1 = partita.player1.deck;
			deck2 = partita.player2.deck;
		}
	}


    	
    	std::cout << "max_length:" << max_length << "in" << num_partite << "games" << std::endl;
    	
    
	return 0;
}

