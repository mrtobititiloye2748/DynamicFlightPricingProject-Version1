#include <stdio.h>

/* FUNCTION DECLARATIONS */
double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram);
double calculate_refund(int daysBeforeTrip, int hasLoyaltyProgram);
double online_checkin(double totalWeight, int totalBags);
double select_seat(int wantsWindow, int wantsFront, int wantsAisle);

int is_valid_bool(int value);
int is_valid_positive(double value);

/* REALISTIC AIRLINE PRICING CONSTANTS */
#define BASE_TICKET_PRICE 220.0

#define WEEKEND_SURCHARGE 1.18
#define TOURIST_SURCHARGE 1.30
#define LOYALTY_DISCOUNT 0.88

#define REFUND_FULL 1.00
#define REFUND_MEDIUM 0.40
#define REFUND_LOW 0.10
#define REFUND_NONE 0.00
#define LOYALTY_REFUND_BONUS 1.15

#define FREE_BAG_WEIGHT 8.0
#define OVERWEIGHT_FEE 85.0
#define EXTRA_BAG_FEE 55.0

#define WINDOW_FEE 25.0
#define FRONT_FEE 45.0
#define AISLE_FEE 20.0

/* VALIDATION HELPERS */
int is_valid_bool(int value) {
    return value == 0 || value == 1;
}

int is_valid_positive(double value) {
    return value >= 0;
}

/* FUNCTION DEFINITIONS */
double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram) {

    if (!is_valid_bool(isWeekend) ||
        !is_valid_bool(isTouristDestination) ||
        !is_valid_bool(hasLoyaltyProgram)) {
        return -1;
    }

    double price = BASE_TICKET_PRICE;

    if (isWeekend == 1) {
        price *= WEEKEND_SURCHARGE;
    }

    if (isTouristDestination == 1) {
        price *= TOURIST_SURCHARGE;
    }

    if (hasLoyaltyProgram == 1) {
        price *= LOYALTY_DISCOUNT;
    }

    return price;
}