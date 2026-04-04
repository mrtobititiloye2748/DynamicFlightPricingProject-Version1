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
 * Input validation helpers
 */
int is_valid_bool(int value);
int is_valid_positive(double value);


/* -------------------------------------------------------------
   AIRLINE PRICING CONSTANTS
   These values simulate realistic airline pricing behavior.
   ------------------------------------------------------------- */

   /* Base ticket cost before any modifiers */
#define BASE_TICKET_PRICE 220.0

/* Ticket price multipliers */
#define WEEKEND_SURCHARGE 1.18          // Higher demand on weekends
#define TOURIST_SURCHARGE 1.30          // Popular destinations cost more
#define LOYALTY_DISCOUNT 0.88           // Loyalty members get a discount

/* Refund percentages based on cancellation timing */
#define REFUND_FULL 1.00                // 100% refund
#define REFUND_MEDIUM 0.40              // 40% refund
#define REFUND_LOW 0.10                 // 10% refund
#define REFUND_NONE 0.00                // No refund
#define LOYALTY_REFUND_BONUS 1.15       // Loyalty members get extra refund

/* Baggage rules */
#define FREE_BAG_WEIGHT 8.0             // Weight allowed before fees
#define OVERWEIGHT_FEE 85.0             // Fee for exceeding weight
#define EXTRA_BAG_FEE 55.0              // Fee per additional bag

/* Seat selection fees */
#define WINDOW_FEE 25.0
#define FRONT_FEE 45.0
#define AISLE_FEE 20.0


/* -------------------------------------------------------------
   FUNCTION DEFINITIONS
   ------------------------------------------------------------- */

   /*
    * calculate_ticket_price
    * ----------------------
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
    */
double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram) {

    // Validate all boolean inputs
    if (!is_valid_bool(isWeekend) ||
        !is_valid_bool(isTouristDestination) ||
        !is_valid_bool(hasLoyaltyProgram)) {
        return -1;
    }

    double price = BASE_TICKET_PRICE;

    // Weekend flights cost more due to higher demand
    if (isWeekend == 1) {
        price *= WEEKEND_SURCHARGE;
    }

    // Tourist destinations have higher pricing
    if (isTouristDestination == 1) {
        price *= TOURIST_SURCHARGE;
    }

    // Loyalty members receive a discount
    if (hasLoyaltyProgram == 1) {
        price *= LOYALTY_DISCOUNT;
    }

    return price;
}


/*
 * calculate_refund
 * ----------------
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
 */
double calculate_refund(int daysBeforeTrip, int hasLoyaltyProgram) {

    // Validate inputs
    if (daysBeforeTrip < 0 || !is_valid_bool(hasLoyaltyProgram)) {
        return -1;
    }

    double refund = 0.0;

    // Determine base refund amount
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

    // Apply loyalty bonus (capped at 100%)
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
 * --------------
 * Calculates baggage fees based on:
 *   - total weight of all bags combined
 *   - number of bags the passenger is checking in
 *
 * Rules:
 *   • First 8 kg are free (FREE_BAG_WEIGHT)
 *   • If total weight exceeds the free allowance → apply OVERWEIGHT_FEE
 *   • If more than 1 bag is checked → each additional bag costs EXTRA_BAG_FEE
 *
 * Parameters:
 *   totalWeight -> combined weight of all bags (must be >= 0)
 *   totalBags   -> number of bags (must be >= 0)
 *
 * Returns:
 *   Total baggage fee (double)
 *   -1 if inputs are invalid
 */
double online_checkin(double totalWeight, int totalBags) {

    // Validate inputs
    if (!is_valid_positive(totalWeight) || totalBags < 0) {
        return -1;
    }

    double fee = 0.0;

    // Overweight fee applies if total weight exceeds free allowance
    if (totalWeight > FREE_BAG_WEIGHT) {
        fee += OVERWEIGHT_FEE;
    }

    // First bag is free; additional bags cost EXTRA_BAG_FEE each
    if (totalBags > 1) {
        fee += (totalBags - 1) * EXTRA_BAG_FEE;
    }

    return fee;
}

/*
 * select_seat
 * -----------
 * Calculates the seat selection fee based on the passenger’s preferences.
 *
 * Rules:
 *   • Window seat adds WINDOW_FEE
 *   • Front-row seat adds FRONT_FEE
 *   • Aisle seat adds AISLE_FEE
 *
 * Notes:
 *   - All inputs must be valid booleans (0 or 1)
 *   - Multiple preferences can be selected at once
 *   - If no preferences are selected, the fee is 0
 *
 * Parameters:
 *   wantsWindow -> 1 if passenger wants a window seat
 *   wantsFront  -> 1 if passenger wants a front-row seat
 *   wantsAisle  -> 1 if passenger wants an aisle seat
 *
 * Returns:
 *   Total seat selection fee (double)
 *   -1 if any input is invalid
 */
double select_seat(int wantsWindow, int wantsFront, int wantsAisle) {

    // Validate all boolean inputs
    if (!is_valid_bool(wantsWindow) ||
        !is_valid_bool(wantsFront) ||
        !is_valid_bool(wantsAisle)) {
        return -1;
    }

    double fee = 0.0;

    // Add fee for window seat
    if (wantsWindow == 1) {
        fee += WINDOW_FEE;
    }

    // Add fee for front-row seat
    if (wantsFront == 1) {
        fee += FRONT_FEE;
    }

    // Add fee for aisle seat
    if (wantsAisle == 1) {
        fee += AISLE_FEE;
    }

    return fee;
}

/* -------------------------------------------------------------
   VERSION 2 INPUT VALIDATION HELPERS
   ------------------------------------------------------------- */

   /*
       get_valid_bool
       --------------
       Prompts the user for a boolean value (0 or 1).
       Repeats until valid input is entered.
   */
int get_valid_bool(const char* prompt) {
    int value;
    int result;

    do {
        printf("%s (0 or 1): ", prompt);
        result = scanf("%d", &value);

        while (getchar() != '\n'); // clear input buffer

        if (result == 1 && (value == 0 || value == 1)) {
            return value;
        }

        printf("Invalid input. Please enter 0 or 1.\n");

    } while (1);
}

/*
    get_valid_int
    -------------
    Prompts the user for a non-negative integer.
    Repeats until valid input is entered.
*/
int get_valid_int(const char* prompt) {
    int value;
    int result;

    do {
        printf("%s: ", prompt);
        result = scanf("%d", &value);

        while (getchar() != '\n'); // clear input buffer

        if (result == 1 && value >= 0) {
            return value;
        }

        printf("Invalid input. Please enter a non-negative integer.\n");

    } while (1);
}

/*
    get_valid_double
    ----------------
    Prompts the user for a non-negative decimal number.
    Repeats until valid input is entered.
*/
double get_valid_double(const char* prompt) {
    double value;
    int result;

    do {
        printf("%s: ", prompt);
        result = scanf("%lf", &value);

        while (getchar() != '\n'); // clear input buffer

        if (result == 1 && value >= 0) {
            return value;
        }

        printf("Invalid input. Please enter a non-negative number.\n");

    } while (1);
}

