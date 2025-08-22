-- 【問題文】
-- 7.sqlで、2010年にリリースされたすべての映画とそのレーティングをレーティングの降順でリストするSQLクエリを記述します。同じ評価の映画の場合は、タイトルのアルファベット順に並べ替えます。
-- クエリを実行すると、2つの列を持つテーブルが出力されます。1つは各ムービーのタイトル、もう1つは各ムービーのレーティングです。
-- レーティングが設定されていない映画は結果に含めないでください。

SELECT movies.title, ratings.rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = 2010
ORDER BY ratings.rating DESC, movies.title ASC;
