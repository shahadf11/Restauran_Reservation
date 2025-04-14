#include <iostream>
#include <string>
#include <ctime>
using namespace std;

const int MAX_TABLES_PER_DATE = 2;
const int MAX_PEOPLE_PER_TABLE = 6;

struct Reservation {
    int receipt, numPeople;
    string name, date, time, contactNum, status;
    double payment;
    Reservation *next;
};

class Restaurant_Reservation_System {
private:
    Reservation *head;
    int receiptCounter;
    const double RESERVATION_FEE = 150.0; // Constant for reservation fee
    string openingTime; // Opening time of the restaurant
    string closingTime; // Closing time of the restaurant

public:
    Restaurant_Reservation_System(string opening, string closing) {
        head = NULL;
        receiptCounter = 0;
        openingTime = opening;
        closingTime = closing;
    }

    string getOpeningTime() const { return openingTime; }
    string getClosingTime() const { return closingTime; }

    void addReservation(string name, string date, string time, int numPeople, string contactNum);
    void searchReservation(int receipt);
    void cancelReservation(int receipt);
    void makePayment(int receipt, double billAmount);
    void showAllReservations();
    void updateDateTime(int receipt, string newDate, string newTime);
    void calculateDailyIncome(string date);
    bool isTimeFormatValid(string time);
    bool isTimeWithinOperatingHours(string reservationTime);
    bool isValidDate(string date);
};


bool Restaurant_Reservation_System::isValidDate(string date) {
    // Check the date format
    if (date.length() != 10) {
        return false; // Invalid format
    }
    // Extract year, month, and day from the input date string
    int year, month, day;
    if (sscanf(date.c_str(), "%d/%d/%d", &year, &month, &day) != 3) {
        return false; // Invalid format
    }
    // Check if the extracted year, month, and day are within valid ranges
    if (year < 2024 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false; // Date is outside the desired range
    }
   
    return true; // Date is valid
}


bool Restaurant_Reservation_System::isTimeFormatValid(string time) {
    // Check if time is in HH:MM format
    if (time.length() != 5 || time[2] != ':')
        return false;

    for (int i = 0; i < 5; ++i) {
        if (i == 2)
            continue; // Skip ':'
        if (!isdigit(time[i]))
            return false;
    }
    return true;
}



bool Restaurant_Reservation_System::isTimeWithinOperatingHours(string reservationTime) {
    // Parse reservation time
    int resHour = stoi(reservationTime.substr(0, 2));
    int resMinute = stoi(reservationTime.substr(3, 2));

    // Parse opening and closing hours
    int openHour = stoi(openingTime.substr(0, 2));
    int closeHour = stoi(closingTime.substr(0, 2));

    if (resHour < openHour || resHour > closeHour)
        return false;
    if (resHour == openHour && resMinute < stoi(openingTime.substr(3, 2)))
        return false;
    if (resHour == closeHour && resMinute > stoi(closingTime.substr(3, 2)))
        return false;

    return true;
}





void Restaurant_Reservation_System::addReservation(string name, string date, string time, int numPeople, string contactNum) {
 //Checks if the provided time adheres to the expected format (HH:MM). If not, it prints an error message and returns early.

    if (!isTimeFormatValid(time)) {
        cout << "Invalid time format. Please use HH:MM format." << endl;
        return;
    }
//Verifies whether the reservation time falls within the restaurant operating hours.
// If not, it displays an error message indicating the valid operating hours. 
    if (!isTimeWithinOperatingHours(time)) {
        cout << "Reservation time is outside of operating hours (" << getOpeningTime() << " - " << getClosingTime() << ")." << endl;
        return;
    }

//Ensures that the number of people requested does not exceed the maximum allowed per table. If it does, an error message is shown.

    if (numPeople > MAX_PEOPLE_PER_TABLE) {
        cout << "Sorry, maximum " << MAX_PEOPLE_PER_TABLE << " people per table allowed." << endl;
        return;
    }
    
/*Initializes a counter for tables booked on the specified date.
terates through the existing reservations (current) and increments tablesBookedForDate if 
a reservation with the same date and a status of a Confirmed is found.*/
    int tablesBookedForDate = 0;
    Reservation* current = head;
    while (current != nullptr) {
        if (current->date == date && current->status == "Confirmed") {
            tablesBookedForDate++;
        }
        current = current->next;
    }
/*Ensures that the total number of tables booked for the given date does not exceed the maximum allowed.
If it does, an error message is displayed.*/

    if (tablesBookedForDate >= MAX_TABLES_PER_DATE) {
        cout << "Sorry, all tables are booked for " << date << "." << endl;
        return;
    }
    
/*Creating a New Reservation*/
/*Sets various properties for the reservation, including receipt, name, date, time, numPeople, 
contactNum, status, and payment.*/

    Reservation* newReservation = new Reservation;
    //This line assigns a unique receipt number to the new reservation.
    newReservation->receipt = ++receiptCounter;
    newReservation->name = name;
    newReservation->date = date;
    newReservation->time = time;
    newReservation->numPeople = numPeople;
    newReservation->contactNum = contactNum;
    newReservation->status = "Confirmed";
    newReservation->payment = 0.0;
     newReservation->next = nullptr;
     
     
/*Adding the New Reservation to the Linked List*/
/*If the linked list is empty (head == nullptr), the new reservation becomes the head.
Otherwise, it traverses the linked list to find the last reservation (current->next == nullptr)
and appends the new reservation to the end.*/
    if (head == nullptr) {
        head = newReservation;
    } else {
        Reservation* current = head;
        //This line iterates through the linked list until current points to the last reservation.
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newReservation;
    }
    cout << "Reservation added successfully. Receipt number: " << newReservation->receipt << endl;
}



void Restaurant_Reservation_System::searchReservation(int receipt) { 
    // Find a specific reservation by receipt number 
    Reservation *current = head;
    while (current != NULL) { 
        if (current->receipt == receipt) { 
            // View reservation information
            cout << "Receipt: " << current->receipt << endl;
            cout << "Name: " << current->name << endl;
            cout << "Date: " << current->date << endl;
            cout << "Time: " << current->time << endl;
            cout << "Number of People: " << current->numPeople << endl;
            cout << "Contact Number: " << current->contactNum << endl;
            cout << "Status: " << current->status << endl; 
            cout << "----------------------------------------"<<endl;
            return; 
        } 
        current = current->next;
    } 
    cout << "Reservation not found ! " <<endl; 
}
void Restaurant_Reservation_System::cancelReservation(int receipt) {
    // Initialize pointers to traverse the linked list
    Reservation *current = head;
    Reservation *prev = nullptr;
    
    // Traverse the linked list to find the reservation with the given receipt number
    while (current != nullptr && current->receipt != receipt ) {
        prev = current;
        current = current->next;
    }

    // If the reservation with the given receipt number is found
    if (current != nullptr) {
        // Delete the node
        if (prev == nullptr) {
            // If the node to be deleted is the head
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "Reservation with receipt number " << receipt << " has been cancelled and deleted." << endl;

        // Decrease the total tables booked for the date of this reservation
        string canceledDate = current->date;
        Reservation* dateChecker = head;
        int bookedTables = 0;
        // Traverse the list to count the number of tables booked for the cancelled date
        while (dateChecker != nullptr) {
            if (dateChecker->date == canceledDate && dateChecker->status == "Confirmed") {
                bookedTables++;
            }
            dateChecker = dateChecker->next;
        }

        cout << "Updated total tables available for " << canceledDate << ": " << MAX_TABLES_PER_DATE - bookedTables << endl;
    } else {
        cout << "Reservation with receipt number " << receipt << " not found." << endl;
    }
}




// This member function of the class Restaurant_Reservation_System handles payment processing for reservations.
// It takes two parameters: receipt (an integer representing the receipt number of the reservation) and billAmount (a double representing the total bill amount).
void Restaurant_Reservation_System::makePayment(int receipt, double billAmount) {
    // Start with the first reservation in the linked list
    Reservation* current = head;
    
    // Iterate through the linked list until reaching the end
    while (current != nullptr ) {
        // Check if the receipt number and status of the current reservation match the provided receipt number and if the status is "Confirmed"
        if (current->receipt == receipt && current->status == "Confirmed") {
            // Calculate the remaining balance after deducting the reservation fee from the total bill amount
            double remainingBalance = billAmount - RESERVATION_FEE;

            // Print payment details
            cout << "Payment details for Receipt " << receipt << ": " << endl;
            cout << "Total bill amount: " << billAmount << endl;
            cout << "Reservation fee: " << RESERVATION_FEE << endl;
            cout << "Remaining balance: " << remainingBalance << endl;

            // Update the payment information of the current reservation
            current->payment = billAmount;
            
            // Change the status of the reservation to "Completed"
            current->status = "Completed";
            
            // Exit the function after processing the payment
            return;
        }
        // Check if the reservation is cancelled
        else if (current->status == "Cancelled") {
            // Print a message indicating that the receipt is cancelled
            cout << "The receipt is Cancelled" << endl;
            
            // Return immediately if the reservation is cancelled without processing the payment
            return;
        }
        // Move to the next reservation in the linked list
        else {
            current = current->next;
        }
    }
    
    // Print a message if no matching reservation with the provided receipt number is found or if the reservation is not confirmed
    cout << "Reservation with receipt number " << receipt << " not found or not confirmed." << endl;
}




// This member function of the class Restaurant_Reservation_System updates the date and time of a reservation identified by its receipt number.
// It takes three parameters: receipt (an integer representing the receipt number of the reservation), newDate (a string representing the new date for the reservation), and newTime (a string representing the new time for the reservation).
void Restaurant_Reservation_System::updateDateTime(int receipt, string newDate, string newTime) {
    // Start with the first reservation in the linked list
    Reservation* current = head;
    
    // Iterate through the linked list until reaching the end
    while (current != nullptr) {
        // Check if the receipt number of the current reservation matches the provided receipt number
        if (current->receipt == receipt) {
            // Update the date and time of the current reservation
            current->date = newDate;
            current->time = newTime;
            
            // Print a message indicating successful update of the reservation
            cout << "Reservation with receipt number " << receipt << " has been updated." << endl;
            
            // Exit the function after updating the reservation
            return;
        }
        
        // Move to the next reservation in the linked list
        current = current->next;
    }
    
    // Print a message if no matching reservation with the provided receipt number is found
    cout << "Reservation with receipt number " << receipt << " not found." << endl;
}




void Restaurant_Reservation_System::showAllReservations() {   
    Reservation* current = head;
    cout << "All Reservations:" << endl;
    // Check if there are no reservations
    if (current == nullptr) {
        cout << "No reservations found." << endl;
        return;
    }
    //Display all reservations
    while (current != nullptr) {
        cout << "Receipt: " << current->receipt << endl;
        cout << "Name: " << current->name << endl;
        cout << "Date: " << current->date << endl;
        cout << "Time: " << current->time << endl;
        cout << "Number of People: " << current->numPeople << endl;
        cout << "Contact Number: " << current->contactNum << endl;
        cout << "Status: " << current->status << endl; 
        cout << "----------------------------------------"<<endl;
        current = current->next;    
    }
}




// Function to calculate the total income for a specific date
void Restaurant_Reservation_System::calculateDailyIncome(string date) { 
    double income = 0.0; // initialize total income to zero

    Reservation* current = head; // Start at the beginning of the reservation list
    // Check if the reservation matches the given date and has been completed
    while (current != nullptr) { 
     // Check if the reservation matches the given date and has been completed
        if (current->date == date && current->status == "Completed") { 
            income += current->payment; // Add the payment amount to the total income
        } 
        current = current->next; // Move to the next reservation
    } 
      // Print the total income for the specified date
    cout << "Total income for " << date << ": " << income << " SAR\n" ; 
}





int main() {
    
    Restaurant_Reservation_System rrs("09:00", "21:00");//working hours in our Restaurant 
    int choice, receipt;
    string name, date, time, contactNum;
    int numPeople;
    double billAmount;

    //menu with options for the user to choose from
    do {
        cout <<endl<< "Welcome to the Restaurant Reservation System (RRS)..." << endl;
        cout << "Please choose from the following menu: " << endl;
        cout << "1- Add reservation." << endl;
        cout << "2- Search for a reservation." << endl;
        cout << "3- Make a payment." << endl;
        cout << "4- Cancel a reservation." << endl;
        cout << "5- Show all reservations." << endl;
        cout << "6- Update reservation date and time." << endl;
        cout << "7- Calculate daily income." << endl;
        cout << "8- Exit." << endl;
        cin >> choice;

        switch (choice) {
    case 1:
         cout << "Enter name: ";
         cin >> name;
   
       do {
          cout << "Enter date (YYYY/MM/DD): ";
          cin >> date;
   
          if (!rrs.isValidDate(date)) {
              cout << "Invalid date format or out-of-range day. Please enter a valid date in the format YYYY/MM/DD." << endl;
              continue;
            }
      
          cout << "Enter time (HH:MM): ";
          cin >> time;
   
          //Check if the time in the correcr format
          if (!rrs.isTimeFormatValid(time)) {
              cout << "Invalid time format. Please use HH:MM format." << endl;
           continue;
           } 
         // if the time in the correcr format Check if it in the working hours range
          else if (!rrs.isTimeWithinOperatingHours(time)) {
              cout << "Reservation time is outside of operating hours (" << rrs.getOpeningTime() << " - " << rrs.getClosingTime() << ")." << endl;
              continue;
           }
      
          cout << "**Note that the maximum number of people allowed at one table is 6" << endl;
          cout << "Enter number of people : ";
          cin >> numPeople;
   
          if (numPeople > MAX_PEOPLE_PER_TABLE) {
              cout << "Sorry, maximum 6 people per table allowed." << endl;
              continue;
          }
   
          cout << "Enter contact number : ";
             cin >> contactNum;
          //add reservation
          rrs.addReservation(name, date, time, numPeople, contactNum);
          break; // Exit the loop after successful reservation
          }
       while (true);
         break;

    case 2:
         cout << "Enter receipt number: ";
         cin >> receipt;
         rrs.searchReservation(receipt);
         break;
      
      
    case 3:
         cout << "Enter receipt number: ";
         cin >> receipt;
         cout << "Enter total bill amount: ";
         cin >> billAmount; // Asking user to enter total bill payment
         rrs.makePayment(receipt, billAmount);
           break;

    case 4:
         cout << "Enter receipt number: ";
         cin >> receipt;
         rrs.cancelReservation(receipt);
         break;
         
    case 5:
         rrs.showAllReservations();
         break;
         
    case 6:
         cout << "Enter receipt number: "<< endl;
         cin >> receipt ;
         cout << "Enter new date: "<< endl;
         cin >>  date ;
         cout << "Enter receipt number, new date, and new time: "<< endl;
         cin >> time;
         if (!rrs.isValidDate(date)) {
          cout << "Invalid date format. Please enter date in the format YYYY/MM/DD." << endl;
          break;
          }
    
         // Validate time format
         if (!rrs.isTimeFormatValid(time)) {
             cout << "Invalid time format. Please use HH:MM format." << endl;
             break;
         }
    
         // Validate if time is within operating hours
         if (!rrs.isTimeWithinOperatingHours(time)) {
             cout << "Reservation time is outside of operating hours (" << rrs.getOpeningTime() << " - " << rrs.getClosingTime() << ")." << endl;
             break;
         }
         //if all true do case 6
          rrs.updateDateTime(receipt, date, time);
          break;
    
    case 7:
        cout << "Enter date to calculate daily income: ";
        cin >> date;
        rrs.calculateDailyIncome(date);
        break;
        
    case 8:
        cout << "Exiting the system." << endl;
        break;
        
    default:
         cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
