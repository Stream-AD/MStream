#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#include "numerichash.hpp"
#include <cmath>
#include <limits>

using namespace std;

Numerichash::Numerichash(int r, int b) {
    num_rows = r;
    num_buckets = b;
    this->clear();
}


int Numerichash::hash(double cur_node, int i) {
    int bucket;
    cur_node = cur_node * (num_buckets - 1);
    bucket = floor(cur_node);
    return bucket;
}

void Numerichash::insert(double cur_node, double weight) {
    int bucket;
    bucket = hash(cur_node, 0);
    count[0][bucket] += weight;
}

double Numerichash::get_count(double cur_node) {
    int bucket;
    bucket = hash(cur_node, 0);
    return count[0][bucket];
}

void Numerichash::clear() {
    count = vector<vector<double> >(num_rows, vector<double>(num_buckets, 0.0));
}


void Numerichash::lower(double factor) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_buckets; j++) {
            count[i][j] = count[i][j] * factor;
        }
    }
}