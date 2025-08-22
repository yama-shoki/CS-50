#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // コマンドライン引数の数をチェック
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    // イメージファイルを開く
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    
    // 1バイトのデータ型を定義
    typedef uint8_t BYTE;
    
    // 512バイトのバッファを作成
    BYTE buffer[512];
    
    // JPEG出力用のファイルポインタ
    FILE *output_file = NULL;
    
    // 復元したJPEGファイルの数をカウント
    int jpeg_count = 0;
    
    // ファイルから512バイトずつ読み込む
    while (fread(buffer, sizeof(BYTE), 512, input_file) == 512)
    {
        // 最初の3バイト: 0xff, 0xd8, 0xff
        // 4バイト目: 0xe0〜0xef（上位4ビットが1110）
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && 
            (buffer[3] & 0xf0) == 0xe0)
        {   
            // 前のファイルが開いている場合は閉じる
            if (output_file != NULL)
            {
                fclose(output_file);
            }
            
            // 新しいJPEGファイル名を作成
            // sprintf: 文字列のフォーマット（printfのファイル版）
            char filename[8];  // "###.jpg" + null terminator
            sprintf(filename, "%03d.jpg", jpeg_count);
            
            // 新しいファイルを書き込みモードで開く
            output_file = fopen(filename, "w");
            if (output_file == NULL)
            {
                printf("Could not create %s.\n", filename);
                fclose(input_file);
                return 1;
            }
            
            // JPEGファイル数をインクリメント
            jpeg_count++;
        }
        
        // 現在JPEGファイルが開いている場合、バッファの内容を書き込む
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, output_file);
        }
    }
    
    // 開いているファイルをすべて閉じる
    if (output_file != NULL)
    {
        fclose(output_file);
    }
    fclose(input_file);
    
    printf("Recovery completed. Found %d JPEG files.\n", jpeg_count);
    return 0;
}