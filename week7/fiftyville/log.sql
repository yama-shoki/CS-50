-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Step 1: 事件の詳細を確認
-- 2020年7月28日、Chamberlin Streetで起きた盗難事件の詳細を調べる
SELECT description 
FROM crime_scene_reports 
WHERE year = 2020 
AND month = 7 
AND day = 28 
AND street = 'Chamberlin Street'
AND description LIKE '%theft%';

-- 結果: 午前10時15分頃、CS50アヒルがChemberlin Street法廷から盗まれた。
-- 3人の目撃者がいる。全員「courthouse（法廷）」という言葉を含むインタビューをしている。

-- Step 2: 目撃者のインタビューを確認
-- 法廷に関するインタビューを7月28日から探す
SELECT name, transcript 
FROM interviews 
WHERE year = 2020 
AND month = 7 
AND day = 28 
AND transcript LIKE '%courthouse%';

-- 結果から得られた手がかり:
-- Ruth: 盗難から10分以内に、泥棒が法廷駐車場から車で立ち去るのを見た
-- Eugene: 朝、泥棒がFisk Street のATMでお金を引き出しているのを見た  
-- Raymond: 盗難後、泥棒が1分以内に誰かに電話し、明日の最初のフライトで町を出ると言った

-- Step 3: 法廷のセキュリティログを確認
-- 10:15から10:25の間に法廷駐車場を出た車を調べる
SELECT license_plate, activity 
FROM courthouse_security_logs 
WHERE year = 2020 
AND month = 7 
AND day = 28 
AND hour = 10 
AND minute >= 15 
AND minute <= 25 
AND activity = 'exit';

-- 容疑者の車のナンバープレート一覧を取得

-- Step 4: ATM取引記録を確認  
-- Fisk Streetで朝のうちにお金を引き出した人を調べる
SELECT account_number, amount 
FROM atm_transactions 
WHERE year = 2020 
AND month = 7 
AND day = 28 
AND atm_location = 'Fisk Street' 
AND transaction_type = 'withdraw';

-- Step 5: 電話記録を確認
-- 盗難後1分以内（10:15-10:16）に行われた短い電話を調べる
SELECT caller, receiver, duration 
FROM phone_calls 
WHERE year = 2020 
AND month = 7 
AND day = 28 
AND duration < 60;

-- Step 6: 翌日（7月29日）の最初のフライトを確認
-- Fiftyvilleから出発する最も早いフライトを調べる
SELECT id, destination_airport_id, hour, minute 
FROM flights 
WHERE year = 2020 
AND month = 7 
AND day = 29 
ORDER BY hour, minute 
LIMIT 1;

-- 結果: フライトID 36, 目的地空港ID 4, 8:20 AM

-- Step 7: 目的地の確認
SELECT city 
FROM airports 
WHERE id = 4;
-- 結果: London（ロンドン）

-- Step 8: 容疑者の絞り込み
-- 3つの条件を満たす人物を特定：
-- 1) 法廷駐車場から10:15-10:25に退出
-- 2) Fisk StreetのATMで7/28朝に引き出し
-- 3) 7/29 8:20のロンドン行きフライトに搭乗

-- 法廷駐車場から退出した人の身元確認
SELECT people.name, people.phone_number, people.passport_number 
FROM people 
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate 
WHERE courthouse_security_logs.year = 2020 
AND courthouse_security_logs.month = 7 
AND courthouse_security_logs.day = 28 
AND courthouse_security_logs.hour = 10 
AND courthouse_security_logs.minute >= 15 
AND courthouse_security_logs.minute <= 25 
AND courthouse_security_logs.activity = 'exit';

-- ATMで引き出しした人の身元確認  
SELECT people.name, people.phone_number, people.passport_number 
FROM people 
JOIN bank_accounts ON people.id = bank_accounts.person_id 
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number 
WHERE atm_transactions.year = 2020 
AND atm_transactions.month = 7 
AND atm_transactions.day = 28 
AND atm_transactions.atm_location = 'Fisk Street' 
AND atm_transactions.transaction_type = 'withdraw';

-- フライトの乗客確認
SELECT people.name, people.phone_number, people.passport_number 
FROM people 
JOIN passengers ON people.passport_number = passengers.passport_number 
WHERE passengers.flight_id = 36;

-- Step 9: 3つの条件をすべて満たす人物を特定
-- 複数のクエリ結果を照合して共通する人物を見つける
SELECT people.name 
FROM people 
WHERE people.license_plate IN (
    -- 法廷から退出した車
    SELECT license_plate 
    FROM courthouse_security_logs 
    WHERE year = 2020 AND month = 7 AND day = 28 
    AND hour = 10 AND minute >= 15 AND minute <= 25 
    AND activity = 'exit'
) 
AND people.id IN (
    -- ATMで引き出した人
    SELECT bank_accounts.person_id 
    FROM bank_accounts 
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number 
    WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 
    AND atm_transactions.atm_location = 'Fisk Street' 
    AND atm_transactions.transaction_type = 'withdraw'
) 
AND people.passport_number IN (
    -- フライトに登場した人
    SELECT passport_number 
    FROM passengers 
    WHERE flight_id = 36
);

-- 結果: Ernest

-- Step 10: 共犯者の特定
-- Ernestが電話した相手を調べる
SELECT people.name 
FROM people 
JOIN phone_calls ON people.phone_number = phone_calls.receiver 
WHERE phone_calls.year = 2020 
AND phone_calls.month = 7 
AND phone_calls.day = 28 
AND phone_calls.duration < 60 
AND phone_calls.caller = (
    SELECT phone_number 
    FROM people 
    WHERE name = 'Ernest'
);
