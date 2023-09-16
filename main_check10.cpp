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
    std::vector<std::vector<int>> readData = ReadVectorVectorFromFile("data.txt");
    std::vector<std::vector<int>> outvec;
    
    
	DeckOfCards deck;
    DeckOfCards deck1;
    DeckOfCards deck2;

    for(int i=0;i<readData.size();i++){

    auto vec = readData[i];
    std::pair<std::vector<int>, std::vector<int>> pair = splitVector(vec);


    deck1.convertVectorToDeck(pair.first);
    deck2.convertVectorToDeck(pair.second);

    deck1.print_deck();
    deck2.print_deck();
    
    Partita partita;
    partita.initialize_game(deck1,deck2);
    partita.spoglio();

    deck1=partita.player1.deck;
    deck2=partita.player2.deck;

    deck1.print_deck();
    std::cout << "here" << std::endl;
    deck2.print_deck();
    
    
    std::cout << "Debito Perdente" << partita.info.a_chi_tocca->debt << std::endl;
     std::cout << "carte giocate" << partita.info.num_carte_giocate << std::endl;
    
    if( (partita.info.a_chi_tocca->debt==0) and partita.info.num_carte_giocate==10 ){
    	std::cout << "Sequenza di 10 carte equilibrata" << std::endl;
        outvec.push_back(vec);
    }
    else
    std::cout << "Sequenza non equilibrata" << std::endl;

    }

    std::cout << "seq trovate: " << outvec.size() << std::endl;

    WriteVectorVectorToFile(outvec, "seq.txt");

    return 0;
}
