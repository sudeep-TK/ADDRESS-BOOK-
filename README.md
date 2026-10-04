# Address Book

A console-based **Address Book application developed in C** for managing contact information.

## Project Overview

The Address Book application allows users to manage contacts through a simple menu-driven interface. It provides functionality to add, search, edit, delete, and display contact information.

The project is implemented using **C programming** and demonstrates concepts such as structures, functions, pointers, file handling, and modular programming.

## Features

- Add a new contact
- Search for a contact
- Edit contact details
- Delete a contact
- Display all contacts
- Store contact information using file handling
- Menu-driven console interface

## Technologies Used

- **Programming Language:** C
- **Concepts:** Structures, Pointers, Functions, File Handling
- **Development Environment:** Linux / GCC

## Project Structure

```text
ADDRESS-BOOK/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
└── contacts.txt
```

## How to Run

Compile the project using GCC:

```bash
gcc main.c contact.c file.c populate.c -o addressbook
```

Run the application:

```bash
./addressbook
```

## Learning Outcomes

Through this project, I gained hands-on experience in:

- Modular programming in C
- Structures and pointers
- File handling
- Function-based program design
- Problem solving and debugging
- Building a multi-file C project
