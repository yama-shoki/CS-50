// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
// 連結リストの1つのノード（単語を保存する箱）
typedef struct node
{
    char word[LENGTH + 1];  // 単語を保存する場所
    struct node *next;     // 次のノードを指すポインタ
}
node;

// Hash Tableのサイズ
#define N 50000

// Hash table - ポインタの配列、各要素は連結リストの先頭を指す
node *table[N];

// 辞書に入ってる単語の数をカウントする変数
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
// 単語が辞書にあるかチェックする関数
bool check(const char *word)
{
    // ①入力された単語を小文字に変換する準備
    char lowercase_word[LENGTH + 1];
    int len = strlen(word);
    
    // ②長すぎる単語は辞書に存在しないのでfalseを返す
    if (len > LENGTH)
    {
        return false;
    }
    
    // ③大文字小文字を統一するため小文字に変換する
    for (int i = 0; i < len; i++)
    {
        lowercase_word[i] = tolower(word[i]);
    }
    lowercase_word[len] = '\0';  // 文字列の終端文字
    
    // ④ハッシュ値を計算して該当する箱（バケット）を見つける
    unsigned int index = hash(lowercase_word);
    
    // ⑤その箱の中の連結リストを順番に探す
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // ⑥strcmp: 文字列が一致すれば0を返す
        if (strcmp(cursor->word, lowercase_word) == 0)
        {
            return true;  // 単語が見つかった場合
        }
        cursor = cursor->next;  // 次のノードへ
    }
    
    // ⑦単語が見つからなかった
    return false;
}

// Hashes word to a number
// 単語を数字（ハッシュ値）に変換する関数
unsigned int hash(const char *word)
{
    // ①djb2アルゴリズム用の初期値を設定
    unsigned long hash_value = 5381;
    int c;
    
    // ②単語の各文字を使ってハッシュ値を計算する
    while ((c = *word++))
    {
        hash_value = ((hash_value << 5) + hash_value) + c;
    }
    
    // ③ハッシュテーブルのサイズで割った余りを返す（0～N-1の範囲）
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
// 辞書ファイルを読み込んでメモリに保存する関数
bool load(const char *dictionary)
{
    // ①辞書ファイルを読み取りモードで開く
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;  // ファイルが開けない場合はfalseを返す
    }
    
    char word[LENGTH + 1];  // 単語を一時保存する変数
    
    // ②ファイルから1行ずつ単語を読み取る
    while (fscanf(file, "%s", word) != EOF)
    {
        // ③新しいノードをメモリに確保する
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            // メモリ確保に失敗した場合の処理
            fclose(file);
            return false;
        }
        
        // ④単語をノードにコピーする
        strcpy(new_node->word, word);
        
        // ⑤ハッシュ値を計算してどの箱（バケット）に入れるか決める
        unsigned int index = hash(word);
        
        // ⑥新しいノードを連結リストの先頭に挿入（O(1)で早い）
        new_node->next = table[index];  // 今まで先頭だったものを次にする
        table[index] = new_node;        // 新しいノードを先頭にする
        
        // ⑦単語数をカウントアップ
        word_count++;
    }
    
    // ⑧ファイルを閉じて正常終了
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
// 辞書に入ってる単語数を返す関数
unsigned int size(void)
{
    // ①辞書が読み込まれていない場合は0が返される
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
// 使ったメモリを解放する関数
bool unload(void)
{
    // ①ハッシュテーブルの全ての箱（バケット）を見る
    for (int i = 0; i < N; i++)
    {
        // ②各箱の中の連結リストを全部解放する
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // ③次のノードを一時保存してからメモリを解放
            node *temp = cursor;
            cursor = cursor->next;  // 次へ進む
            free(temp);             // メモリを返す
        }
    }
    
    // ④正常に解放完了
    return true;
}