What is Cava in camisa?
It is a regional card game with uses a deck of 40 cards. For the rules and details see https://it.wikipedia.org/wiki/Straccia_camicia.

Re: 4 carte
Cavallo: 3 carte
Fante: 2 carte
Asso: 1 carta

Chi prende il mazzo risponde per primo! 


main_check.cpp carica deckprova1.txt e deckprova2.txt e gioca una partita con quelli

main_check10.cpp carica il file data.txt che contiene tutti i possibili deck di 10 carte e trova le sequanze di 10 carte che divise in 2 deck portano ad avere una partita senza resto e li salva il seq.txt


main.cpp gioca 100000 partite e salva quella con lunghezza più lunga in deck1.txt e deck2.txt

deck1_10 e deck2_10 sono deck di dieci carte usati per testare il codice.

I have tested all the possible decks made by 10-10-10-10 (concatenation of 4 decks of size ten) where each of the 10 deck card if played terminates a match without debt for the losing player. Each 10 card deck has been tried by both the first player and the second player starting as first. None of them gives an infinite sequence. The goal was to see if there was an infinite sequence with cycle of 10 cards per rounds or at least starting with 4 rounds of 10 cards each. 
