#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;

    // do whileで1~8以外の数字の場合は再入力を求める
    do
    {
        n = get_int("type number between 1~8: ");
    }
    while (n < 1 || n > 8);


    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++) 
        {
            if (j <= n - i)
            {
                printf(" "); // 各行ごとのスペース
            }
            else
            {
                printf("#"); // 各行ごとの#
            }
        }

        printf("\n"); // 改行
    }
}