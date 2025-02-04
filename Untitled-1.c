#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define MAX_WORD_LENGTH 100

void displayWord(const char word[], const int revealed[]);
void displayHangman(int wrongGuesses);
int checkWin(const int revealed[], int length);

const char *wordList[] = {
    "apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon",
    "mango", "nectarine", "orange", "papaya", "quince", "raspberry", "strawberry", "tangerine", "ugli", "vanilla",
    "watermelon", "xigua", "yuzu", "zucchini", "apricot", "blueberry", "coconut", "dragonfruit", "eggplant", "guava",
    "hazelnut", "indigo", "jackfruit", "kumquat", "lychee", "mulberry", "nectar", "olive", "peach", "quinoa",
    "radish", "spinach", "tomato", "umbrella", "violet", "walnut", "xylophone", "yam", "zebra"};

#define WORD_LIST_SIZE (sizeof(wordList) / sizeof(wordList[0]))

int main() {
    char word[MAX_WORD_LENGTH];
    char guess;
    int revealed[MAX_WORD_LENGTH] = {0};
    int wrongGuesses = 0, maxWrongGuesses = 7;

    srand(time(NULL));
    strncpy(word, wordList[rand() % WORD_LIST_SIZE], MAX_WORD_LENGTH);
    word[MAX_WORD_LENGTH - 1] = '\0';  // Ensuring null-termination

    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        word[i] = tolower(word[i]);
    }

    printf("\nLet's play Hangman!\n");

    while (wrongGuesses < maxWrongGuesses) {
        displayHangman(wrongGuesses);
        displayWord(word, revealed);
        printf("\nEnter a guess: ");
        scanf(" %c", &guess);  // Added space before %c to consume leftover whitespace
        guess = tolower(guess);

        int correctGuess = 0;
        for (int i = 0; i < length; i++) {
            if (word[i] == guess && !revealed[i]) {
                revealed[i] = 1;
                correctGuess = 1;
            }
        }

        if (!correctGuess) {
            wrongGuesses++;
            printf("Incorrect guess! You have %d guesses left.\n", maxWrongGuesses - wrongGuesses);
        }

        if (checkWin(revealed, length)) {
            displayHangman(wrongGuesses);
            printf("\nCongratulations! You guessed the word: %s\n", word);
            return 0;
        }
    }

    displayHangman(wrongGuesses);
    printf("\nGame over! The word was: %s\n", word);
    return 0;
}

void displayWord(const char word[], const int revealed[]) {
    printf("\nWord: ");
    for (int i = 0; word[i] != '\0'; i++) {
        if (revealed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void displayHangman(int wrongGuesses) {
    const char *stages[] = {
        "\n  +---+\n      |\n      |\n      |\n     ===",
        "\n  +---+\n  O   |\n      |\n      |\n     ===",
        "\n  +---+\n  O   |\n  |   |\n      |\n     ===",
        "\n  +---+\n  O   |\n /|   |\n      |\n     ===",
        "\n  +---+\n  O   |\n /|\  |\n      |\n     ===",
        "\n  +---+\n  O   |\n /|\  |\n /    |\n     ===",
        "\n  +---+\n  O   |\n /|\  |\n / \  |\n     ==="};

    printf("%s\n", stages[wrongGuesses]);
    sleep(1);  // Use sleep instead of usleep for platform compatibility
}

int checkWin(const int revealed[], int length) {
    for (int i = 0; i < length; i++) {
        if (!revealed[i]) {
            return 0;
        }
    }
    return 1;
}