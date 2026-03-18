from cs50 import get_string
from sys import exit

# Coleman Liau index coefficients:
coefficient_l = 0.0588
coefficient_s = - 0.296
indep = - 15.8


def coleman_liau_index(letters_per_100_words, sentences_per_100_words):
    # the coleman liau formula calculates the readability index as a function of
    # the average number of letters per 100 words (L) and the average number of
    # sentences per 100 words
    index = coefficient_l * letters_per_100_words + coefficient_s * sentences_per_100_words + indep
    index = round(index)
    return index


def compute_averages(text):

    words = 1  # we start counting the first word because there will
    # not be a space after the last one
    sentences = 0
    letters = 0
    for character in text:
        if character == " ":  # condition for new word
            words += 1
        elif character in ".!?":  # condition for end of sentence
            sentences += 1
        elif character.isalpha():  # check if the character is alphabetical
            letters += 1
    if (words == 1):
        print("Not enough words")
        exit(1)
    L = letters / words
    try:
        S = words / sentences
    except ZeroDivisionError:
        print("No sentences")
        exit(2)
    return L, S


if __name__ == "__main__":  # main function
    text = get_string("Text: ")
    letters_per_words, words_per_sentence = compute_averages(text)
    letters_per_100_words = 100 * letters_per_words  # average number of letters per 100 words
    # average number of words per 100 sentences
    sentences_per_100_words = (100 / words_per_sentence)

    index = coleman_liau_index(letters_per_100_words, sentences_per_100_words)  # calculate index
    if (index > 16):
        print("Grade 16+")
        exit(0)
    if (index < 1):
        print("Before Grade 1")
        exit(0)
    print(f"Grade {index}")
    exit(0)
