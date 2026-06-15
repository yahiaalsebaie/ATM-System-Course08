
# ATM System Simulator 🏧 (Programming Advices - Course 08)

An advanced, console-based Automated Teller Machine (ATM) simulator implemented in modern C++. This project serves as a standalone client self-service interface that interacts with a shared banking ledger (`Clients.txt`), built as part of the **Programming Advices** roadmap mentored by Eng. Mohammed Abu-Hadhoud.

This repository is designed as an extension and operates in direct synchronization with the core [yahiaalsebaie/Bank-Management-System-Cpp](https://github.com/yahiaalsebaie/Bank-Management-System-Cpp) repository: *A multi-phase Bank Management System in C++ featuring multi-user authentication, granular permissions matrix, transactional ledger, and system audit logs.*

---

## 📌 Project Overview

This architecture separates administrative management from client operations. While the backend administrative tools handle user permissions and client creation, this **ATM System** provides clients with direct, secured access via their unique **Account Number** and **PIN Code**. 

All transactional data scales across a flat-file database, ensuring data integrity and real-time ledger updates.

---

## 🏗️ Directory & Repository Structure

The project layout follows a standard header-only library architecture combined with standard compiler outputs (Visual Studio & GCC compatible):

``` text
.
├── Course 08 Project 2 ATM System.cpp      # Main Application Entry Point
├── Course 08 Project 2 ATM System.sln      # Visual Studio Solution File
├── Clients.txt                             # Shared Database Ledger
├── MyBankDataLib.h                         # Core Bank Business Logic & Parsing
├── MyInputLib.h                            # Bulletproof Input Validation Utilities
├── MyStringLib.h                           # String Tokenization & Parsing Toolkit
├── MyDateLib.h                             # Gregorian Calendar Logic & System Date
├── MyHijriDateLib.h                        # Tabular Hijri Calendar & Dynamic Alignment
├── MyArrayLib.h                            # Custom Array Manipulation Functions
├── MyVectorLib.h                           # Vector Handling and Transformation
├── MyMathLib.h                             # Mathematical Utility Operations
├── MyUtilityLib.h                          # Generic Helper Functions
├── MyMathLib.h                             # Algorithmic Math Implementations
└── .gitignore                              # Git exclusion rules (build artifacts)
```

## 🔒 Simulated Database & Security Compliance

- **Data Isolation**: Files like `Clients.txt` and `Users.txt` function strictly as local mock databases using custom field layout delimiters (`#//#`).
    
- No real financial credentials, actual banking numbers, or production-grade Personal Identifiable Information (PII) are processed or stored.
    
---

## 🚀 Key Features

- **Secure Client Login:** Authenticates credentials directly from `Clients.txt` with defensive session locking.
    
- **Quick Withdraw:** One-click standardized withdrawals ($20, $50, $100, $200, $500, $1000) mapped to balance verification routines.
    
- **Normal Withdraw & Deposit:** Custom transaction inputs engineered with strict logical barriers preventing overdrafts or invalid numerical inputs.
    
- **Dynamic Balance Inquiry:** Real-time checking of current account balances.
    
- **Dual-Calendar Integration (`MyDateLib` & `MyHijriDateLib`):** Displays real-time synchronized dates showing the Gregorian system date mapped alongside a dynamically-aligned Hijri weekday calculation.
    

## 🛠️ Technical Highlights & Clean Code Architecture

This project strictly adheres to professional software engineering practices:

- **Separation of Concerns (SoC):** Logic is deeply decoupled into independent, header-only reusable libraries (`MyInputLib`, `MyStringLib`, etc.).
    
- **Defensive Programming:** Employs advanced standard input stream validation via `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')` wrapped inside safe compilation guards (`#define NOMINMAX`) to counter terminal buffer corruptions in Windows environments.
    
- **DRY Principle (Don't Repeat Yourself):** Reuses the absolute indexing routines across both calendar libraries for uniform calculation layouts.

    

## 💻 Compilation and Execution

### Using standard GCC/g++ (Command Line)

To compile the solution cleanly on modern standard compilers (C++17 or higher):

Bash

```
g++ -std=c++17 "Course 08 Project 2 ATM System.cpp" -I . -o ATMSystem.exe
./ATMSystem.exe
```
```

