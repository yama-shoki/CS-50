def main():
    user_input = input("Text: ")

    letters = count_letters(user_input)
    words = count_words(user_input)
    sentences = count_sentences(user_input)

    print(f"{letters} letters")
    print(f"{words} words")
    print(f"{sentences} sentences")

    # 動画で紹介された式を使う。
    L = letters / words * 100
    S = sentences / words * 100

    # Coleman-Liau指数は課題で提示された式を使う。
    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    # 結果表示
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


# 文字数カウント
def count_letters(text):
    count = 0
    for char in text:
        if char.isalpha(): 
            count += 1
    return count

# 単語数カウント
def count_words(text):
    count = 1  # スペース数 + 1
    for char in text:
        if char == ' ':
            count += 1
    return count



# 文数カウント
def count_sentences(text):
    count = 0
    for char in text:
        if char in ['.', '!', '?']:
            count += 1
    return count

main()
