Dynamic Ticket Pricing System (C | DLL | C++ Unit Testing | TDD)

Overview:
This project is a modular airline pricing engine built in C using a Dynamic Link Library (DLL), with a separate C++ unit testing layer following a Test-Driven Development workflow. It demonstrates structured software design, separation of concerns, and reliable testing of core business logic.
The system simulates a flight booking environment where pricing is dynamically calculated based on multiple real-world factors.

System Functionality:
The application calculates final flight booking costs by combining several pricing components. Ticket prices are adjusted using factors such as travel timing, destination, and loyalty status. Additional charges are applied for baggage based on weight and quantity, as well as optional seat selection fees. Refund calculations are also included and depend on how many days remain before departure.
All of these components are aggregated into a final booking summary that represents the complete cost of a simulated flight purchase.

Architecture:
The project is divided into three main components:
- The core pricing engine is implemented in a C-based Dynamic Link Library. This layer contains all business logic and is responsible for calculating prices, fees, and refunds. Functions are exported using standard DLL export mechanisms to allow reuse across different applications.
- The application layer is written in C and serves as the interface for user interaction. It collects input, calls functions from the DLL, and displays the final booking summary. This layer is intentionally separated from the pricing logic to maintain modularity.
- The testing layer is implemented in C++ using Microsoft’s Unit Test Framework. It directly tests the DLL functions without relying on the user interface. This allows the core pricing logic to be validated independently and ensures correctness across multiple scenarios.

Testing Approach:
The project follows a Test-Driven Development workflow. Test cases were written before or alongside feature implementation. Each test was executed to confirm expected failure before implementation, followed by development of the corresponding logic. After implementation, tests were re-run until all cases passed successfully. The final step involved refactoring to improve structure and maintainability without changing functionality.
The test suite covers ticket pricing rules, baggage fee calculations, seat selection charges, refund logic based on time before departure, and multiple edge cases.

Code Coverage:
Code coverage analysis was performed using Visual Studio instrumentation tools. The DLL was built in Debug mode with profiling enabled, and test execution was monitored to ensure that core pricing functions were actively exercised. This confirmed that the unit tests were not only passing but also meaningfully covering the underlying logic.

Technical Challenges:
During development, challenges included debugging linker errors when exporting and importing functions across the DLL boundary, ensuring correct function visibility between C and C++, and maintaining consistent behavior across different build configurations. These issues were resolved through proper header configuration, export definitions, and careful separation of interface and implementation layers.

Learning Outcomes:
This project improved my understanding of modular software design, low-level C programming, and cross-language interoperability between C and C++. It strengthened my ability to design testable systems, apply structured debugging techniques, and use Test-Driven Development to improve code reliability.
It also reinforced the importance of clean architecture, especially when separating core logic from interface and testing layers.

Future Improvements:
Planned improvements include expanding test coverage for additional edge cases, improving input validation and error handling, and refining the DLL interface for better scalability. I also plan to explore packaging the system into a more production-style architecture with enhanced documentation and extensibility.
