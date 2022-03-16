-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Review thefts on 28th July at Humphrey Street
SELECT * FROM crime_scene_reports WHERE street LIKE "Humphrey Street" AND month = 7 AND day = 28 AND description LIKE "%theft%";

-- Review witnesses
SELECT * FROM interviews WHERE transcript LIKE "%bakery%" AND month = 7 AND day = 28;

-- Keep track of suspects
CREATE TABLE thief (
    person_id INTEGER,
    id INTEGER,
    PRIMARY KEY(id)
);

-- Get people who left bakery within 10 minutes after theft (thief)
INSERT INTO thief (person_id)
SELECT id FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28
        AND hour = 10
        AND minute >= 15 AND minute <= 25
);

-- Get people who withdrew money from ATM on Leggett Street morning of 28th (thief)
INSERT INTO thief (person_id)
SELECT id FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2021 AND month = 7 and day = 28
            AND atm_location LIKE "Leggett Street"
            AND transaction_type LIKE "withdraw"
    )
);

-- People who took the earliest flight on 29th (thief)
INSERT INTO thief (person_id)
SELECT id FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id IN (
        SELECT id FROM flights
        WHERE origin_airport_id IN (
            SELECT id FROM airports
            WHERE city LIKE "Fiftyville"
        )
            AND year = 2021 AND month = 7 AND day = 29
        ORDER BY hour, minute
        LIMIT 1
    )
);

-- People who called someone for less than a minute on the 28th (thief)
INSERT INTO thief (person_id)
SELECT id FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28
        AND duration < 60
);


-- Get thief
SELECT name AS thief FROM people
WHERE id IN (
-- Thief id
    SELECT person_id FROM thief
    GROUP BY person_id
    ORDER BY COUNT(id) DESC
    LIMIT 1
);

-- Get accomplice
-- People who received a call for less than a minute on the 28th (accomplice)
SELECT name AS accomplice FROM people WHERE phone_number IN (
SELECT receiver FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28
    AND duration < 60
    AND caller IN (
        -- Thief's phone number
        SELECT phone_number FROM people
        WHERE id IN (
        SELECT person_id FROM thief
        GROUP BY person_id
        ORDER BY COUNT(id) DESC
        LIMIT 1
        )
    )
);

DROP TABLE thief;
