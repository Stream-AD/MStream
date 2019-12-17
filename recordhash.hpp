#ifndef recordhash_hpp
#define recordhash_hpp

#include <cstdio>
#include <vector>

class Recordhash {
public:
    Recordhash(int r, int b, int dim1, int dim2);

    void insert(std::vector<double> &cur_numeric, std::vector<long> &cur_categ, double weight);

    double get_count(std::vector<double> &cur_numeric, std::vector<long> &cur_categ);

    void clear();

    void lower(double factor);

private:
    int num_rows;
    int num_buckets;
    int dimension1;
    int dimension2;
    std::vector<std::vector<std::vector<double> > > num_recordhash;
    std::vector<std::vector<int> > cat_recordhash;
    std::vector<std::vector<double> > count;

    int numerichash(const std::vector<double>& cur_numeric, int i);

    int categhash(std::vector<long> &cur_categ, int i);
};

#endif /* recordhash_hpp */
