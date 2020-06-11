 #include <iostream>
 #include <vector>
 #include <fstream>
   
 std::vector<int> prefix;
 std::vector<int> answer;
   
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
   
 void doKMPAlgorithm(std::string string, std::string substring) {
     findPrefixFunction(substring + '#' +string);
       
     for (int i = 0; i < string.length(); i++) {
         if (prefix[substring.length() + i + 1] == substring.length()) {
             answer.push_back(static_cast<int>(i - substring.length() + 2));
         }
     }
 }
   
 int main() {
     std::string substring;
     std::string string;
       
     std::ifstream fin("search2.in");
       
     fin >> substring >> string;
       
     fin.close();
       
     doKMPAlgorithm(string, substring);
       
     std::ofstream fout("search2.out");
       
     fout << answer.size() << '\n';
     for (int i = 0; i < answer.size(); i++) {
         fout << answer[i] << ' ';
     }
       
     fout.close();
 }
