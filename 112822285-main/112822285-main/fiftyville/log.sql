-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time.
-- All Mention the bakery in the interview transcripts.
SELECT description
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- Interviews from Ruth, Eugene, Raymond
-- Call someone after the theft for less a minute and plan to leave by taking the earliest plane tomorrow.
-- saw the thief withdrawing the money on Leggett Street earlier on that day.
-- Within 10 minutes of the theft, get into a car in the bakery parking lot and drive away.
SELECT transcript, name
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- Find the earlist flight by sorting.
-- Original_airport_id is 8 and the flight was taken at 8:20 and the destination was airport_id 4 and flight_id is 36
SELECT origin_airport_id, destination_airport_id, hour, minute, id
FROM flights
WHERE year = 2021 AND month = 7 AND day = 29
ORDER BY hour;
-- The city the thief escaped to was New York City
SELECT city
FROM airports
WHERE id = 4;

-- No use query
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28
AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

-- Get possible thives from all clues and have Bruce, Sofia and Kelsey and their ids
SELECT DISTINCT people.passport_number, name, people.id
FROM people, bakery_security_logs, phone_calls, passengers
WHERE people.license_plate = bakery_security_logs.license_plate
AND people.phone_number = phone_calls.caller
AND bakery_security_logs.minute > 15
AND bakery_security_logs.minute < 25
AND bakery_security_logs.year = phone_calls.year
AND bakery_security_logs.month = phone_calls.month
AND bakery_security_logs.day = phone_calls.day
AND phone_calls.duration < 60
AND people.passport_number = passengers.passport_number
AND passengers.flight_id = 36
AND bakery_security_logs.day = 28
AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.hour = 10;

-- Compare person_id in bank_accounts table, there is only 686048, this is Bruce, so he is the thief.
SELECT account_number, person_id
FROM bank_accounts
WHERE person_id IN (686048, 398010, 560886);

-- Have known the thief's name, id, phone_number find his receiver's phone_number and name.
SELECT name
FROM people
WHERE phone_number =
(SELECT DISTINCT receiver
FROM phone_calls, people
WHERE phone_calls.caller =
(SELECT phone_number
FROM people
WHERE id = 686048
AND name = "Bruce")
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60);