// Written by Krish Shah, U75802512, kshah26@bu.edu

#ifndef MAXPRODUCT_H
#define MAXPRODUCT_H

#include <string>

using namespace std;

class MaxProductClass {
public:
    long MaxProduct(string file);

private:
    long findMaxProduct(vector<long>& sequence);
};

#endif
