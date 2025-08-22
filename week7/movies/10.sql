-- 【問題文】
-- 10.sqlで、9.0以上のレーティングを受けた映画を監督したすべての人の名前をリストするSQLクエリを記述します。
-- クエリを実行すると、各ユーザーの名前を1つの列で表すテーブルが出力されます。

SELECT DISTINCT people.name
FROM people
JOIN directors ON people.id = directors.person_id
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0;
