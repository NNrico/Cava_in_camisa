#ifndef PARTITA_HPP_
#define PARTITA_HPP_

#include <Player.hpp>
#include <DeckOfCards.hpp>

class Info{
public:
	Player* a_chi_tocca;
	Player* a_chi_non_tocca;
	
	Player* vincitore;
	Player* perdente;
	int num_carte_giocate = 0;

};

class Partita {
public:
	Player player1;
	Player player2;
	Info info;
	
	enum Rank { ASSO = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, FANTE, CAVALLO, RE };
    	enum Suit { SPADE, BASTONI, COPPE, DENARI };
	
	
	void initialize_decks()
	{
		DeckOfCards deck;
		deck.populate40();
		deck.shuffle();
		auto pair = deck.split_deck();
    		player1.deck = pair.first;
    		player2.deck = pair.second;
	}
	
	void swap_turn()
	{
		Player* temp = info.a_chi_tocca;
		info.a_chi_tocca = info.a_chi_non_tocca;
		info.a_chi_non_tocca = temp;
	}
	
	void initialize_game()
	{
		info.a_chi_tocca = &player1;
		info.a_chi_non_tocca = &player2;
		player1.name = "player1";
		player2.name = "player2";
		initialize_decks();
	}
	
	void game()
	{
	 	while (!spoglio()){}
	 	
	 	std::cout << "vincitore:" << info.vincitore->name << std::endl;
	 	std::cout << "carte giocate:" << info.num_carte_giocate << std::endl;	
	}	
	
	
	bool spoglio()
	{	//inizializzo spoglio 
		DeckOfCards mezzo; 
		bool spoglio_in_corso = true;
		bool fine_partita = false;
		bool inizio_debito = false;
		
		info.a_chi_tocca->debt=1; 
		
		while (spoglio_in_corso and !fine_partita)
		{		
			while ( info.a_chi_tocca->debt>0)
			{	
				
				auto carta_giocata = info.a_chi_tocca->deck.dealCard();
				mezzo.carta_nel_mazzo(carta_giocata);
				info.num_carte_giocate++;
				
				//std::cout << std::to_string(carta_giocata.rank) << std::endl;
				
				if(info.a_chi_tocca->deck.cardsRemaining()==0)
				{
					info.a_chi_non_tocca->deck.tiraSu(mezzo);
					fine_partita=true;
					info.vincitore = info.a_chi_non_tocca;
					info.perdente = info.a_chi_tocca;
					break;
				};
				
				//esamina carta e scegliere il dà farsi
				switch (carta_giocata.rank)
				{
            				case ASSO:
					case FANTE:
					case CAVALLO:
					case RE: 
						info.a_chi_tocca->debt=0;
						info.a_chi_non_tocca->debt=carta_giocata.getDebt();
						swap_turn();
						inizio_debito = true;
						break;
            				default:
						info.a_chi_tocca->debt--;
						if(info.a_chi_tocca->debt==0 and inizio_debito == true)
						{
							spoglio_in_corso = false;
							info.a_chi_non_tocca->deck.tiraSu(mezzo); //mezzo viene distrutto usciti da spoglio
							swap_turn();
							break;
						}
						else if(info.a_chi_tocca->debt==0 and inizio_debito == false)
						{	
							info.a_chi_non_tocca->debt=1;
							swap_turn();
							break;
						}  
        			}
			}	 
		}
		return fine_partita;
	}
	
};

#endif
