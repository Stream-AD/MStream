#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#include <cstdlib>
#include "recordhash.hpp"
#include <limits>
#include <bitset>
#include "lshhash.h"
#include <cmath>

using namespace std;

Recordhash::Recordhash(int r, int b, int dim1, int dim2)
{
    num_rows = r;
    num_buckets = b;
    dimension1 = dim1;
    dimension2 = dim2;
    MTRand mtr;

    num_recordhash.resize(num_rows);
    for (int i = 0; i < num_rows; i++) {
        int log_bucket = ceil(log2(num_buckets));
        num_recordhash[i].resize(log_bucket);
        for (int j = 0; j < log_bucket; j++) {
            num_recordhash[i][j].resize(dimension1);
            for (int k = 0; k < dimension1; k++) {
                num_recordhash[i][j][k] = mtr.randNorm();
            }
        }
    }

    cat_recordhash.resize(num_rows);
    for (int i = 0; i < num_rows; i++) {
        cat_recordhash[i].resize(dimension2);
        for (int k = 0; k < dimension2 - 1; k++) {
            cat_recordhash[i][k] = (rand() % (num_buckets - 1) + 1);
        }
        cat_recordhash[i][dimension2 - 1] = (rand() % num_buckets);
    }

    this->clear();
}

int Recordhash::numerichash(const vector<double>& cur_numeric, int i)
{

    double sum = 0.0;
    int bitcounter = 0;
    bitset<10> b;

    for (int iter = 0; iter < 10; iter++) {
        sum = 0;
        for (int k = 0; k < dimension1; k++) {
            sum = sum + num_recordhash[i][iter][k] * cur_numeric[k];
        }

        if (sum < 0)
            b.set(bitcounter, 0);
        else
            b.set(bitcounter, 1);
        bitcounter++;
    }

    return b.to_ulong();
}

int Recordhash::categhash(vector<int> cur_categ, int i)
{

    int counter = 0;
    int resid = 0;

    for (int k = 0; k < dimension2; k++) {
        resid = (resid + cat_recordhash[i][counter] * cur_categ[counter]) % num_buckets;
        counter++;
    }
    return resid + (resid < 0 ? num_buckets : 0);
}

void Recordhash::insert(vector<double> cur_numeric, vector<int> cur_categ, double weight)
{

    vector<double> v(cur_numeric.size() + cur_categ.size());
    move(cur_numeric.begin(), cur_numeric.end(), v.begin());
    move(cur_categ.begin(), cur_categ.end(), v.begin() + cur_numeric.size());
    int bucket1, bucket2, bucket;

    for (int i = 0; i < num_rows; i++) {
        bucket1 = numerichash(cur_numeric, i);
        bucket2 = categhash(cur_categ, i);
        bucket = (bucket1 + bucket2) % num_buckets;
        count[i][bucket] += weight;
    }
}

double Recordhash::get_count(vector<double> cur_numeric, vector<int> cur_categ)
{

    vector<double> v(cur_numeric.size() + cur_categ.size());
    m