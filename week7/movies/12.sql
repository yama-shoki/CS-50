-- 【問題文】
-- 12.sqlで、Johnny DeppとHelena Bonham Carterの両方が主演したすべての映画のタイトルをリストするSQLクエリを記述します。
-- クエリを実行すると、各ムービーのタイトルを1つの列にまとめたテーブルが出力されます。
-- データベースにはJohnny Deppという名前の人が1人しかいないと仮定します。
-- データベースには、Helena Bonham Carterという名前の人物が1人だけ存在するものとします。

SELECT movies.title
FROM movies
JOIN stars s1 ON movies.id = s1.movie_id
JOIN people p1 ON s1.person_id = p1.id
JOIN stars s2 ON movies.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id
WHERE p1.name = 'Johnny Depp'
AND p2.name = 'Helena Bonham Carter';
