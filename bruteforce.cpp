
#include <algorithm>
#include <iostream>
#include <DeckOfCards.hpp>
#include <Partita.hpp>
#include <ctime>     // For std::time
#include <cstdlib>   // For std::rand and std::srand
#include <fstream>

std::pair<std::vector<int>, std::vector<int>> splitVector(const std::vector<int>& inputVector) {
    std::vector<int> firstFive;
    std::vector<int> nextFive;

    // Check if the input vector has at least 10 elements
    if (inputVector.size() >= 40) {
        // Copy the first five elements to 'firstFive'
        firstFive.assign(inputVector.begin(), inputVector.begin() + 20);
        // Copy elements 6 to 10 to 'nextFive'
        nextFive.assign(inputVector.begin() + 20, inputVector.begin() + 40);
    } else {
        // If the input vector doesn't have enough elements, copy what's available
        firstFive = inputVector;
    }

    // Return the two subvectors
    return std::make_pair(firstFive, nextFive);
}

int main() {

	int num_partite=100000000;
	int max_length = 0;
	DeckOfCards deck1;
	DeckOfCards deck2;
	std::string vincitore;
	
	std::vector<int> best_vec;
    std::vector<int> vec = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,8,8,8,8,9,9,9,9,10,10,10,10};
    //sort(vec.begin(), vec.end()); 
	
	for(int i=0;i<num_partite;i++)
	{    
        std::pair<std::vector<int>, std::vector<int>> pair = splitVector(vec);

        deck1.convertVectorToDeck(pair.first);
        deck2.convertVectorToDeck(pair.second);

		//deck1.print_deck();
		//deck2.print_deck();

		Partita partita;
		partita.initialize_game(deck1,deck2);
		partita.game();
		if(max_length<partita.info.num_carte_giocate)
		{
			max_length = partita.info.num_carte_giocate;
			vincitore = partita.info.vincitore->name;
			best_vec=vec;
		
		}

        next_permutation(vec.begin(), vec.end());  
	}

		
		std::cout << "current unchecked vector:" << std::endl;
		;
		for (auto e : vec) {

		    std::cout << e << std::endl;
        }
        std::cout << "\n" << std::endl;
    	
		std::cout << "current best vector:" << std::endl;
		for (auto e : best_vec) {

		    std::cout << e << std::endl;
        }
        std::cout << "\n" << std::endl;
    	

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



