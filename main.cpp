#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <vector>

void displayBinaryShort(short int value) {
    std::cout << "Binary representation: ";
    for (int i = 15; i >= 0; --i) {
        std::cout << ((value >> i) & 1);
        if (i % 4 == 0 && i != 0) std::cout << " ";
    }
    std::cout << std::endl;
}

void displayBinaryFloat(float value) {
    union {
        float f;
        unsigned int u;
    } temp;
    temp.f = value;

    std::cout << "Binary representation: ";

    // Print the sign bit (1 bit)
    std::cout << ((temp.u >> 31) & 1) << " ";

    // Print the exponent bits (8 bits)
    std::cout << "(";
    for (int i = 30; i >= 23; --i) {
        std::cout << ((temp.u >> i) & 1);
    }
    std::cout << ") ";

    // Print the mantissa bits (23 bits)
    std::cout << "(";
    for (int i = 22; i >= 0; --i) {
        std::cout << ((temp.u >> i) & 1);
        if (i % 4 == 0 && i != 0) {
            std::cout << " ";
        }
    }
    std::cout << ")" << std::endl;
}

bool getShortInt(short int & value) {
    while (true) {
        std::cout << "Please enter a short int value (from -32768 to 32767):";
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        int temp;
        if (iss >> temp) {
            if (temp >= std::numeric_limits<short int>::min() &&
                temp <= std::numeric_limits<short int>::max()) {
                value = static_cast<short int>(temp);
                return true;
            } else {
                std::cout << "Value out of range for short int. Please try again (from -32768 to 32767)." << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter a valid short int number." << std::endl;
        }
    }
}

bool getFloat(float & value) {
    while (true) {
        std::cout << "Please enter a float value:";
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        if (iss >> value) {
            return true;
        } else {
            std::cout << "Invalid input. Please enter a valid float number." << std::endl;
        }
    }
}

bool getBitPositions(int maxBits, std::vector<int>& positions) {
    while (true) {
        positions.clear();
        std::cout << "Please enter the number of bits to exclude from inversion (0 to " << maxBits << "):";
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        int numBits;
        if (iss >> numBits) {
            if (numBits >= 0 && numBits <= maxBits) {
                if (numBits == 0) return true;
                std::cout << "Enter the bit positions to exclude (separated by spaces, between 0 and " << (maxBits - 1) << "):";
                std::getline(std::cin, input);
                std::istringstream iss2(input);
                int pos;
                while (iss2 >> pos) {
                    if (pos >= 0 && pos < maxBits) {
                        positions.push_back(pos);
                    } else {
                        std::cout << "Bit position " << pos << " is out of range. Please enter positions between 0 and " << (maxBits - 1) << "." << std::endl;
                        break;
                    }
                }
                if (positions.size() != static_cast<size_t>(numBits)) {
                    std::cout << "Number of positions entered does not match the number specified. Please try again." << std::endl;
                    continue;
                }
                return true;
            } else {
                std::cout << "Invalid number of bits to exclude. Please enter a number between 0 and " << maxBits << "." << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
        }
    }
}

int main() {
    std::cout << "___ Short Int Processing ___" << std::endl;
    short int shortValue;
    if (getShortInt(shortValue)) {
        std::cout << "Original short int value: " << shortValue << std::endl;
        displayBinaryShort(shortValue);

        std::vector<int> positions;
        while (!getBitPositions(16, positions)) {
        }

        unsigned short inversionMask = 0xFFFF;
        for (size_t i = 0; i < positions.size(); ++i) {
            inversionMask &= ~(1 << positions[i]);
        }

        shortValue ^= inversionMask;
        std::cout << "Inverted short int value: " << shortValue << std::endl;
        displayBinaryShort(shortValue);
    }

    std::cout << "\n___ Float Processing ___" << std::endl;
    float floatValue;
    if (getFloat(floatValue)) {
        std::cout << "Original float value: " << floatValue << std::endl;
        displayBinaryFloat(floatValue);

        std::vector<int> positions;
        while (!getBitPositions(32, positions)) {
        }

        union {
            float f;
            unsigned int u;
        } temp;
        temp.f = floatValue;

        unsigned int inversionMask = 0xFFFFFFFF;
        for (size_t i = 0; i < positions.size(); ++i) {
            inversionMask &= ~(1U << positions[i]);
        }

        temp.u ^= inversionMask;
        std::cout << "Inverted float value: " << temp.f << std::endl;
        displayBinaryFloat(temp.f);
    }

    return 0;
}
