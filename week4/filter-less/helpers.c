#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // 各ピクセルに対してループ処理
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // RGB値の平均を計算
            // グレースケールは赤、緑、青の値をすべて同じにする
            int average = round((image[i][j].rgbtRed + 
                               image[i][j].rgbtGreen + 
                               image[i][j].rgbtBlue) / 3.0);
            
            // すべての色成分を平均値にする
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // 各ピクセルに対してループ処理
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 元の色値を保存
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            
            // セピア色の計算式
            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            
            // 255を超えないようにする
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // 各行に対してループ処理
    for (int i = 0; i < height; i++)
    {
        // 幅の半分まででループ（左右を交換するため）
        for (int j = 0; j < width / 2; j++)
        {
            // 左端と対応する右端のピクセルを交換
            // 一時変数を使ってスワップ
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // 元の画像のコピーを作成
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    
    // 各ピクセルに対してぼかしをいれる
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;
            
            // 3x3のグリッド内の隣接ピクセルをチェック
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;  // 新しい行インデックス
                    int nj = j + dj;  // 新しい列インデックス
                    

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalRed += copy[ni][nj].rgbtRed;
                        totalGreen += copy[ni][nj].rgbtGreen;
                        totalBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }
            
            // 平均を計算して新しいピクセル値に設定する
            image[i][j].rgbtRed = round(totalRed / (float)count);
            image[i][j].rgbtGreen = round(totalGreen / (float)count);
            image[i][j].rgbtBlue = round(totalBlue / (float)count);
        }
    }
    return;
}