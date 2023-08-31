class Partita {
public:
	Player player1;
	Player player2;
	Info info;
	
	
	void initialize_decks()
	{
		DeckOfCards deck;
		deck.populate40();
		deck.shuffle();
		auto pair = deck.split_deck();
    		Player1.deck1 = pair.first;
    		Player2.deck2 = pair.second;
	}
	
	void swap_turn(Player* a, Player* b)
	{
		Player* temp = a;
		a = b;
		b = temp;
	}
	
	
	
	
	bool spoglio()
	{	//inizializzo spoglio 
		DeckOfCards mezzo; 
		bool spoglio_in_corso = true;
		bool fine_partita = false;
		bool inizio_debito = false;
		Info.a_chi_tocca->debt=1; 
		
		while (spoglio_in_corso and !fine_partita)
		{			
			while ( Info.a_chi_tocca->debt>0)
			{
				auto carta_giocata = Info.a_chi_tocca->dealCard();
				mezzo.carta_nel_mazzo(carta_giocata);
				Info.num_carte_giocate++;
				if(Info.a_chi_tocca->deck.cardsRemaining()==0)
				{
					fine_partita=true;
					Info.vincitore = Info.a_chi_non_tocca;
					Info.perdente = Info.a_chi_tocca;
					break;
				};
				//esamina carta e aumentare/diminuire il debito e aumentare l'altro
				switch (carta_giocata.rank)
				{
            				case ACE: 
            					Info.a_chi_tocca->debt=0;
            					Info.a_chi_non_tocca->debt=1;
            					swap_turn(Info.a_chi_tocca,Info.a_chi_non_tocca);
            					inizio_debito = true;
            					break;
            				case JACK:
            					Info.a_chi_tocca->debt=0;
            					Info.a_chi_non_tocca->debt=2;
            					swap_turn(Info.a_chi_tocca,Info.a_chi_non_tocca);
            					inizio_debito = true;
            					break;
            				case QUEEN:
            					Info.a_chi_tocca->debt=0;
            					Info.a_chi_non_tocca->debt=3;
            					swap_turn(Info.a_chi_tocca,Info.a_chi_non_tocca);
            					inizio_debito = true;
            					break;            				
            				case KING:
            					Info.a_chi_tocca->debt=0;
            					Info.a_chi_non_tocca->debt=4;
            					swap_turn(Info.a_chi_tocca,Info.a_chi_non_tocca);
            					inizio_debito = true;
            					break;
            				default:
            				       Info.a_chi_tocca->debt--;
            				       if(Info.a_chi_tocca->debt==0 and inizio_debito == true)
            				       {
            				       	spoglio_in_corso = false;
            				       	Info.a_chi_non_tocca->deck.tiraSU(mezzo); //mezzo viene distrutto usciti da spoglio
            				       	swap_turn(Info.a_chi_tocca,Info.a_chi_non_tocca);
            				       	break;
            				       }
            				       else if(Info.a_chi_tocca->debt==0 and inizio_debito == false)
            				       {	
            				       	Info.a_chi_non_tocca->debt=1;
            				       	swap_turn(Info.a_chi_tocca,Info.a_chi_non_tocca);
            				       	break;
            				       }  
        			}
			}	 
		}
		return fine_partita;
	}
	
	

}


class Info{
public:
	Player* a_chi_tocca;
	Player* a_chi_non_tocca;
	
	Player* vincitore;
	Player* perdente;
	int num_carte_giocate = 0;

}
