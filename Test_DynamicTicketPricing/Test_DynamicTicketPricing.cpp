#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "../DynamicTicketPricingProject/pricing.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DynamicTicketPricingTests
{
    TEST_CLASS(DynamicTicketPricingTests)
    {
    public:

        TEST_METHOD(Test_TicketPrice_Base)
        {
            Assert::AreEqual(220.0, calculate_ticket_price(0, 0, 0), 0.01);
        }

        TEST_METHOD(Test_TicketPrice_AllModifiers)
        {
            Assert::AreEqual(280.38, calculate_ticket_price(1, 1, 1), 0.01);
        }

        TEST_METHOD(Test_Refund_Full)
        {
            Assert::AreEqual(1.00, calculate_refund(40, 0), 0.01);
        }

        TEST_METHOD(Test_Refund_ShortNotice)
        {
            Assert::AreEqual(0.10, calculate_refund(3, 0), 0.01);
        }

        TEST_METHOD(Test_Baggage_Overweight)
        {
            Assert::AreEqual(85.0, online_checkin(10, 1), 0.01);
        }

        TEST_METHOD(Test_Seat_Window)
        {
            Assert::AreEqual(25.0, select_seat(1, 0, 0), 0.01);
        }
    };
}
