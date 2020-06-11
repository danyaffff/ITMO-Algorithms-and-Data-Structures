#include <iostream>
#include <fstream>
#include <vector>
 
int main() {
    std::string substring;
    std::string string;
    std::ifstream fin("search1.in");
     
    std::vector<int> occurrences;
     
    fin >> substring >> string;
     
    fin.close();
     
    for (int i = 0; i < string.size(); i++) {
        if (substring[0] == string[i]) {
            for (int j = 0; j < substring.size(); j++) {
                if (substring[j] == string[i + j]) {
                    if (j == substring.size() - 1) {
                        occurrences.push_back(i);
                    }
                } else {
                    break;
                }
            }
        }
    }
     
    occurrences.shrink_to_fit();
     
    std::ofstream fout("search1.out");
     
    fout << occurrences.size() << '\n';
    for (int i = 0; i < occurrences.size(); i++) {
        fout << occurrences[i] + 1 << ' ';
    }
     
    fout.close();
}
