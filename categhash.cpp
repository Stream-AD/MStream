#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#include <cstdlib>
#include "categhash.hpp"
#include <limits>

using namespace std;

Categhash::Categhash(int r, int b) {
    num_rows = r;
    num_buckets = b;
    hash_a.resize(num_rows);
    hash_b.resize(num_rows);
    for (int i = 0; i < num_rows; i++) {
        // a is in [1, p-1]; b is in [0, p-1]
        hash_a[i] = rand() % (num_buckets - 1) + 1;
        hash_b[i] = rand() % num_buckets;
    }
    this->clear();
}

int Categhash::hash(int a, int i) {
    int resid = (a * hash_a[i] + hash_b[i]) % num_buckets;
    return resid + (resid < 0 ? num_buckets : 0);
}

void Categhash::insert(int cur_int, double weight) {
    int bucket;
    for (int i = 0; i < num_rows; i++) {
        bucket = hash(cur_int, i);
        count[i][bucket] += weight;

    }
}

double Categhash::get_count(int cur_int) {
    double min_count = numeric_limits<double>::max();
    int bucket;
    for (int i = 0; i < num_rows; i++) {
        bucket = hash(cur_int, i);
        min_count = MIN(min_count, count[i][bucket]);
    }
    return min_count;
}

void Categhash::clear() {
    count = vector<vector<double> >(num_rows, vector<double>(num_buckets, 0.0));
}

void Categhash::lower(double factor) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_buckets; j++) {
            count[i][j] = count[i][j] * factor;
        }
    }
}