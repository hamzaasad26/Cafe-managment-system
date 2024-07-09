# Cafe Management System

## Overview
The Cafe Management System is a console-based application developed in C++ using Object-Oriented Programming (OOP) principles. The system allows users to manage cafe orders and track customer types. The three customer types are:

1. Students
2. Faculty
3. Non-Faculty

Each customer type has different privileges and discounts. The system includes password protection for accessing certain features.

## Features
- **User Authentication**: Secure login for different customer types.
- **Order Management**: Place, view, and manage orders.
- **Discounts**: Apply discounts based on customer type.
- **Billing**: Generate bills for orders.
- **Admin Control**: Manage menu items and view all orders.

## Classes and Structure
### Classes
- `User`: Base class for all user types. Contains common attributes and methods.
  - `Student`: Derived from `User`, includes student-specific attributes and methods.
  - `Faculty`: Derived from `User`, includes faculty-specific attributes and methods.
  - `NonFaculty`: Derived from `User`, includes non-faculty-specific attributes and methods.
- `Order`: Manages individual orders, including items and quantities.
- `Menu`: Contains available menu items and their prices.
- `CafeManagementSystem`: The main class that brings together users, orders, and the menu.

### Class Diagram
```plaintext
+------------------------+
|       User             |
+------------------------+
| - username: string     |
| - password: string     |
+------------------------+
| + login(): bool        |
+------------------------+
           |
           | (inheritance)
           v
+------------------------+     +------------------------+     +------------------------+
|      Student           |     |      Faculty           |     |     NonFaculty         |
+------------------------+     +------------------------+     +------------------------+
| - studentID: string    |     | - facultyID: string    |     | - nonFacultyID: string |
+------------------------+     +------------------------+     +------------------------+
| + login(): bool        |     | + login(): bool        |     | + login(): bool        |
+------------------------+     +------------------------+     +------------------------+

+------------------------+
|        Order           |
+------------------------+
| - orderID: int         |
| - items: list          |
| - totalAmount: double  |
+------------------------+
| + addItem(): void      |
| + calculateTotal(): double |
+------------------------+

+------------------------+
|        Menu            |
+------------------------+
| - items: map<string, double> |
+------------------------+
| + addItem(): void      |
| + getPrice(): double   |
+------------------------+

+------------------------+
| CafeManagementSystem   |
+------------------------+
| - users: list<User>    |
| - menu: Menu           |
| - orders: list<Order>  |
+------------------------+
| + run(): void          |
+------------------------+
