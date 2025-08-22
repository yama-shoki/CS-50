-- 【問題文】
-- Kevin Baconが主演した映画に出演したすべての人の名前をリストするSQLクエリを記述します。
-- クエリを実行すると、各ユーザーの名前を1つの列で表すテーブルが出力されます。
-- データベースにKevin Baconという名前の人が複数存在する可能性があります。必ず1958年生まれのKevin Baconだけを選んでください。
-- Kevin Bacon本人は結果リストに含まれません。


SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN (
    SELECT movies.id
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Kevin Bacon'
    AND people.birth = 1958
)
AND people.name != 'Kevin Bacon';


