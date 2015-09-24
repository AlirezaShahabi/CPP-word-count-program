
// c++11

// In this program, we read a text file and report how many times each word is
// repeated. We exclude certain words from the counting process. We use a std::map
// to store the words and their repetition and a std::set to store the exclusion words.


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>  



// declaring the readText(), countWord() and display() functions
void read_text(std::ifstream&, std::map<std::string,int>&, const std::set<std::string>&);
void count_word(const std::string&, std::map<std::string,int>&, const std::set<std::string>&);
void display(const std::map<std::string,int>&, std::ofstream&);



int main (){

    std::ifstream rFile("1-string-stream.txt");
    
    std::map<std::string,int> word_count;
    
    std::set<std::string> exclude_word = {"a","an","the","The","or","of","on","On"};
    
    read_text(rFile, word_count, exclude_word);
    
    std::ofstream wFile("output.txt");
    
    display(word_count, wFile);
    
    return 0;
}



// this function reads text from file, devide it into lines, and then passes each line
// into countWord() function
void read_text(std::ifstream& rf, std::map<std::string,int>& w_c, const std::set<std::string>& e_w){
    std::string line;
    // call CountWord for each line
    while (std::getline(rf,line)) {count_word(line, w_c, e_w);}
}



// this function recieves lines of string, check each word in the line, add the word
// to a map if it does not exist in the exclusion set
void count_word(const std::string& line, std::map<std::string,int>& w_c, const std::set<std::string>& e_w){
    std::istringstream iss(line);
    std::string word;
    std::vector<char> punc_v{'.' , ',' , ':' , ';' , '?'};
    while (iss >> word) {
        // remove the punctuations at the end of words (if any)
        char c = *(word.end()-1);
        if (std::find(punc_v.begin(),punc_v.end(),c) != punc_v.end()) {word.erase(word.end()-1);}
        // add the word to the map if it is not a member of the excluded words
        if (e_w.find(word) == e_w.end()) {++w_c[word];}
    }
}



// this function displays the content of word_count
void display(const std::map<std::string,int>& w_c, std::ofstream& wf){
    for (const auto& element : w_c){
        std::string s = element.second>1 ? " times":" time";
        wf << element.first << " is repeated " << element.second << s << std::endl;
    }
}



