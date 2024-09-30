#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void displayBinaryShort(short int value) {
    cout << "Binary representation: ";
    for (int i = 15; i >= 0; --i) {
        cout << ((value >> i) & 1);
        if (i % 4 == 0 && i != 0) cout << " ";
    }
    cout << endl;
}

void displayBinaryFloat(float value) {
    union {
        float f;
        unsigned int u;
    } temp;
    temp.f = value;

    cout << "Binary representation: ";

    // Print the sign bit (1 bit)
    cout << ((temp.u >> 31) & 1) << " ";

    // Print the exponent bits (8 bits)
    cout << "(";
    for (int i = 30; i >= 23; --i) {
        cout << ((temp.u >> i) & 1);
    }
    cout << ") ";

    // Print the mantissa bits (23 bits)
    cout << "(";
    for (int i = 22; i >= 0; --i) {
        cout << ((temp.u >> i) & 1);
        if (i % 4 == 0 && i != 0) {
            cout << " ";
        }
    }
    cout << ")" << endl;
}

bool getShortInt(short int & value) {
    while (true) {
        cout << "Please enter a short int value (from -32768 to 32767):";
        string input;
        getline(cin, input);

        istringstream iss(input);
        int temp;
        if (iss >> temp) {
            if (temp >= numeric_limits<short int>::min() &&
                temp <= numeric_limits<short int>::max()) {
                value = static_cast<short int>(temp);
                return true;
            } else {
                cout << "Value out of range for short int. Please try again (from -32768 to 32767)." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a valid short int number." << endl;
        }
    }
}

bool getFloat(float & value) {
    while (true) {
        cout << "Please enter a float value:";
        string input;
        getline(cin, input);

        istringstream iss(input);
        if (iss >> value) {
            return true;
        } else {
            cout << "Invalid input. Please enter a valid float number." << endl;
        }
    }
}

bool getBitPositions(int maxBits, vector<int>& positions) {
    while (true) {
        positions.clear();
        cout << "Please enter the number of bits to exclude from inversion (0 to " << maxBits << "):";
        string input;
        getline(cin, input);
        istringstream iss(input);
        int numBits;
        if (iss >> numBits) {
            if (numBits >= 0 && numBits <= maxBits) {
                if (numBits == 0) return true;
                cout << "Enter the bit positions to exclude (separated by spaces, between 0 and " << (maxBits - 1) << "):";
                getline(cin, input);
                istringstream iss2(input);
                int pos;
                while (iss2 >> pos) {
                    if (pos < 0 || pos >= maxBits) {
                        cout << "Bit position " << pos << " is out of range. Please enter positions between 0 and " << (maxBits - 1) << "." << endl;
                        return false;
                    }
                    positions.push_back(pos);
                }
                if (positions.size() != static_cast<size_t>(numBits)) {
                    cout << "Number of positions entered does not match the number specified. Please try again." << endl;
                    continue;
                }
                return true;
            } else {
                cout << "Invalid number of bits to exclude. Please enter a number between 0 and " << maxBits << "." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a valid number." << endl;
        }
    }
}

int main() {
    cout << "___ Short Int Processing ___" << endl;
    short int shortValue;
    if (getShortInt(shortValue)) {
        cout << "Original short int value: " << shortValue << endl;
        displayBinaryShort(shortValue);

        vector<int> positions;
        while (!getBitPositions(16, positions)) {
        }

        unsigned short inversionMask = 0xFFFF;
        for (size_t i = 0; i < positions.size(); ++i) {
            inversionMask &= ~(1 << positions[i]);
        }

        shortValue ^= inversionMask;
        cout << "Inverted short int value: " << shortValue << endl;
        displayBinaryShort(shortValue);
    }

    cout << "\n___ Float Processing ___" << endl;
    float floatValue;
    if (getFloat(floatValue)) {
        cout << "Original float value: " << floatValue << endl;
        displayBinaryFloat(floatValue);

        vector<int> positions;
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
        cout << "Inverted float value: " << temp.f << endl;
        displayBinaryFloat(temp.f);
    }

    return 0;
}
