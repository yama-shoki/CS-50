-- 【問題文】
-- 2.sqlで、Emma Stoneの誕生年を判別するSQLクエリを記述します。
-- クエリは、Emma Stoneの誕生年を含む単一の列と単一の行 (ヘッダーを含まない) を持つテーブルを出力します。
-- データベースにはEmma Stoneという名前の人物が1人だけ存在すると仮定します。

SELECT birth
FROM people
WHERE name = 'Emma Stone';
