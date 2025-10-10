# Bank Management System (C++ Series)  
**Author:** Shehab Ghitany  
**Language:** C++  
**Development Period:** June – August 2025  
**Total Versions:** 5  

## Overview  
This repository contains a complete C++ Bank Management System developed through five progressive stages.  
Each version adds new modules, features, and programming concepts — from basic file handling to full OOP-based.

The purpose of this series is to demonstrate:  
- Mastery of procedural and object-oriented C++.  
- Real-world application design and data management.  
- Clean modular coding, file I/O, and layered structure.  
- Professional project documentation and scalability.  

## Version Roadmap

### 01 - Base Project  
**Description:**  
The foundation of the system.  
Implements a basic client management system using text files for storage.

**Main Features:**  
- View client list.  
- Add, update, find, and delete clients.  
- File-based data persistence (Clients.txt).

**Concepts:** functions, file I/O, loops, validation.  

### 02 - Transactions Extension  
**Description:**  
Enhances the base project by introducing financial transactions.

**Main Features:**  
- Deposit and withdraw money.  
- Display total balances for all clients.  
- Automatic file update after each operation.

**Concepts:** Functions reuse, modularity, numeric validation.  

### 03 - Users & Permissions Extension  
**Description:**  
Adds user login and permission control to the system.

**Main Features:**  
- Multi-user login with username & password.  
- Role-based permissions (view, edit, delete, manage users).  
- Enhanced security for user actions.

**Concepts:** User authentication, role control, structured menus.  

### 04 - ATM Interface  
**Description:**  
Transforms the system into a functional ATM simulation that real clients can interact with.

**Main Features:**  
- Login via Account Number and Pin Code.  
- Withdraw (quick or custom), deposit, and balance check.  
- Smooth and user-friendly console interface.  
- Independent client-side operation (no admin menus).

**Concepts:** User interaction, data encapsulation, menu-driven systems.  

### 05 - OOP Advanced Version  
**Description:**  
Fully restructured version using Object-Oriented Programming.  
All screens and logic are modular classes with clear separation of concerns.

**Main Features:**  
- Complete multi-user system (login, register, roles).  
- Client CRUD, deposit/withdraw/transfer.  
- Transfer logs and login audit logs with timestamps.  
- Currency exchange module (list, update, calculator).  
- Secure (demo) password encryption.  
- 35+ header files implementing a clean modular design.

**Concepts:** Classes, encapsulation, inheritance, polymorphism, file persistence, and modular architecture.  

## Repository Structure  
```text
Bank-Management-System/
│
├── 01-Base-Project/
├── 02-Transactions-Extension/
├── 03-Users-Permission-Extension/
├── 04-ATM-Interface/
├── 05-OOP-Advanced/
│
└── README.txt  ← (this file)
```  

Each folder contains:  
- Source code (.cpp / .h)  
- Data files (Clients.txt, Users.txt, etc.)  
- A detailed README for that specific version  
- Example screenshots  

## Technologies & Tools  
- **Language:** C++  
- **IDE:** Visual Studio  
- **File Storage:** Text-based persistence  
- **Paradigms:** Procedural → OOP transition  
- **Design Focus:** Modularity, reusability, scalability  

## Learning Highlights  
Throughout the 5 stages, this project demonstrates:  
- Practical software evolution from simple functions to full OOP systems.  
- Proper class design and real-world modeling.  
- File handling, validation, error checking, and user interfaces.  
- Versioned documentation and structured development workflow.  

## Future Enhancements  
- Move from text files to a database (SQLite / MySQL).  
- Replace reversible password encryption with secure hashing (bcrypt / Argon2).  
- Add GUI (desktop or web) interface using C# or Qt.
