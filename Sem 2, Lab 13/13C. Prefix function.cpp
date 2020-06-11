#include <iostream>
#include <vector>
#include <fstream>
 
std::vector<int> prefix;
 
void findPrefixFunction(std::string string) {
    prefix.resize(string.length());
    for (int i = 1; i < string.length(); i++) {
        int j = prefix[i - 1];
        while (j > 0 && string[i] != string[j]) {
            j = prefix[j - 1];
        }
        if (string[i] == string[j]) {
            j++;
        }
        prefix[i] = j;
    }
}
 
int main() {
    std::string string;
     
    std::ifstream fin("prefix.in");
     
    fin >> string;
     
    fin.close();
     
    findPrefixFunction(string);
     
    std::ofstream fout("prefix.out");
     
    for (int i = 0; i < prefix.size(); i++) {
        fout << prefix[i] << ' ';
    }
     
    fout.close();
}
