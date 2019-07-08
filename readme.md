# Contact Management System

An application written in C that can add, update, delete, search, and sort a contact list.

## Prerequisites
Install the Minimalist GNU for Windows

## Running the Application

Compile the source and header files.
```
g++ AmaApp.cpp Date.cpp ErrorState.cpp Perishable.cpp Product.cpp Utilities.cpp ms5.cpp -std=c++11 -o productapp
```

Run the executable file.
```
./productapp.exe
```

Example
```
Disaster Aid Supply Management Program
--------------------------------------
1- List products
2- Search product
3- Add non-perishable product
4- Add perishable product
5- Add to product quantity
6- Delete product
7- Sort products
0- Exit program
> 1
------------------------------------------------------------------------------------------------
| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |
|-----|---------|------------------|------------|---------|-----|--------|--------|------------|
|   1 |     122 | Bucket           | units      |   10.32 | yes |    150 |    300 |
|   2 |     124 | Corn             | kg         |    4.10 |  no |      0 |    140 | 2020/04/03 |
|   3 |    8476 | Disaster Reli... | package    | 1033.99 |  no |      1 |      3 |
|   4 |    1596 | Milk             | litre      |    3.99 |  no |     98 |    150 | 2019/05/04 |
|   5 |    3456 | Paper Cups       | package    |    5.99 | yes |     38 |     90 |
|   6 |    1234 | Royal Gala Ap... | kg         |    4.42 |  no |     10 |    332 | 2019/05/16 |
|   7 |    1212 | Salted Butter    | package    |    5.99 |  no |    108 |    750 | 2019/05/03 |
|   8 |    5678 | Sugar            | kg         |    6.78 |  no |      0 |    200 |
|   9 |     111 | Water Container  | units      |   11.32 | yes |    500 |   5000 |
------------------------------------------------------------------------------------------------
|                                                      Total cost of support ($): |   10518.38 |
------------------------------------------------------------------------------------------------

Press Enter to continue...

Disaster Aid Supply Management Program
--------------------------------------
1- List products
2- Search product
3- Add non-perishable product
4- Add perishable product
5- Add to product quantity
6- Delete product
7- Sort products
0- Exit program
> 2
Please enter the product SKU: 122

                         Sku: 122
                        Name: Bucket
                       Price: 10.32
             Price after Tax: 11.66
          Quantity Available: 150 units
             Quantity Needed: 300 units

Press Enter to continue...
````