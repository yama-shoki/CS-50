-- 【問題文】
-- 9.sqlで、2004年に公開された映画に主演したすべての人の名前を、誕生年順にリストするSQLクエリを記述します。
-- クエリを実行すると、各ユーザーの名前を1つの列で表すテーブルが出力されます。
-- 同じ生年月日の人は、任意の順序でリストできます。
-- 生年月日が記入されていない場合、生年月日のある人が順番に記載されていれば問題ありません。
-- ある人物が2004年に複数の映画に出演した場合、その人物は一度だけ検索結果に表示されます。


SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth;
