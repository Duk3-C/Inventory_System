import struct
with open('inventory.dat', 'rb') as f:
    data = f.read()
for i in range(0, len(data), 52):
    rec = data[i:i+52]
    if len(rec) < 52: print('Partial record at', i); break
    id_, name, qty, price = struct.unpack('<i40sif', rec)
    print('ID: ',id_, 'Name: ',name.rstrip(b'\0').decode('utf-8', errors='replace'), 'Quantity: ',qty, 'Price: $',price)
