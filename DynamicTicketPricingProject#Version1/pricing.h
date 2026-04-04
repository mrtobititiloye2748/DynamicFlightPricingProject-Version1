#ifndef PRICING_H
#define PRICING_H

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

double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram);
double calculate_refund(int daysBeforeTrip, int hasLoyaltyProgram);
double online_checkin(double totalWeight, int totalBags);
double select_seat(int wantsWindow, int wantsFront, int wantsAisle);

int is_valid_bool(int value);
int is_valid_positive(double value);

#endif#
