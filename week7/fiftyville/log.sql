-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Include all steps taken to get the solution

-- The theft took place on July 28, 2025 on Humphrey Street
SELECT description FROM crime_scene_reports WHERE day=28 AND year=2025 AND month=7 AND street='Humphrey Street';
-- Theft took place at 10:15am at the bakery. There were three witnesses.

-- Let's see the interviews that took place 7/28/2025
SELECT name, transcript FROM interviews WHERE day=28 AND year=2025 AND month=7;
-- There are seven interviews from that day
-- Ruth, Eugene and Raymond are the three witness we are looking for

------------------------------------------------------------------------
-- The thief got into a car in the bakery parking within 10 mins of the theft.


-- The thief was seen withdrawing money from
-- the ATM on Leggett Street that same morning (t < 10:15 am)


-- As the thief was leaving, they made a call for less than a minute.
-- In the call the thief said that they were palnning on taking the earliest flight out
-- the following day (7/29/2025)

-- The accomplice purchased the flight
------------------------------------------------------------------------
SELECT name FROM people WHERE license_plate in
    (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND year=2025 AND month=7 AND hour=10 AND minute BETWEEN 15 AND 25 AND activity='exit');

SELECT name FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions WHERE day=28 AND year=2025 AND month=7 AND transaction_type='withdraw' AND atm_location = 'Leggett Street'));

SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND year=2025 AND month=7 AND duration<60);

-- The thief is one of the following:
SELECT name FROM people WHERE
    id IN (SELECT person_id FROM bank_accounts WHERE account_number IN
            (SELECT account_number FROM atm_transactions WHERE day=28 AND year=2025 AND month=7 AND transaction_type='withdraw' AND atm_location LIKE 'Leggett Street'))
    AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND year=2025 AND month=7 AND hour=10 AND minute BETWEEN 15 AND 25 AND activity='exit')
    AND phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND year=2025 AND month=7 AND duration<60);


-- Let's see who the accomplice is based on the receiver's identity
-- THIEF-ACCOMPLICE POSSIBLE PAIRS
SELECT caller.name AS 'suspect thief', receiver.name AS 'suspect accomplice' FROM phone_calls JOIN people AS caller ON phone_calls.caller = caller.phone_number
    JOIN people AS receiver ON phone_calls.receiver = receiver.phone_number
    WHERE phone_calls.day=28 AND phone_calls.year=2025 AND phone_calls.month=7 AND phone_calls.duration<60 AND
    caller.id IN (SELECT person_id FROM bank_accounts WHERE account_number IN
                        (SELECT account_number FROM atm_transactions WHERE day=28 AND year=2025 AND month=7 AND transaction_type='withdraw' AND atm_location LIKE 'Leggett Street'))
    AND caller.license_plate in (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND year=2025 AND month=7 AND hour=10 AND minute BETWEEN 15 AND 25 AND activity='exit');


--The flight they were going to take
SELECT destination.city AS destination FROM airports AS origin JOIN flights ON origin.id = flights.origin_airport_id
JOIN airports AS destination ON destination.id = flights.destination_airport_id
    WHERE flights.day=29 AND flights.month=7 AND flights.year=2025 AND origin.city='Fiftyville'
    ORDER BY hour ASC, minute ASC LIMIT 1;


--Compare the passengers with the three possible thiefs and display the thief and the accomplice
SELECT thief.name AS thief, accomplice.name AS accomplice FROM people AS thief
JOIN passengers ON thief.passport_number = passengers.passport_number
JOIN phone_calls ON thief.phone_number = phone_calls.caller
JOIN people AS accomplice ON accomplice.phone_number = phone_calls.receiver
WHERE thief.id IN (SELECT person_id FROM bank_accounts WHERE
    phone_calls.day=28 AND phone_calls.year=2025 AND phone_calls.month=7 AND phone_calls.duration<60 AND
    account_number IN (SELECT account_number FROM atm_transactions WHERE day=28 AND year=2025 AND month=7 AND transaction_type='withdraw' AND atm_location LIKE 'Leggett Street')) AND
    thief.license_plate in (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND year=2025 AND month=7 AND hour=10 AND minute BETWEEN 15 AND 25 AND activity = 'exit') AND
    passengers.flight_id = (SELECT flights.id FROM airports AS origin JOIN flights ON origin.id = flights.origin_airport_id JOIN airports AS destination ON destination.id = flights.destination_airport_id  WHERE flights.day=29 AND flights.month=7 AND flights.year=2025 AND origin.city='Fiftyville' ORDER BY hour ASC, minute ASC LIMIT 1);


-- Display all final information
SELECT thief.name AS thief, accomplice.name AS accomplice, airports.city AS destination FROM people AS thief JOIN passengers ON thief.passport_number = passengers.passport_number
JOIN phone_calls ON thief.phone_number = phone_calls.caller
JOIN people AS accomplice ON accomplice.phone_number = phone_calls.receiver
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON flights.destination_airport_id = airports.id
WHERE thief.id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day=28 AND year=2025 AND month=7 AND transaction_type='withdraw' AND atm_location LIKE 'Leggett Street')) AND thief.license_plate in (SELECT license_plate FROM bakery_security_logs WHERE day=28 AND year=2025 AND month=7 AND hour=10 AND minute BETWEEN 15 AND 25 AND activity = 'exit') AND phone_calls.day=28 AND phone_calls.year=2025 AND phone_calls.month=7 AND phone_calls.duration<60 AND
passengers.flight_id = (SELECT flights.id FROM airports AS origin JOIN flights ON origin.id = flights.origin_airport_id JOIN airports AS destination ON destination.id = flights.destination_airport_id  WHERE flights.day=29 AND flights.month=7 AND flights.year=2025 AND origin.city='Fiftyville' ORDER BY hour ASC, minute ASC LIMIT 1);
