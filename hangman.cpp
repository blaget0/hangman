#include <iostream>
#include <iterator>
#include "random.h"
#include <string_view>
#include <vector>
#include <cstddef>

namespace WordList {
    std::vector<std::string_view> words { "bottle", "purple" , "chair", "airplane", "fireworks", "onion", "keyboard", "lantern" };

    std::string_view getRandomWord() {
        return words[Random::get(0, std::ssize(words)) - 1];
    }
}

class Session {
private:
    std::string_view m_word{ WordList::getRandomWord() };
    std::vector<bool> m_lettersGuessed{ std::vector<bool>(26) };
    int m_wrongGuesses{ 6 };
    bool m_win{ false };

public:
    Session() = default;

    std::string_view getWord() const { return m_word; }

    int getWrongGuesses() const { return m_wrongGuesses; }

    bool hasWon() const { return m_win; }

    bool isLetterGuessed(char c) const {
        return (m_lettersGuessed[(c % 32) - 1] == true);
    }
    void setLetterGuessed(char ch) {
        m_lettersGuessed[(ch % 32) - 1] = true;
    }
    bool isLetterInWord(char chr) const {
        bool flag{ false };
        for (int k{ 0 }; k < std::ssize(m_word); ++k) {
            if (chr == m_word[k]) {
                flag = true;
            }
        }
        return flag;
    }

    void drawGame() {
        std::cout << "The word: ";
        int count{ 0 };
        for (int i{ 0 }; i < std::ssize(m_word); ++i) {
            if (isLetterGuessed(m_word[i])) {
                std::cout << m_word[i];
                ++count;
                continue;
            }
            std::cout << '_';
        }
        if (count == std::ssize(m_word)) {
            m_win = true;
        }
        std::cout << '\n';
        std::cout << "Wrong guesses: ";
        for (int j{ 0 }; j < m_wrongGuesses; ++j) {
            std::cout << '+';
        }
        std::cout << '\n';
        std::cout << "Guesses: ";
        for (char c = 'a'; c <= 'z'; ++c) {
            if (isLetterGuessed(c)) {
                std::cout << c;
            }
        }
        std::cout << '\n';

        if (m_win == false){
            std::cout << "Enter the letter: ";
        }
    }

    char getInput() {
        char input;
        std::cin >> input;
        while (!std::cin || (input < 'a' || input > 'z') || (isLetterGuessed(input))) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Fail" << '\n';
            std::cout << "Enter the letter: ";
            std::cin >> input;
        }
        std::cout << "You entered: " << input << '\n';
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        setLetterGuessed(input);

        if (isLetterInWord(input) == false) {
            --m_wrongGuesses;
        }
        return input;
    }
};


int main()
{
    int wrongGuesses{ 6 };

    Session session;
    while (true) {
        if (session.getWrongGuesses() <= 0) {
            std::cout << "You lost\n";
            break;
        }
        session.drawGame();
        if (session.hasWon()) {
            std::cout << "You won\n";
            break;
        }
        char guess{ session.getInput() };
    }
}
