#include <iostream>
#include <fstream>
#include <vector>
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
using namespace std;


// C++ Program to implement
// the above approach
 


 
// Function to fill the vector curr
// while maintaining the indices visited
// in the array num
void backtrack(vector<int>& nums,
               vector<int>& curr,
               vector<vector<int> >& ans,
               vector<bool>& visited)
{
 
    // If current permutation is complete
    if ((int)curr.size() == (int)nums.size()) {
        ans.push_back(curr);
    }
 
    // Traverse the input vector
    for (int i = 0; i < (int)nums.size();
         i++) {
 
        // If index is already visited
        if (visited[i])
            continue;
 
        // If the number is duplicate
        if (i > 0 and nums[i] == nums[i - 1]
            and !visited[i - 1])
            continue;
 
        // Set visited[i] flag as true
        visited[i] = true;
 
        // Push nums[i] to current vector
        curr.push_back(nums[i]);
 
        // Recursive function call
        backtrack(nums, curr,
                  ans, visited);
 
        // Backtrack to the previous
        // state by unsetting visited[i]
        visited[i] = false;
 
        // Pop nums[i] and place at
        // the back of the vector
        curr.pop_back();
    }
}
 
// Function to pre-process the vector num
vector<vector<int> > permuteDuplicates(
    vector<int>& nums)
{
    // Sort the array
    sort(nums.begin(), nums.end());
 
    // Stores distinct permutations
    vector<vector<int> > ans;
 
    vector<bool> visited(
        (int)nums.size(), false);
 
    // Store the current permutation
    vector<int> curr;
 
    // Find the distinct permutations of num
    backtrack(nums, curr, ans, visited);
 
    return ans;
}
 
// Function call to print all distinct
// permutations of the vector nums
vector<vector<int> > getDistinctPermutations(vector<int> nums)
{
    // Find the distinct permutations
    vector<vector<int> > ans
        = permuteDuplicates(nums);
        
        
 
    // Traverse every row
    for (int i = 0; i < (int)ans.size();
         i++) {
 
        // Traverse every column
        for (int j = 0; j < (int)ans[i].size();
             j++) {
 
            cout << ans[i][j] << " ";
        }
 
        cout << '\n';
    }
    
    std::cout << ans.size() << std::endl;
    
    return ans;
}
 



int main() {



    // Input
    //vector<int> nums = {5,5,5, 5, 5, 5,1,8,9,10 };
 
    // Function call to print
    // all distinct permutations
    //auto ans = getDistinctPermutations(nums);


    // Create a sample vector of vectors of integers
    //std::vector<std::vector<int>> data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // Write the data to a file
    //WriteVectorVectorToFile(ans, "data.txt");

    // Read the data from the file
    std::vector<std::vector<int>> readData = ReadVectorVectorFromFile("seq.txt");

    // Display the read data
    std::cout << "Read Data:" << std::endl;
    for (const auto& innerVector : readData) {
        for (int value : innerVector) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

