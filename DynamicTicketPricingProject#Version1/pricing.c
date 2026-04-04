#include <stdio.h>

/* -------------------------------------------------------------
   FUNCTION DECLARATIONS
   ------------------------------------------------------------- */

   /*
    * Pricing-related calculations
    */
double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram);
double calculate_refund(int daysBeforeTrip, int hasLoyaltyProgram);
double online_checkin(double totalWeight, int totalBags);
double select_seat(int wantsWindow, int wantsFront, int wantsAisle);

/*
 * Version 2 Input validation helpers
 */
int get_valid_bool(const char* prompt);
int get_valid_int(const char* prompt);
double get_valid_double(const char* prompt);


/* -------------------------------------------------------------
   AIRLINE PRICING CONSTANTS
   These values simulate realistic airline pricing behavior.
   ------------------------------------------------------------- */

#define BASE_TICKET_PRICE 220.0

   /* Ticket price multipliers */
#define WEEKEND_SURCHARGE 1.18
#define TOURIST_SURCHARGE 1.30
#define LOYALTY_DISCOUNT 0.88

/* Refund percentages */
#define REFUND_FULL 1.00
#define REFUND_MEDIUM 0.40
#define REFUND_LOW 0.10
#define REFUND_NONE 0.00
#define LOYALTY_REFUND_BONUS 1.15

/* Baggage rules */
#define FREE_BAG_WEIGHT 8.0
#define OVERWEIGHT_FEE 85.0
#define EXTRA_BAG_FEE 55.0

/* Seat selection fees */
#define WINDOW_FEE 25.0
#define FRONT_FEE 45.0
#define AISLE_FEE 20.0


/* -------------------------------------------------------------
   FUNCTION DEFINITIONS
   ------------------------------------------------------------- */

   /*
    * calculate_ticket_price
    * -----------------------------------------------------------
    * Computes the final ticket price after applying:
    *   - weekend surcharge
    *   - tourist destination surcharge
    *   - loyalty program discount
    *
    * Parameters:
    *   isWeekend            -> 1 if flight is on a weekend, 0 otherwise
    *   isTouristDestination -> 1 if destination is high-demand, 0 otherwise
    *   hasLoyaltyProgram    -> 1 if customer is a loyalty member
    *
    * Returns:
    *   Final ticket price (double)
    *   -1 if any input is invalid
    * -----------------------------------------------------------
    */
double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram) {

    /* Validate boolean inputs */
    if ((isWeekend != 0 && isWeekend != 1) ||
        (isTouristDestination != 0 && isTouristDestination != 1) ||
        (hasLoyaltyProgram != 0 && hasLoyaltyProgram != 1)) {
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


/*
 * calculate_refund
 * -----------------------------------------------------------
 * Determines the refund percentage based on:
 *   - how early the cancellation occurs
 *   - loyalty program membership
 *
 * Refund logic:
 *   30+ days before trip  -> 100%
 *   7–29 days             -> 40%
 *   1–6 days              -> 10%
 *   0 days                -> 0%
 *
 * Loyalty members receive a bonus multiplier,
 * but refunds are capped at 100%.
 *
 * Parameters:
 *   daysBeforeTrip     -> number of days before the flight
 *   hasLoyaltyProgram  -> 1 if customer is a loyalty member
 *
 * Returns:
 *   Refund percentage (0.0 to 1.0)
 *   -1 if input is invalid
 * -----------------------------------------------------------
 */
double calculate_refund(int daysBeforeTrip, int hasLoyaltyProgram) {

    if (daysBeforeTrip < 0 ||
        (hasLoyaltyProgram != 0 && hasLoyaltyProgram != 1)) {
        return -1;
    }

    double refund = 0.0;

    if (daysBeforeTrip >= 30) {
        refund = REFUND_FULL;
    }
    else if (daysBeforeTrip >= 7) {
        refund = REFUND_MEDIUM;
    }
    else if (daysBeforeTrip >= 1) {
        refund = REFUND_LOW;
    }
    else {
        refund = REFUND_NONE;
    }

    if (hasLoyaltyProgram == 1) {
        refund *= LOYALTY_REFUND_BONUS;
        if (refund > 1.0) {
            refund = 1.0;
        }
    }

    return refund;
}


/*
 * online_checkin
 * -----------------------------------------------------------
 * Calculates baggage fees based on:
 *   - total weight of all bags combined
 *   - number of bags the passenger is checking in
 *
 * Rules:
 *   • First 8 kg are free
 *   • If total weight exceeds free allowance → OVERWEIGHT_FEE
 *   • If more than 1 bag → each additional bag costs EXTRA_BAG_FEE
 *
 * Parameters:
 *   totalWeight -> combined weight of all bags (>= 0)
 *   totalBags   -> number of bags (>= 0)
 *
 * Returns:
 *   Total baggage fee (double)
 *   -1 if inputs are invalid
 * -----------------------------------------------------------
 */
double online_checkin(double totalWeight, int totalBags) {

    if (totalWeight < 0 || totalBags < 0) {
        return -1;
    }

    double fee = 0.0;

    if (totalWeight > FREE_BAG_WEIGHT) {
        fee += OVERWEIGHT_FEE;
    }

    if (totalBags > 1) {
        fee += (totalBags - 1) * EXTRA_BAG_FEE;
    }

    return fee;
}


/*
 * select_seat
 * -----------------------------------------------------------
 * Calculates the seat selection fee based on preferences.
 *
 * Rules:
 *   • Window seat adds WINDOW_FEE
 *   • Front-row seat adds FRONT_FEE
 *   • Aisle seat adds AISLE_FEE
 *
 * Parameters:
 *   wantsWindow -> 1 if window seat requested
 *   wantsFront  -> 1 if front-row seat requested
 *   wantsAisle  -> 1 if aisle seat requested
 *
 * Returns:
 *   Total seat selection fee (double)
 *   -1 if any input is invalid
 * -----------------------------------------------------------
 */
double select_seat(int wantsWindow, int wantsFront, int wantsAisle) {

    if ((wantsWindow != 0 && wantsWindow != 1) ||
        (wantsFront != 0 && wantsFront != 1) ||
        (wantsAisle != 0 && wantsAisle != 1)) {
        return -1;
    }

    double fee = 0.0;

    if (wantsWindow == 1) fee += WINDOW_FEE;
    if (wantsFront == 1) fee += FRONT_FEE;
    if (wantsAisle == 1) fee += AISLE_FEE;

    return fee;
}


/* -------------------------------------------------------------
   VERSION 2 INPUT VALIDATION HELPERS
   ------------------------------------------------------------- */

   /*
    * get_valid_bool
    * -----------------------------------------------------------
    * Prompts the user for a boolean value (0 or 1).
    * Continues asking until a valid input is entered.
    *
    * Parameters:
    *   prompt -> message displayed to the user
    *
    * Returns:
    *   0 or 1 (int)
    * -----------------------------------------------------------
    */
int get_valid_bool(const char* prompt) {
    int value;
    int result;

    do {
        printf("%s (0 or 1): ", prompt);
        result = scanf_s("%d", &value);

        while (getchar() != '\n');

        if (result == 1 && (value == 0 || value == 1)) {
            return value;
        }

        printf("Invalid input. Please enter 0 or 1.\n");

    } while (1);
}


/*
 * get_valid_int
 * -----------------------------------------------------------
 * Prompts the user for a non-negative integer.
 * Continues asking until a valid input is entered.
 *
 * Parameters:
 *   prompt -> message displayed to the user
 *
 * Returns:
 *   A non-negative integer (int)
 * -----------------------------------------------------------
 */
int get_valid_int(const char* prompt) {
    int value;
    int result;

    do {
        printf("%s: ", prompt);
        result = scanf_s("%d", &value);

        while (getchar() != '\n');

        if (result == 1 && value >= 0) {
            return value;
        }

        printf("Invalid input. Please enter a non-negative integer.\n");

    } while (1);
}


/*
 * get_valid_double
 * -----------------------------------------------------------
 * Prompts the user for a non-negative decimal number.
 * Continues asking until a valid input is entered.
 *
 * Parameters:
 *   prompt -> message displayed to the user
 *
 * Returns:
 *   A non-negative decimal value (double)
 * -----------------------------------------------------------
 */
double get_valid_double(const char* prompt) {
    double value;
    int result;

    do {
        printf("%s: ", prompt);
        result = scanf_s("%lf", &value);

        while (getchar() != '\n');

        if (result == 1 && value >= 0) {
            return value;
        }

        printf("Invalid input. Please enter a non-negative number.\n");

    } while (1);
}
