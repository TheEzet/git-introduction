#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class HangmanGame {
public:
    void setSecretWord(const std::string&);
    bool guess(char);
    int getRemainingGuesses() const {return remainingGuesses;}
private:
    std::string word, correctLetters, newSecret;
    int remainingGuesses;
};

void HangmanGame::setSecretWord(const std::string &newWord){
// start new game
    word = newWord;
    correctLetters.clear();
    remainingGuesses = 9;
}

bool HangmanGame::guess(char letter){
    // find character in word. If not found, word.find returns string::npos.
    std::string::size_type found = word.find(letter);
    if(found == std::string::npos){
        --remainingGuesses;
        std::cout << "Sorry, wrong guess! You have " << remainingGuesses 
            << " remaining guesses.\n";
        if(remainingGuesses == 0) {
            std::cout << "Too bad, you lost! x.x\n";
            return false;
        }
        
    } else correctLetters.push_back(letter);

    // print all currently guessed letters
    // Also add a check to see if the full word was found
    bool isSomeLetterWrong = false;
    std::cout << "\n\t Guessed so far:\n";
    for(int i = 0;i < word.size(); ++i ){
        // Check for each character in the secret word if it is guessed.
        // Print the letter if found, print "." if not found yet.
        found = correctLetters.find(word[i]);
        if(found == std::string::npos){
            isSomeLetterWrong = true;
            std::cout << ".";
        } else std::cout << word[i];    
    }
    if(!isSomeLetterWrong){
        std::cout << "Congratulations, you guessed the word!\n";
        
    } else std::cout << "Please try again.\n";
    
    return isSomeLetterWrong;
}

int main(){
    std::ifstream ifs("hangman_words.txt");
    if(!ifs.is_open()){
        std::cerr << "Could not open file!\n";
    }
    std::vector< std::string > vWords;
    while(!ifs.eof()){
        std::string sWord;
        ifs >> sWord;
        vWords.push_back(sWord);
    }
    ifs.close();
    // Test if file is opened correctly
   
    HangmanGame hangman;
    hangman.setSecretWord(vWords[0]);

    // start game
    char ch;
    do {
        std::cout << "Enter a letter to guess the secret word : ";
        std::cin >> ch;
    } while (hangman.guess(ch));
    if(hangman.getRemainingGuesses()!=0){
        std::cout << "Add a new word to the list:\n";
        std::string newSecretWord;
        std::cin >> newSecretWord;
        vWords.push_back(vWords[0]);
        vWords[0] = newSecretWord;
    }
    std::rotate(vWords.begin(),vWords.begin() + 1 ,vWords.begin() + int(vWords.size()/2));
    std::ofstream ofs("hangman_words.txt");
    if(ofs.is_open()){
        for(int i = 0; i < vWords.size() ; ++i){
            ofs << vWords[i] << "\n";
        }
    } else std::cerr << "Could not open the save file!\n";
    return 0;
}