// Written by Krish Shah, U75802512, kshah26@bu.edu

#include "MaxProduct.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

using namespace std;

long MaxProductClass::MaxProduct(string file) {
    ifstream input(file);
    if (!input.is_open()) {
        cerr << "Error: Unable to open input file." << endl;
        return -1;
    }

    long maxResult = INT_MIN;  

    string line;
    while (getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        vector<long> sequence;
        long num;
        istringstream iss(line);

        while (iss >> num && num != -999999) {
            sequence.push_back(num);
        }

        long maxSubsequenceProduct = findMaxProduct(sequence);
        cout << maxSubsequenceProduct << endl;

        if (maxSubsequenceProduct > maxResult) {
            maxResult = maxSubsequenceProduct;
        }
    }

    input.close();
    return maxResult;
}

long MaxProductClass::findMaxProduct(vector<long>& sequence) {
    int n = sequence.size();
    if (n == 0) {
        return 0;  
    }

    long maxProduct = sequence[0];

    for (int i = 0; i < n; i++) {
        long currentProduct = sequence[i];
        for (int j = i + 1; j < n && j - i < 3; j++) {
            currentProduct *= sequence[j];
            maxProduct = max(maxProduct, currentProduct);
        }
    }

    return maxProduct;
}
