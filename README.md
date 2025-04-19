# Restauran_Reservation
A console-based C++ application that allows users to manage restaurant reservations. The system is
 interactive and provides various options to add, search, update, cancel reservations, and calculate daily
 income.It also validates time and date formats and ensures that reservations fall within the restaurant's
 working hours.


 Features:

- Add reservation (with validation for time, date, and number of people)
- Search reservation by receipt number
- Make a payment
- Cancel reservation
- View all reservations
- Update reservation date and time
- Calculate daily income from reservations
- Exit the syste


 Working Hours:

 The system is initialized with restaurant working hours:
 Restaurant_Reservation_System rrs("09:00", "21:00");
 All reservations are checked to ensure the selected time is within this range.


Main Menu Options:

 1. Add reservation
 2. Search for a reservation
 3. Make a payment
 4. Cancel a reservation
 5. Show all reservations
 6. Update reservation date and time
 7. Calculate daily income
 8. Exit the program


Validations Implemented:

- Date Format: Must be in YYYY/MM/DD.
- Time Format: Must be in HH:MM (24-hour format).
- Time Range: Must fall within restaurant hours (09:00 to 21:00).
- People Limit: Max 6 people per table.
- Tables Limit: Max 2 reservations per date (can be modified using MAX_TABLES_PER_DATE).

