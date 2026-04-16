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

#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) double calculate_ticket_price(int isWeekend, int isTouristDestination, int hasLoyaltyProgram);
	__declspec(dllexport) double calculate_refund(int daysBeforeTrip, int hasLoyaltyProgram);
	__declspec(dllexport) double online_checkin(double totalWeight, int totalBags);
	__declspec(dllexport) double select_seat(int wantsWindow, int wantsFront, int wantsAisle);

#ifdef __cplusplus
}
#endif

#endif
