#ifndef numerichash_hpp
#define numerichash_hpp

#include <cstdio>
#include <vector>

class Numerichash {
public:
    Numerichash(int r, int b);

    void insert(double cur_node, double weight);

    double get_count(double cur_node);

    void clear();

    void lower(double factor);

private:
    int num_rows;
    int num_buckets;
    std::vector<std::vector<double> > count;

    int hash(double cur_node);
};

#endif /* numerichash_hpp */
