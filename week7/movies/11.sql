-- 【問題文】
-- 11.sqlで、SQLクエリを記述し、Chadwick Bosemanが主演した映画の評価の高い順に5つのタイトルをリストします。
-- クエリを実行すると、各ムービーのタイトルを1つの列にまとめたテーブルが出力されます。
-- データベースにはChadwick Bosemanという名前の人が1人しかいないとします。

SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;
