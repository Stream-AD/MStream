#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "anom.hpp"
#include "argparse.hpp"

using namespace std;

void load_data(vector<vector<double> > &numeric, vector<vector<int> > &categorical, vector<int> &times,
               const string &numeric_filename, const string &categ_filename, const string &time_filename) {
    int l = 0;
    string s, line;
    if (!numeric_filename.empty()) {
        ifstream numericFile(numeric_filename);
        while (numericFile) {
            l++;
            if (!getline(numericFile, s))
                break;
            if (s[0] != '#') {
                istringstream ss(s);
                vector<double> record;
                while (ss) {

                    if (!getline(ss, line, ',')) {
                        break;
                    }
                    try {
                        record.push_back(stod(line));
                    }
                    catch (const std::invalid_argument &e) {
                        cout << "NaN found in file " << numeric_filename << " line " << l
                             << endl;
                        e.what();
                    }
                }
                numeric.push_back(record);
            }
        }
        if (!numericFile.eof()) {
            cerr << "Could not read file " << numeric_filename << "\n";
            __throw_invalid_argument("File not found.");
        }
    }
    if (!categ_filename.empty()) {
        ifstream categFile(categ_filename);
        l = 0;
        while (categFile) {
            l++;
            if (!getline(categFile, s))
                break;
            if (s[0] != '#') {
                istringstream ss(s);
                vector<int> record;
                while (ss) {
                    if (!getline(ss, line, ','))
                        break;
                    try {
                        record.push_back(stoi(line));
                    }
                    catch (const std::invalid_argument &e) {
                        cout << "NaN found in file " << categ_filename << " line " << l
                             << endl;
                        e.what();
                    }
                }
                categorical.push_back(record);
            }
        }
        if (!categFile.eof()) {
            cerr << "Could not read file " << categ_filename << "\n";
            __throw_invalid_argument("File not found.");
        }
    }
    ifstream timeFile(time_filename);
    l = 0;
    while (timeFile) {
        l++;
        if (!getline(timeFile, s))
            break;
        if (s[0] != '#') {
            istringstream ss(s);
            while (ss) {
                if (!getline(ss, line, ','))
                    break;
                try {
                    times.push_back(stoi(line));
                }
                catch (const std::invalid_argument &e) {
                    cout << "NaN found in file " << time_filename << " line " << l
                         << endl;
                    e.what();
                }
            }
        }
    }
    if (!timeFile.eof()) {
        cerr << "Could not read file " << time_filename << "\n";
        __throw_invalid_argument("File not found.");
    }
}

int main(int argc, const char *argv[]) {

    argparse::ArgumentParser program("mstream");
    program.add_argument("-n", "--numerical")
            .default_value(string(""))
            .help("Numerical Data File");
    program.add_argument("-c", "--categorical")
            .default_value(string(""))
            .help("Categorical Data File");
    program.add_argument("-t", "--times")
            .required()
            .help("Timestamp Data File");
    program.add_argument("-r", "--rows")
            .default_value(2)
            .action([](const std::string &value) { return std::stoi(value); })
            .help("Number of rows. Default is 2");
    program.add_argument("-b", "--buckets")
            .default_value(1024)
            .action([](const std::string &value) { return std::stoi(value); })
            .help("Number of buckets. Default is 1024");
    program.add_argument("-a", "--alpha")
            .default_value(0.6)
            .action([](const std::string &value) { return std::stod(value); })
            .help("Alpha: Temporal Decay Factor. Default is 0.6");
    program.add_argument("-o", "--output").default_value(string("scores.txt")).help(
            "Output File. Default is scores.txt");
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        program.print_help();
        exit(0);
    }

    string numeric_filename = program.get<string>("-n");
    string categ_filename = program.get<string>("-c");
    string times_filename = program.get<string>("-t");
    string output_filename = program.get<string>("-o");
    int rows = program.get<int>("-r");
    int buckets = program.get<int>("-b");
    auto alpha = program.get<double>("-a");

    if (rows < 1) {
        cerr << "Number of numerichash functions should be positive.\n";
        exit(0);
    }

    if (buckets < 2) {
        cerr << "Number of buckets should be at least 2\n";
        exit(0);
    }

    if (alpha <= 0 || alpha >= 1) {
        cerr << "Alpha: Temporal Decay Factor must be between 0 and 1.\n";
        exit(0);
    }

    if (numeric_filename.empty() && categ_filename.empty()) {
        cerr << "Please give at least one of numeric or categorical data file\n";
        exit(0);
    }

    vector<vector<double> > numeric;
    vector<vector<int> > categ;
    vector<int> times;
    int dimension1 = 0, dimension2 = 0;
    load_data(numeric, categ, times, numeric_filename, categ_filename, times_filename);
    if (!numeric.empty())
        dimension1 = numeric[0].size();
    if (!categ.empty())
        dimension2 = categ[0].size();

    cout << "Finished loading" << endl;

    clock_t start_time2 = clock();
    vector<double> *scores2 = mstream(numeric, categ, times, rows, buckets, alpha, dimension1, dimension2);
    cout << "@ " << ((double) (clock() - start_time2)) / CLOCKS_PER_SEC << endl;

    FILE *output_file = fopen(output_filename.c_str(), "w");
    for (double i : *scores2) {
        fprintf(output_file, "%f\n", i);
    }
    return 0;
}