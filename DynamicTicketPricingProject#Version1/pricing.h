#ifndef PRICING_H
#define PRICING_H

/* -------------------------------------------------------------
   Passenger Struct
   -------------------------------------------------------------
   Holds all user input data required for the full booking
   simulation in Version 2.
   ------------------------------------------------------------- */
typedef struct {
    int isWeekend;
    int isTouristDestination;
    int hasLoyaltyProgram;

    int wantsWindow;
    int wantsFront;
    int wantsAisle;

    double totalWeight;
    int totalBags;

    int daysBeforeTrip;
} Passenger;

/* -------------------------------------------------------------
   Pricing Function Declarations
   ------------------------------------------------------------- */
double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram);
double calculate_refund(int daysBeforeTrip, int hasLoyaltyProgram);
double online_checkin(double totalWeight, int totalBags);
double select_seat(int wantsWindow, int wantsFront, int wantsAisle);

/* -------------------------------------------------------------
   Version 2 Input Validation Helpers
   ------------------------------------------------------------- */
int get_valid_bool(const char* prompt);
int get_valid_int(const char* prompt);
double get_valid_double(const char* prompt);

#endif
