#include <stdio.h>
#include "pricing.h"

/* -------------------------------------------------------------
   wait_for_enter
   ------------------------------------------------------------- */
void wait_for_enter() {
    printf("\nPress ENTER to continue...");
    while (getchar() != '\n');
}

/* -------------------------------------------------------------
   show_menu
   ------------------------------------------------------------- */
void show_menu() {
    printf("\n==========================\n");
    printf("      AIRLINE MENU\n");
    printf("==========================\n");
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
   ------------------------------------------------------------- */
void fill_passenger_info(Passenger* p) {

    p->isWeekend = get_valid_bool("Is the flight on a weekend?");
    p->isTouristDestination = get_valid_bool("Is it a tourist destination?");
    p->hasLoyaltyProgram = get_valid_bool("Does the passenger have loyalty status?");

    p->wantsWindow = get_valid_bool("Window seat?");
    p->wantsFront = get_valid_bool("Front-row seat?");
    p->wantsAisle = get_valid_bool("Aisle seat?");

    p->totalWeight = get_valid_double("Total baggage weight (kg)");
    p->totalBags = get_valid_int("Number of bags");

    p->daysBeforeTrip = get_valid_int("Days before trip");
}

/* -------------------------------------------------------------
   run_full_booking_simulation
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

            wait_for_enter();
            break;
        }

        case 2: {
            int days = get_valid_int("Days before trip");
            int loyalty = get_valid_bool("Loyalty member?");

            double refund = calculate_refund(days, loyalty);
            printf("Refund Percentage: %.2f%%\n", refund * 100);

            wait_for_enter();
            break;
        }

        case 3: {
            double weight = get_valid_double("Total baggage weight (kg)");
            int bags = get_valid_int("Number of bags");

            double fee = online_checkin(weight, bags);
            printf("Baggage Fee: $%.2f\n", fee);

            wait_for_enter();
            break;
        }

        case 4: {
            int window = get_valid_bool("Window seat?");
            int front = get_valid_bool("Front-row seat?");
            int aisle = get_valid_bool("Aisle seat?");

            double fee = select_seat(window, front, aisle);
            printf("Seat Selection Fee: $%.2f\n", fee);

            wait_for_enter();
            break;
        }

        case 6: {
            Passenger p;
            fill_passenger_info(&p);
            run_full_booking_simulation(p);
            wait_for_enter();
            break;
        }

        case 5:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice. Try again.\n");
            wait_for_enter();
        }

    } while (choice != 5);

    return 0;
}
