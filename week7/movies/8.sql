-- 【問題文】
-- 8.sqlで、トイ・ストーリーに出演したすべての人の名前をリストするSQL問合せを記述します。
-- クエリを実行すると、各人物の名前を1つの列で表すテーブルが出力されます。
-- データベースにはToy Storyというタイトルのムービーが1つだけあるとします。

SELECT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = 'Toy Story';
