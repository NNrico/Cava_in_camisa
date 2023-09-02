

#include <iostream>
#include <DeckOfCards.hpp>
#include <Partita.hpp>
#include <ctime>     // For std::time
#include <cstdlib>   // For std::rand and std::srand
#include <fstream>

int main() {

	int num_partite=100000000;
	int max_length = 0;
	DeckOfCards deck1;
	DeckOfCards deck2;
	std::string vincitore;
	
	// Seed the random number generator
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	
	for(int i=0;i<num_partite;i++)
	{
		Partita partita;
		partita.initialize_game();
		deck1 = partita.player1.deck;
		deck2 = partita.player2.deck;
		partita.game();
		if(max_length<partita.info.num_carte_giocate)
		{
			max_length = partita.info.num_carte_giocate;
			vincitore = partita.info.vincitore->name;
		}
	}


    	
    	std::cout << "max_length: " << max_length << "in " << num_partite << "games" << std::endl;
    	
    	std::ifstream inputFile("results.txt");  
    	if (!inputFile.is_open())
    	{
        std::cerr << "Error: Unable to open the file for reading." << std::endl;
        return 1;  // Exit with an error code.
    	}
    
    
    	std::string valueStr = "0";
    
    
    	    std::string line;
	    while (std::getline(inputFile, line))
	    {
		// Check if the line contains "lunghezza"
		if (line.find("lunghezza:") != std::string::npos) {
		    // If "lunghezza:" is found, extract the value.
		    // Assuming the value is on the same line and follows the ":" character.
		    size_t colonPos = line.find(":");
		    if (colonPos != std::string::npos) {
		        valueStr = line.substr(colonPos + 1);
		        std::cout << "Value of lunghezza: " << valueStr << std::endl;
		        break;  // Exit the loop after finding the value.
		    }
		}
	    }
    	
    	 inputFile.close();
    	 
    	int value = std::stoi(valueStr);
    	 if (value>max_length) return 0;
    	 
    	// Open a text file for writing
    	std::ofstream outFile("results.txt");

    	// Check if the file is open
    	if (!outFile.is_open())
    	{
        	std::cerr << "Failed to open the file for writing." << std::endl;
        	return 1; // Return an error code
        }
        
        // Write the integers to the file
    	outFile << "lunghezza: " << max_length << std::endl;
    	outFile << "vincitore: " << vincitore << std::endl;
    	outFile.close();
    	
    	    	// Open a text file for writing
    	std::ofstream outFile2("deck1.txt");

    	// Check if the file is open
    	if (!outFile2.is_open())
    	{
        	std::cerr << "Failed to open the file for writing." << std::endl;
        	return 1; // Return an error code
        }
        
        outFile2 << "deck1: "<< std::endl;
    	for (const Card& card : deck1.getCards())
    	{
        outFile2 << card.toString() << std::endl;
        }
        outFile2.close();
    	
    	    	// Open a text file for writing
    	std::ofstream outFile3("deck2.txt");

    	// Check if the file is open
    	if (!outFile3.is_open())
    	{
        	std::cerr << "Failed to open the file for writing." << std::endl;
        	return 1; // Return an error code
        }
    	
        
    	outFile3 << "deck2: "<< std::endl;
    	for (const Card& card : deck2.getCards())
    	{
        outFile3 << card.toString() << std::endl;
        }
        

    	// Close the file
    	outFile3.close();

    	
    
	return 0;
}




