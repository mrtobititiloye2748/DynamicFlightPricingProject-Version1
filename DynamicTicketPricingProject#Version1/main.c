#include <stdio.h>
#include "pricing.h"

/* -------------------------------------------------------------
   show_menu
   -------------------------------------------------------------
   Displays the main menu options for the program.
   ------------------------------------------------------------- */
void show_menu() {
    printf("\n==============================\n");
    printf("      AIRLINE MENU (V2)\n");
    printf("==============================\n");
    printf("1. Calculate Ticket Price\n");
    printf("2. Calculate Refund\n");
    printf("3. Calculate Baggage Fees\n");
    printf("4. Calculate Seat Selection Fee\n");
    printf("5. Exit\n");
    printf("6. Full Booking Simulation\n");
    printf("==============================\n");
}

/* -------------------------------------------------------------
   fill_passenger_info
   -------------------------------------------------------------
   Collects all required passenger information using the
   Version 2 input validation helpers.

   Parameters:
       p -> pointer to Passenger struct to fill

   Returns:
       Nothing (struct is filled by reference)
   ------------------------------------------------------------- */
void fill_passenger_info(Passenger* p) {

    /* Ticket-related inputs */
    p->isWeekend = get_valid_bool("Is the flight on a weekend?");
    p->isTouristDestination = get_valid_bool("Is it a tourist destination?");
    p->hasLoyaltyProgram = get_valid_bool("Does the passenger have loyalty status?");

    /* Seat preferences */
    p->wantsWindow = get_valid_bool("Window seat?");
    p->wantsFront = get_valid_bool("Front-row seat?");
    p->wantsAisle = get_valid_bool("Aisle seat?");

    /* Baggage info */
    p->totalWeight = get_valid_double("Total baggage weight (kg)");
    p->totalBags = get_valid_int("Number of bags");

    /* Refund info */
    p->daysBeforeTrip = get_valid_int("Days before trip");
}

/* -------------------------------------------------------------
   run_full_booking_simulation
   -------------------------------------------------------------
   Runs all pricing calculations for a passenger and prints
   a complete summary of all charges.

   Parameters:
       p -> Passenger struct containing all user inputs

   Returns:
       Nothing (prints full breakdown)
   ------------------------------------------------------------- */
void run_full_booking_simulation(Passenger p) {

    double ticket = calculate_ticket_price(p.isWeekend, p.isTouristDestination, p.hasLoyaltyProgram);
    double refund = calculate_refund(p.daysBeforeTrip, p.hasLoyaltyProgram);
    double baggage = online_checkin(p.totalWeight, p.totalBags);
    double seat = select_seat(p.wantsWindow, p.wantsFront, p.wantsAisle);

    printf("\n==============================\n");
    printf("     FULL BOOKING SUMMARY\n");
    printf("==============================\n");

    printf("Ticket Price:          $%.2f\n", ticket);
    printf("Seat Selection Fee:    $%.2f\n", seat);
    printf("Baggage Fee:           $%.2f\n", baggage);
    printf("Refund Percentage:     %.2f%%\n", refund * 100);

    printf("==============================\n");
}

/* -------------------------------------------------------------
   main
   -------------------------------------------------------------
   Main program loop for Version 2.
   Displays a menu, collects user input, and calls the
   appropriate pricing functions.
   ------------------------------------------------------------- */
int main() {

    int choice;

    do {
        show_menu();
        choice = get_valid_int("Enter your choice");

        switch (choice) {

        case 1: {
            int weekend = get_valid_bool("Is the flight on a weekend?");
            int tourist = get_valid_bool("Is it a tourist destination?");
            int loyalty = get_valid_bool("Does the passenger have loyalty status?");

            double price = calculate_ticket_price(weekend, tourist, loyalty);
            printf("Ticket Price: $%.2f\n", price);
            break;
        }

        case 2: {
            int days = get_valid_int("Days before trip");
            int loyalty = get_valid_bool("Loyalty member?");

            double refund = calculate_refund(days, loyalty);
            printf("Refund Percentage: %.2f%%\n", refund * 100);
            break;
        }

        case 3: {
            double weight = get_valid_double("Total baggage weight (kg)");
            int bags = get_valid_int("Number of bags");

            double fee = online_checkin(weight, bags);
            printf("Baggage Fee: $%.2f\n", fee);
            break;
        }

        case 4: {
            int window = get_valid_bool("Window seat?");
            int front = get_valid_bool("Front-row seat?");
            int aisle = get_valid_bool("Aisle seat?");

            double fee = select_seat(window, front, aisle);
            printf("Seat Selection Fee: $%.2f\n", fee);
            break;
        }

        case 6: {
            Passenger p;
            fill_passenger_info(&p);
            run_full_booking_simulation(p);
            break;
        }

        case 5:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);

    return 0;
}
