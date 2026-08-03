
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

---
## 🔑 Built-in Testing Credentials:

**Account Number**: A101

**PinCode**: 1111

<img width="1482" height="852" alt="image" src="https://github.com/user-attachments/assets/7df74e6e-36fe-4b00-bc30-82e15f8ae2a9" />

---

## 💻 Compilation and Execution

### Using standard GCC/g++ (Command Line)

To compile the solution cleanly on modern standard compilers (C++17 or higher):

Bash

```
g++ -std=c++17 "Course 08 Project 2 ATM System.cpp" -I . -o ATMSystem.exe
ATMSystem.exe
```
<img width="1482" height="852" alt="image" src="https://github.com/user-attachments/assets/c516446f-ebed-426c-8cef-dc6180ad21d0" />

---

<img width="1482" height="852" alt="image" src="https://github.com/user-attachments/assets/9e0426fd-1992-4852-9e29-83e353216fd7" />

---

<img width="1482" height="852" alt="image" src="https://github.com/user-attachments/assets/366a4288-a970-4c4d-beca-e60ac33ea2e8" />

---
<img width="1483" height="852" alt="Screenshot 2026-08-04 012817" src="https://github.com/user-attachments/assets/79abe572-3fe2-4ce2-be80-49ba000dc3b3" />
<img width="1483" height="852" alt="Screenshot 2026-08-04 012900" src="https://github.com/user-attachments/assets/7c628da8-0688-4c54-8ddf-ef265d57a1e7" />
<img width="1483" height="852" alt="Screenshot 2026-08-04 012713" src="https://github.com/user-attachments/assets/383aa3db-d5c0-4b96-93be-c86605dd6d0c" />
<img width="1483" height="852" alt="Screenshot 2026-08-04 012756" src="https://github.com/user-attachments/assets/6bdbe4d2-2321-44a4-adee-c1ca1c46dd61" />



---
## 💻 Related Projects

If you'd like to explore more of my C++ journey and see how I build data structures, algorithms, and complete applications from scratch, check out these repositories.

---

### 📚 C++ Data Data Structures & Algorithms From Scratch

A collection of advanced Data Structures and Algorithms implemented completely from scratch in C++.

This repository contains:

- Custom implementations of Linked List, Stack, Queue, Dynamic Array, String, and more.
- Every data structure includes a dedicated **test file (.cpp)** with practical examples.
- Multiple implementations of the same project to compare different approaches (Custom Data Structures vs STL).
- Solutions and projects from **Programming Advices – Algorithms & Problem Solving Level 5** course.

Most of these classes are extensions of the libraries available in **MyCppToolboxLibraries**.

https://github.com/yahiaalsebaie/CppDataStructuresFromScratch

---

### 🔧 MyCppToolboxLibraries

My personal C++ library built completely from scratch.

It contains reusable utility classes that I developed throughout my programming journey, including:

- Date & Time
- String
- Input Validation
- Utility Functions
- Period
- And many more...

Many of the projects below are built on top of these libraries.

https://github.com/yahiaalsebaie/MyCppToolboxLibraries

---

### 🏦 Bank System (OOP)

Object-Oriented implementation of a complete banking system.

Includes the Currency Exchange project.

https://github.com/yahiaalsebaie/Bank-System-OOP

---

### 🏦 Bank Management System (Procedural Programming)

The same banking system implemented using Procedural Programming.

https://github.com/yahiaalsebaie/Bank-Management-System-Cpp

---

### 🏧 ATM System

Complete ATM simulation.

https://github.com/yahiaalsebaie/ATM-System-Course08

---

### 📅 Dual Calendar System

Gregorian & Hijri Calendar Library.

Features:

- Date calculations
- Date arithmetic
- Historical dates
- Astronomical calculations
- Date differences

https://github.com/yahiaalsebaie/Dual-Calendar-System-MiladiAndHijiri

---

### 🎮 Math Game

Console Math Game.

https://github.com/yahiaalsebaie/cpp-Math-Game

---

### ✂️ Stone Paper Scissors Game

Console implementation of the classic game.

https://github.com/yahiaalsebaie/stone-paper-scissors-cpp-game

---

# ⭐ If you find this repository useful...

Please consider giving it a ⭐.

It helps others discover the project and motivates me to continue improving it.

---

