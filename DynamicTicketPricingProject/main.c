#include <stdio.h>
#include "pricing.h"

/* -------------------------------------------------------------
   GLOBAL DATA FOR VERSION 3
   ------------------------------------------------------------- */

Passenger passengers[MAX_PASSENGERS];
int passengerCount = 0;

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
    printf("\n==============================\n");
    printf("      AIRLINE MENU (V3)\n");
    printf("==============================\n");
    printf("1. Calculate Ticket Price\n");
    printf("2. Calculate Refund\n");
    printf("3. Calculate Baggage Fees\n");
    printf("4. Calculate Seat Selection Fee\n");
    printf("5. Exit\n");
    printf("6. Add Passenger (Full Booking)\n");
    printf("7. Save Bookings to File\n");
    printf("8. Load Bookings from File\n");
    printf("9. Show Total Revenue\n");
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
   save_bookings_to_file
   ------------------------------------------------------------- */
void save_bookings_to_file(const char* filename) {
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, filename, "w");

    if (err != 0 || fp == NULL) {
        printf("Error: could not open file for writing.\n");
        return;
    }

    fprintf(fp, "%d\n", passengerCount);

    for (int i = 0; i < passengerCount; i++) {
        Passenger p = passengers[i];
        fprintf(fp, "%d %d %d %d %d %d %.2f %d %d\n",
            p.isWeekend,
            p.isTouristDestination,
            p.hasLoyaltyProgram,
            p.wantsWindow,
            p.wantsFront,
            p.wantsAisle,
            p.totalWeight,
            p.totalBags,
            p.daysBeforeTrip
        );
    }

    fclose(fp);
    printf("Bookings saved to file '%s'.\n", filename);
}

/* -------------------------------------------------------------
   load_bookings_from_file
   ------------------------------------------------------------- */
void load_bookings_from_file(const char* filename) {
    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, filename, "r");

    if (err != 0 || fp == NULL) {
        printf("Error: could not open file for reading.\n");
        return;
    }

    int count;
    if (fscanf_s(fp, "%d", &count) != 1 || count < 0 || count > MAX_PASSENGERS) {
        printf("Error: invalid data in file.\n");
        fclose(fp);
        return;
    }

    Passenger temp;
    int loaded = 0;

    for (int i = 0; i < count; i++) {
        int read = fscanf(fp, "%d %d %d %d %d %d %lf %d %d",
            &temp.isWeekend,
            &temp.isTouristDestination,
            &temp.hasLoyaltyProgram,
            &temp.wantsWindow,
            &temp.wantsFront,
            &temp.wantsAisle,
            &temp.totalWeight,
            &temp.totalBags,
            &temp.daysBeforeTrip
        );

        if (read == 9) {
            passengers[loaded++] = temp;
        }
        else {
            printf("Warning: skipping invalid record in file.\n");
        }
    }

    passengerCount = loaded;
    fclose(fp);
    printf("Loaded %d passenger(s) from file '%s'.\n", passengerCount, filename);
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
            if (passengerCount >= MAX_PASSENGERS) {
                printf("Passenger list is full. Cannot add more.\n");
            } else {
                Passenger p;
                fill_passenger_info(&p);
                run_full_booking_simulation(p);
                passengers[passengerCount++] = p;
            }

            wait_for_enter();
            break;
        }

        case 7: {
            save_bookings_to_file("bookings.txt");
            wait_for_enter();
            break;
        }

        case 8: {
            load_bookings_from_file("bookings.txt");
            wait_for_enter();
            break;
        }

        case 9: {
            double total = calculate_total_revenue(passengers, passengerCount);
            printf("Total Revenue for all passengers: $%.2f\n", total);
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
