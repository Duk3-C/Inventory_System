# Inventory System Program

*program is currently on version 1.2*

## Features

The program currently allows the user to add new items, edit them, delete them, and display all current items inside the inventory.dat file which is created after adding the first item.

---

The file ``view_inventory.py`` is currently used for displaying items inside ``inventory.dat``. This feature is also included inside the program itself, but it is a faster way of viewing the contents of the data file and debug the data.

---

## Installation

To have the tui version of the program, do the following...

```bash
# Through https
git clone --single-branch --branch stable-tui https://github.com/Duk3-C/Inventory_System.git 

# Through SSH
git clone --single-branch --branch stable-tui git@github.com:Duk3-C/Inventory_System.git
```

```bash
# To Compile
cd Inventory_System/
make

# in case you want to delete all generated files
make clean

# to run the compiled program
./inventory
```

Currently, this only supports UNIX-based environments

---

## New Changes

Added a new way of identifying and managing items through SKU. These have a category abbreviation at the start of the series of digits (e.g. ELEC for electronic devices, etc.), followed by a dash or the start of the series of digits. These series consist of a minimum of 6 digits, but can be a different amount depending on the user's need.

---

### Future Changes

* Add cli functionality
* Add new TUI interface

***Note*** - These changes are future stuff that might come in posterior updates or may not (except for version 1.0 which will be done after I check on the program's functionality)
