#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int k);

int main(int argc, string argv[])
{
    // コマンドライン引数が1つではない場合はメッセージ。
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // 入力された文字が0~9の数字か判定
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // 文字列をASCIIの数値に変換し、アルファベットの26文字で割った余りを使う。
    int key = atoi(argv[1]) % 26;

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // 暗号化した文字を表示
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
    return 0;
}

// 入力された文字が0~9の数字か判定する関数
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// シフトして暗号化する関数
char rotate(char c, int k)
{
    if (isupper(c))
    {

        return 'A' + ( (c - 'A' + k) % 26 );
    }
    else if (islower(c))
    {
        return 'a' + ( (c - 'a' + k) % 26 );
    }
    else
    {
        return c;
    }
}
