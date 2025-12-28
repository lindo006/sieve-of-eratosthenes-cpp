// Include necessary libraries
#include <iostream>   // For input/output
#include <fstream>    // For file operations (reading/writing files)
#include <string>     // For string operations
#include <vector>     // For using vectors

// Function declarations (telling the compiler these functions exist)
int countPrimes(std::vector<bool> &primes, int n);  // Counts prime numbers
void printPrimes(std::vector<bool> &primes, int primeNo);  // Prints primes to screen
void saveToFile(std::vector<bool> &primes, int n, int primeNo);  // Saves primes to file

// Global variable to count steps (how many operations we perform)
// This is accessible from anywhere in the program
int steps = 0;

// Main function - where the program starts execution
int main() {
    // Step 1: Get input from user
    int number;  // Variable to store user's number
    std::cout << "Enter a number greater than 2 : ";
    std::cin >> number;  // Read the number from keyboard

    // Step 2: Create a vector to track prime numbers
    // Think of this as a list where index = number, value = is it prime?
    std::vector<bool> primes;
    
    // Step 3: Count how many prime numbers are below the user's number
    // This function does the actual work using Sieve of Eratosthenes
    const int numberOfPrimes = countPrimes(primes, number);
    
    // Step 4: Show the result to the user
    std::cout << "Number of prime numbers below " << number
              << ":  " << numberOfPrimes << std::endl;

    // Step 5: Print all the prime numbers found
    std::cout << "Printing prime numbers below " << number << "......." << std::endl;
    printPrimes(primes, numberOfPrimes);  // Show primes on screen

    // Step 6: Save the results to a file
    saveToFile(primes, number, numberOfPrimes);  // Save to text file

    // Step 7: Show how many steps (operations) it took
    std::cout << "Number of steps taken : " << steps << std::endl;

    return 0;  // Program ends successfully
}

// Function: countPrimes
// Purpose: Find all prime numbers below 'n' using Sieve of Eratosthenes
// Parameters:
//   primes - reference to our vector (we can modify the original)
//   n - the upper limit (find primes below this number)
int countPrimes(std::vector<bool> &primes, const int n) {
    int count = 0;  // Counter for how many primes we find
    
    // Step 1: Create initial list of numbers
    // We mark EVERY number as "probably prime" (true) to start
    for (int i = 0; i <= n; i++) {
        steps++;  // Count this operation
        primes.push_back(true);  // Add true for each number
    }
    
    // Step 2: 0 and 1 are NOT prime numbers by definition
    primes[0] = false;  // Mark 0 as not prime
    primes[1] = false;  // Mark 1 as not prime
    steps += 2;  // Count these two operations

    // Step 3: The Sieve of Eratosthenes algorithm
    // Start from 2 (the first prime number)
    for (int i = 2; i < n; i++) {
        steps++;  // Count checking each number
        
        // If current number is still marked as prime
        if (primes[i] == true) {
            // Mark all multiples of i as NOT prime
            // Example: if i=2, mark 4, 6, 8, 10... as false
            // Example: if i=3, mark 6, 9, 12, 15... as false
            // Start from i+i (first multiple) and go up by i each time
            for (int j = i + i; j < n; j += i) {
                steps++;  // Count marking each multiple
                primes[j] = false;  // Mark as not prime
            }
        }
    }

    // Step 4: Count how many prime numbers we found
    // Look through our list and count all the "true" values
    for (int i = 2; i < n; i++) {
        steps++;  // Count each check
        if (primes[i] == true) {
            count++;  // Found a prime!
        }
    }
    
    return count;  // Return the total count
}

// Function: printPrimes
// Purpose: Display prime numbers in a nice format on screen
// Parameters:
//   primes - our vector of prime flags
//   primeNo - how many primes we need to print
void printPrimes(std::vector<bool> &primes, const int primeNo) {
    int count = 0;  // Counter for which prime we're printing

    // Print opening brace for the list
    std::cout << "{";
    
    // Go through all numbers in our vector
    for (int i = 0; i < primes.size() - 1; i++) {
        // Check if current number is prime
        if (primes[i] == true) {
            // If this is the LAST prime in the list
            if (count == primeNo - 1) {
                std::cout << i << "}" << std::endl;  // Close the list
            }
            // If this is NOT the last prime
            else if (count < primeNo - 1) {
                std::cout << i << ",";  // Print with comma
            }
            count++;  // Move to next prime
        }
    }
}

// Function: saveToFile
// Purpose: Save prime numbers and statistics to a text file
// Parameters:
//   primes - our vector of prime flags
//   n - the upper limit number from user
//   primeNo - total number of primes found
void saveToFile(std::vector<bool> &primes, const int n, const int primeNo) {
    // Create filename based on user's number
    // Example: if n=100, filename = "PrimeNumberBelow100.txt"
    const std::string fileName = "PrimeNumberBelow" + std::to_string(n) + ".txt";

    // Create and open the file for writing
    std::ofstream file(fileName);

    // Check if file was created successfully
    if (!file) {
        std::cout << "Failed to create file" << std::endl;
        return;  // Exit function if we can't create file
    }

    // Write header information to file
    file << "Amount of Prime Numbers below " + std::to_string(n) + ": " + 
            std::to_string(primeNo) + "\n";
    file << "------------------------------------------------------\n";
    file << "Prime numbers below " + std::to_string(n) + "\n";
    file << "------------------------------------------------------\n";

    int count = 0;  // Counter for which prime we're writing

    // Write all prime numbers to the file
    for (int i = 0; i < primes.size() - 1; i++) {
        if (primes[i] == true) {
            // If this is the LAST prime
            if (count == primeNo - 1) {
                file << std::to_string(i) + "\n";  // Just the number with newline
            }
            // If this is NOT the last prime
            else if (count < primeNo - 1) {
                // Formatting: put 10 primes per line
                if ((count % 10 == 0) && (count > 0)) {
                    file << std::to_string(i) + "\n";  // New line after 10 primes
                }
                else {
                    file << std::to_string(i) + " , ";  // Add comma between primes
                }
            }
            count++;  // Move to next prime
        }
    }

    // Write footer with step count
    file << "------------------------------------------------------\n";
    file << "Number of steps taken to calculate prime number: " + 
            std::to_string(steps);
    
    // Close the file (good practice to free resources)
    file.close();
}