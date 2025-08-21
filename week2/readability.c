#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string user_input = get_string("Text: ");

    int letters = count_letters(user_input);
    int words = count_words(user_input);
    int sentences = count_sentences(user_input);


    printf("%i letters\n", letters);
    printf("%i words\n", words);
    printf("%i sentences\n", sentences);

    // 動画で紹介された式を使う。
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;

    // Coleman-Liau指数は課題で提示された式を使う。
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    // 結果表示
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// 文字数カウント
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// 単語数カウント
int count_words(string text)
{
    int count = 1; // スペース数 + 1
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

// 文数カウント
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
