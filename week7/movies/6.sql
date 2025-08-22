-- 【問題文】
-- 6.sqlで、2012年にリリースされたすべての映画の平均レーティングを決定するSQLクエリを記述します。
-- クエリは、平均レーティングを含む単一の列と単一の行 (ヘッダーを含まない) を持つテーブルを出力します。


SELECT AVG(rating)
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2012;
