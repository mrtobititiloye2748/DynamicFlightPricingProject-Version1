#include <stdio.h>
#include "pricing.h"

/* -------------------------------------------------------------
   PRICING FUNCTIONS
   ------------------------------------------------------------- */

__declspec(dllexport)
double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram) {

    if ((isWeekend != 0 && isWeekend != 1) ||
        (isTouristDestination != 0 && isTouristDestination != 1) ||
        (hasLoyaltyProgram != 0 && hasLoyaltyProgram != 1)) {
        return -1;
    }

    double price = 220.0;

    if (isWeekend == 1) price *= 1.18;
    if (isTouristDestination == 1) price *= 1.30;
    if (hasLoyaltyProgram == 1) price *= 0.88;

    return price;
}

__declspec(dllexport)
double calculate_refund(int daysBeforeTrip, int hasLoyaltyProgram) {

    if (daysBeforeTrip < 0 ||
        (hasLoyaltyProgram != 0 && hasLoyaltyProgram != 1)) {
        return -1;
    }

    double refund = 0.0;

    if (daysBeforeTrip >= 30) refund = 1.00;
    else if (daysBeforeTrip >= 7) refund = 0.40;
    else if (daysBeforeTrip >= 1) refund = 0.10;
    else refund = 0.00;

    if (hasLoyaltyProgram == 1) {
        refund *= 1.15;
        if (refund > 1.0) refund = 1.0;
    }

    return refund;
}

__declspec(dllexport)
double online_checkin(double totalWeight, int totalBags) {

    if (totalWeight < 0 || totalBags < 0) {
        return -1;
    }

    double fee = 0.0;

    if (totalWeight > 8.0) fee += 85.0;
    if (totalBags > 1) fee += (totalBags - 1) * 55.0;

    return fee;
}

__declspec(dllexport)
double select_seat(int wantsWindow, int wantsFront, int wantsAisle) {

    if ((wantsWindow != 0 && wantsWindow != 1) ||
        (wantsFront != 0 && wantsFront != 1) ||
        (wantsAisle != 0 && wantsAisle != 1)) {
        return -1;
    }

    double fee = 0.0;

    if (wantsWindow == 1) fee += 25.0;
    if (wantsFront == 1)  fee += 45.0;
    if (wantsAisle == 1)  fee += 20.0;

    return fee;
}

/* -------------------------------------------------------------
   INPUT VALIDATION
   ------------------------------------------------------------- */

int get_valid_bool(const char* prompt) {
    int value, result;

    do {
        printf("%s (1 = Yes, 0 = No): ", prompt);
        result = scanf_s("%d", &value);

        while (getchar() != '\n');

        if (result == 1 && (value == 0 || value == 1)) return value;

        printf("Invalid input. Try again.\n");
    } while (1);
}

int get_valid_int(const char* prompt) {
    int value, result;

    do {
        printf("%s: ", prompt);
        result = scanf_s("%d", &value);

        while (getchar() != '\n');

        if (result == 1 && value >= 0) return value;

        printf("Invalid input. Try again.\n");
    } while (1);
}

double get_valid_double(const char* prompt) {
    double value;
    int result;

    do {
        printf("%s: ", prompt);
        result = scanf_s("%lf", &value);

        while (getchar() != '\n');

        if (result == 1 && value >= 0) return value;

        printf("Invalid input. Try again.\n");
    } while (1);
}
