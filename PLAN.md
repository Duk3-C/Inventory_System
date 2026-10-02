# cli implementation plan

**Flags**
    * --newlist     (create a new inventory list)
    * --ls          (list all available inventory lists)
    * --add         (create a new item in a list)
    * --name        (set item name)
    * --quant       (set item quantity)
    * --price       (set item price)
    * --help        (always necessary in case a user does not have man)


# SKU implementation

A better way for finding items and accounting them.
Based on my research, SKUs are the series of letters and numbers used for identifying items inside an inventory. Each item category should have a preset, and start counting the numbers from there. An example would look like this:
    In the case of an Electronic Device... ELEC-0000001.
    From there, the number goes up. A good practice to avoid creating a random ID number and maybe having a duplicate without noticing, as well as keeping account for what category said item is in.

---

## To Keep in Mind

It would be a good option for the item value flags to be used alongside other flags like --ls, to list all available items that match the value.
It is necessary to create a manual for the cli even if the tool is not that big.
