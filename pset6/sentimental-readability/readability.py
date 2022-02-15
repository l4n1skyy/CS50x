import sys


def main():
    text = input("Text: ")
    length = len(text)
    letters = letter_counter(text, length)
    words = word_counter(text, length)
    sentences = sentence_counter(text, length)
    grade = compute_grade(letters, words, sentences, length)
    sys.exit()


def letter_counter(text, length):
    letters = 0
    for i in range(length):
        if text[i].isalpha():
            letters += 1
    return letters


def word_counter(text, length):
    words = 1
    for i in range(length):
        if text[i] == " ":
            words += 1
    return words


def sentence_counter(text, length):
    sentences = 0
    for i in range(length):
        if text[i] in ["?", ".", "!"]:
            sentences += 1
    return sentences


def compute_grade(letters, words, sentences, length):
    L = letters * 100.0 / words
    S = sentences * 100.0 / words
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")
    return


if __name__ == '__main__':
    main()