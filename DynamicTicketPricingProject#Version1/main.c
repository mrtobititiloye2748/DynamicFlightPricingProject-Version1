#include <stdio.h>
#include "pricing.c"   // temporary include for testing

int main() {

    // Simple test calls
    printf("Ticket price example: %.2f\n",
        calculate_ticket_price(1, 1, 1));

    printf("Refund example: %.2f\n",
        calculate_refund(10, 1));

    printf("Baggage fee example: %.2f\n",
        online_checkin(12.0, 2));

    printf("Seat fee example: %.2f\n",
        select_seat(1, 0, 1));

    return 0;
}