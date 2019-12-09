#ifndef categhash_hpp
#define categhash_hpp

#include <cstdio>
#include <vector>

class Categhash {
public:
    Categhash(int r, int b);
    void insert(int cur_int, double weight);
    double get_count(int cur_int);
    void clear();
    void lower(double factor);

private:
    int num_rows;
    int num_buckets;
    std::vector<int> hash_a, hash_b;
    std::vector<std::vector<double> > count;

    int hash(int cur_int, int i);
};

#endif /* categhash_hpp */
