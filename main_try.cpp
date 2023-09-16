#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <DeckOfCards.hpp>
#include <Partita.hpp>
#include <bits/stdc++.h>


// Function to write a vector of vectors of integers to a file
void WriteVectorVectorToFile(const std::vector<std::vector<int>>& data, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    size_t numOuterVectors = data.size();
    file.write(reinterpret_cast<const char*>(&numOuterVectors), sizeof(numOuterVectors));

    for (const std::vector<int>& innerVector : data) {
        size_t numInnerElements = innerVector.size();
        file.write(reinterpret_cast<const char*>(&numInnerElements), sizeof(numInnerElements));
        file.write(reinterpret_cast<const char*>(innerVector.data()), numInnerElements * sizeof(int));
    }

    file.close();
    std::cout << "Data written to file: " << filename << std::endl;
}

// Function to read a vector of vectors of integers from a file
std::vector<std::vector<int>> ReadVectorVectorFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return {};
    }

    size_t numOuterVectors;
    file.read(reinterpret_cast<char*>(&numOuterVectors), sizeof(numOuterVectors));

    std::vector<std::vector<int>> result;
    result.reserve(numOuterVectors);

    for (size_t i = 0; i < numOuterVectors; ++i) {
        size_t numInnerElements;
        file.read(reinterpret_cast<char*>(&numInnerElements), sizeof(numInnerElements));

        std::vector<int> innerVector(numInnerElements);
        file.read(reinterpret_cast<char*>(innerVector.data()), numInnerElements * sizeof(int));

        result.push_back(innerVector);
    }

    file.close();
    return result;
}

std::pair<std::vector<int>, std::vector<int>> splitVector(const std::vector<int>& inputVector) {
    std::vector<int> firstFive;
    std::vector<int> nextFive;

    // Check if the input vector has at least 10 elements
    if (inputVector.size() >= 10) {
        // Copy the first five elements to 'firstFive'
        firstFive.assign(inputVector.begin(), inputVector.begin() + 5);
        // Copy elements 6 to 10 to 'nextFive'
        nextFive.assign(inputVector.begin() + 5, inputVector.begin() + 10);
    } else {
        // If the input vector doesn't have enough elements, copy what's available
        firstFive = inputVector;
    }

    // Return the two subvectors
    return std::make_pair(firstFive, nextFive);
}


int main() {

    // Read the data from the file
    std::vector<std::vector<int>> readData = ReadVectorVectorFromFile("seq.txt");
    //std::vector<std::vector<int>> outvec1;
    //std::vector<std::vector<int>> outvec2;
    int max_length = 0;
    
    
	DeckOfCards deck;
    DeckOfCards deck1;
    DeckOfCards deck2;
    
    unsigned e;
    unsigned f;
    unsigned g;
    unsigned h;
    
    //std::cout << readData.size() << std::endl;

    for(unsigned a=63;a<readData.size();a++){
    for(unsigned b=34;b<readData.size();b++)
    for(unsigned c=86;c<readData.size();c++)
    for(unsigned d=63;d<readData.size();d++){
    
    for(e=0;e<2;e++)
    for(f=0;f<2;f++)
    for(g=0;g<2;g++)
    for(h=0;h<2;h++){
    
    

    auto veca = readData[a];
    auto vecb = readData[b];
    auto vecc = readData[c];
    auto vecd = readData[d];
    
    std::pair<std::vector<int>, std::vector<int>> paira = splitVector(veca);
    std::pair<std::vector<int>, std::vector<int>> pairb = splitVector(vecb);
    std::pair<std::vector<int>, std::vector<int>> pairc = splitVector(vecc);
    std::pair<std::vector<int>, std::vector<int>> paird = splitVector(vecd);
    
    if(e<1)
    {
	deck1.convertVectorToDeck(paira.first);
  	deck2.convertVectorToDeck(paira.second);
    }
    else
    {
    	deck1.convertVectorToDeck(paira.second);
  	deck2.convertVectorToDeck(paira.first);
    }
    
        if(f<1)
    {
    deck1.AddVectorToDeck(pairb.first);
    deck2.AddVectorToDeck(pairb.second);
    }
    else
    {
    	deck1.AddVectorToDeck(pairb.second);
  	deck2.AddVectorToDeck(pairb.first);
    }
    
        if(g<1)
    {
	deck1.AddVectorToDeck(pairc.first);
  	deck2.AddVectorToDeck(pairc.second);
    }
    else
    {
    	deck1.AddVectorToDeck(pairc.second);
  	deck2.AddVectorToDeck(pairc.first);
    }
    
        if(h<1)
    {
	deck1.AddVectorToDeck(paird.first);
  	deck2.AddVectorToDeck(paird.second);
    }
    else
    {
    	deck1.AddVectorToDeck(paird.second);
  	deck2.AddVectorToDeck(paird.first);
    }


    deck1.print_deck();
    deck2.print_deck();
    
    Partita partita;
    partita.initialize_game(deck1,deck2);
    partita.game();

    deck1=partita.player1.deck;
    deck2=partita.player2.deck;

    //deck1.print_deck();
    //std::cout << "here" << std::endl;
    //deck2.print_deck();
    
    
    //std::cout << "Debito Perdente" << partita.info.a_chi_tocca->debt << std::endl;
    //std::cout << "carte giocate" << partita.info.num_carte_giocate << std::endl;
    
    if( partita.info.num_carte_giocate>10000 ){
    	std::cout << a << " " << b<< " " << c<< " " << d  << " "<< e <<" " << f <<" " << g <<" " << h<< std::endl;
    }
    //else
    //std::cout << "Sequenza non equilibrata" << std::endl;
    
    if(max_length<partita.info.num_carte_giocate)
		{
			max_length = partita.info.num_carte_giocate;
			std::cout << max_length  << std::endl;
		}

    }
    
    }

    //std::cout << "seq trovate: " << outvec.size() << std::endl;
    
    std::cout << a << std::endl;
    }

    //WriteVectorVectorToFile(outvec, "seq.txt");

    return 0;
}
