# cli implementation plan

**Flags**
    * --newlist     (create a new inventory list)
    * --ls          (list all available inventory lists)
    * --add         (create a new item in a list)
    * --name        (set item name)
    * --quant       (set item quantity)
    * --price       (set item price)
    * --help        (always necessary in case a user does not have man)


## To Keep in Mind

It would be a good option for the item value flags to be used alongside other flags like --ls, to list all available items that match the value.
It is necessary to create a manual for the cli even if the tool is not that big.
