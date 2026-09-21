# Inventory System Program

*program is currently on version 0.4.2*

## Features

The program currently allows the user to add new items, edit them, delete them, and display all current items inside the inventory.dat file which is created after adding the first item.

---

The file ``view_inventory.py`` is currently used for displaying items inside ``inventory.dat``. This feature is also included inside the program itself, but it is a faster way of viewing the contents of the data file and debug the data.

---

## Compilation

```bash
make # To Compile
make clean # in case you want to delete all generated files
./Inventory_System # to run the compiled program
```

Currently, this only supports UNIX-based environments

---

### Future Changes

* Release v1.0 with all current functions tested and fixed (if any present errors)
* Add cli functionality
* Add a better TUI option using ncurses or any other related TUI related library that suits the program

***Note*** - These changes are future stuff that might come in posterior updates or may not (except for version 1.0 which will be done after I check on the program's functionality)
