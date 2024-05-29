#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <stdbool.h>
#include <conio.h>



/*
======================================
JOLLIBEE: A CASE STUDY
======================================
AREVALO, MA CRISTINA
BALGOS, KRISTINA
BESANA, PRINCES BESANA
BONZA, ANGELYN
DE JUAN, CARMELA
DELA CRUZ, AVA MAUREEN
DOCE, MARC JASON
GLUMALID, ERICKA MAY
GLUMALID, ROCHELLE ANN
REPE, RHEA MAY
UNGUI, ISAAC THOMAS
VILLANUEVA, KENNEDHEN
ZONIO, ARON CHRISTIANE
*/


/*
=====================================
GLOBAL VARIABLES
=====================================
*/

char product[10][20] = {"Hamburger", "French Fries", "Coke",
                        "Sundae", "Spaghetti", "Fried Chicken",
                        "Mango Pie", "Jolly Hotdog", "Super Value Meal",
                        "Burger Steak"
                       };
int price[10] = {25,30,15,35,50,80,30,45,160,50};
int stock[10] = {100,100,100,100,100,100,100,100,100,100};
int qty[10];

// orderchecker to avoid individual order repetition
int orderchecker[10];

int subtotal[10], total, grandtotal, pment, change;

// SB = Stock Beginning
// SE = Stock End
int SB[10] = {100,100,100,100,100,100,100,100,100,100}, SE[10] = {100,100,100,100,100,100,100,100,100,100}, sold[10], sales[10];
// counters
int x, xx = 1 , x1, x2, x3;

// choice values
int chc;
char chc1;

// bool values for loop breakers, repeat stoppers, and orderender
bool breaker = false, breaker2 = false, orderender = false;
bool repeatstopper = false, repeatstopper1 = false;

/*
=====================================
FUNCTION PROTOTYPES/DECLARATION
=====================================
*/

int gotoxy(int x, int y);
void ordermenu(void);
void orders(void);
void orderloop(void);

void productorder(void);
void endorder(void);
void endday(void);
void cancelorder(void);
void payment(void);
void paymentinput(void);
void inventory(void);
void newday(void);
void orderboxui(void);
void inventoryboxui(void);


/*
======================================
FUNCTION DEFINITION
======================================
*/

/*
====================================
Function Name: main
Variable Used: none
Description: The purpose of Function is to run the whole program.
====================================
*/


void main(void)
{
    orderboxui();
    ordermenu();
    return;
}

/*
====================================
Function Name: gotoxy
Variable Used: x, y
Description: The purpose of this is to display in respective coordinates for y axis is for horizontal and x axis is for vertical. This is to run gotoxy for GNU/GCC Compiler
====================================
*/

COORD coord = {0,0};
int gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    return 0;
}

/*
====================================
Function Name:void ordermenu
Variable Used: order no. , Products, price, stocks, x, xx
Function used: orders();
Description: This function is used  when you  order  products.
====================================
*/


void ordermenu(void)
{
    gotoxy(1,0);
    printf("ORDER NO. %d", xx);
    gotoxy(3,2);
    printf("Products");
    gotoxy(19,2);
    printf("Price  Stocks");

    // For product display
    for(x=0; x<10; x++)
    {
        gotoxy(0,x+4);
        printf("[%d]%s", x+1, product[x]);
    }

    // For price display
    for(x=0; x<10; x++)
    {
        gotoxy(20,x+4);
        printf("@ %d",price[x]);
    }

    // For stock display
    for(x=0; x<10; x++)
    {
        gotoxy(27,x+4);
        printf("   ");
        gotoxy(27,x+4);
        printf("%d",stock[x]);
    }

    gotoxy(0,14);
    printf("[11]End Order/Exit");

    gotoxy(0,15);
    printf("[12]Cancel Order");

    orders();

    return;
}

/*
======================================
Function Name: orders
Variable used:
x, x2, subtotal, qty, orderchecker, total, change, repeatstopper, repeatstopper1, orderender
Description: This function is for printing out the headers and initializing orders
======================================
*/


void orders(void)
{
    // this statement is for initialize and reset the variables for the next order
    for (x=0; x<10; x++)
    {
        orderchecker[x] = 0;
        subtotal[x] = 0;
        qty[x] = 0;
    }
    total = 0;
    change = 0;
    x2 = 0;

    orderender = false;
    repeatstopper = false;
    repeatstopper1 = false;

    //Header for Orders UI
    gotoxy(40,0);
    printf("No.");
    gotoxy(50,0);
    printf("Product");
    gotoxy(70,0);
    printf("Quantity");
    gotoxy(90,0);
    printf("Price");
    gotoxy(100,x2);
    printf("Subtotal");

    orderloop();

    return;
}

/*
====================================
Function Name: orderloop
Variable Used: choice , products, price, stocks, chc, x2
Description: This function is used to order specific products or choices from the order menu.
====================================
*/


void orderloop(void)
{
    //choice input
    for ( ; x2<11 ; x2++)
    {
        gotoxy(1,16);
        printf("Enter Choice:");
        scanf("%d",&chc);

        // if statement for product choices
        if (chc < 11)
        {
            // If stock is already sold to zero, it will print the Invalid message
            if (stock[chc-1] == 0)
            {
                gotoxy(14,16);
                printf("     ");
                gotoxy(32,17);
                printf("No Stocks! Please order a different product!");
                Sleep(999);
                gotoxy(32,17);
                printf("                                                  ");
                qty[chc-1] = 0;
                orderloop();
            }

            // If orderchecker is equal to one, it will print the invalid message
            if (orderchecker[chc-1] == 1)
            {
                gotoxy(14,16);
                printf("     ");
                gotoxy(32,17);
                printf("Already Ordered! Please order a different product.");
                Sleep(999);
                gotoxy(32,17);
                printf("                                                  ");
                orderloop();
            }
            else
            {
                productorder();
            }
        }

        //End order and end day choice
        else if (chc==11)
        {
            if (x2 == 0)
            {
                endday();
                x2--; // this statement is for not to proceed to the next product number

            }

            else
            {
                endorder();

                if (orderender == true);
                {
                    gotoxy(32,17);
                    orders();
                }
            }

            if (breaker == true)
            {
                break;
            }

        }
        //Cancel order choice
        else if (chc==12)
        {
            if (x2 == 0)
            {
                // this statement is when the order product is zero, it will print the invalid message
                gotoxy(32,17);
                printf("Can't cancel since there are no orders!");
                Sleep(999);
                gotoxy(32,17);
                printf("                                       ");
                gotoxy(14,16);
                printf("     ");
                orderloop();
            }
            else
            {
                cancelorder();
            }
            // breaker is for breaking the loop.
            if (breaker == true)
            {
                ordermenu();
            }

        }
        else
        {
            gotoxy(14,16);
            printf("     ");
            gotoxy(32,17);
            printf("Invalid choice!");
            Sleep(999);
            gotoxy(32,17);
            printf("               ");
            orderloop();
        }
    }
    return;
}
/*
======================================
Function Name: productorder
Variable Used: x2,chc, product[],price[],qty[],stock[],subtotal[],repeatstopper,orderchecker
Description: This function is for ordering the individual product with quantity and computing subtotal
======================================
*/

void productorder(void)
{
    //bug fixer for an unknown bug where bool variables are forcibly turning to false
    if (repeatstopper == true  || repeatstopper1 == true)
    {
        repeatstopper == true;
        repeatstopper1 == true;
    }
    else if (repeatstopper == false || repeatstopper1 == false)
    {
        // choice value index number converter
        chc--;
    }

    //order details
    gotoxy(40,x2+1);
    printf("%d", x2+1);
    gotoxy(50,x2+1);
    printf("%s", product[chc]);
    gotoxy(90,x2+1);
    printf("%d",price[chc]);
    gotoxy(70,x2+1);
    scanf("%d",&qty[chc]);

    //individual order canceller
    if(qty[chc] == 0)
    {
        gotoxy(33,x2+1);
        printf("                                                                                       ");
        gotoxy(14,16);
        printf("     ");
        orderloop();
    }

    //condition for quantity greater than stocks
    else if (qty[chc] > stock[chc])
    {
        gotoxy(32,17);
        printf("Invalid quantity! Please Try Again!");
        Sleep(999);
        gotoxy(32,17);
        printf("                                   ");
        gotoxy(70,x2+1);
        printf("              ");
        repeatstopper = true;
        productorder();
    }
    //conditions for correct input
    else
    {
        subtotal[chc] = price[chc] * qty[chc];
        orderchecker[chc] = 1 ;

        gotoxy(100,x2+1);
        printf("%d", subtotal[chc]);

        gotoxy(14,16);
        printf("     ");
    }
    return;
}


/*
==================================
Function name: endorder
Variable Used: x2, chc1, orderender
Description: This function is used when you want to end your order.
==================================
*/

void endorder(void)
{
    gotoxy(32,17);
    printf("Are you sure you want to end order? Press [Y/N]");
    //non-Y and non-N character canceller
    while(chc1 != 'Y' || chc1 != 'y' || chc1 != 'N' || chc1 != 'n')
    {
        chc1 = getch();
        // this statement if you press Y your order will be end.
        if (chc1 == 'Y' || chc1 == 'y')
        {
            gotoxy(14,16);
            printf("     ");
            gotoxy(32,17);
            printf("                                               ");
            payment();

            orderender = true;
            break;
        }
        // this statement is used to verify if you don't want to end your order.
        else if (chc1 == 'N' || chc1 == 'n')
        {
            x2 -=1;
            gotoxy(14,16);
            printf("     ");
            gotoxy(32,17);
            printf("                                                              ");
            x2++;
            orderloop();
        }
    }
    return;
}

/*
======================================
Function name: endday
Variables used: chc1
Description: This function is used for ending the day.
======================================
*/

void endday(void)
{
    gotoxy(32,17);
    printf("Are you sure you want to end day? Press [Y/N]");

    //non-Y and non-N character canceller
    while(chc1 != 'Y' || chc1 != 'y' || chc1 != 'N' || chc1 != 'n')
    {
        chc1 = getch();
        // this statement if you press Y the day will be end.
        if (chc1 == 'Y' || chc1 == 'y')
        {
            gotoxy(14,16);
            printf("     ");
            gotoxy(32,17);
            printf("                                                        ");
            inventory();
            newday();
        }
        //  this statement is used to verify if you don’t want to exit the day.
        else if (chc1 == 'N' || chc1 == 'n')
        {
            gotoxy(14,16);
            printf("     ");
            gotoxy(32,17);
            printf("                                                         ");
            break;
        }
    }

    return;
}

/*
======================================
Function name: cancelorder
Variables used: chc, chc1, x2, x3, breaker
Description: This function is used to cancel the orders of customers.
======================================
*/

void cancelorder(void)
{
    gotoxy(32,17);
    printf("Are you sure you want to cancel order? Press [Y/N]");
    //non-Y and non-N character canceller
    while(chc1 != 'Y' || chc1 != 'y' || chc1 != 'N' || chc1 != 'n')
    {
        chc1 = getch();
        // this statement if you press Y the products/orders will  be cancel and to restart the orders
        if (chc1 == 'Y' || chc1 == 'y')
        {
            // this statement is used to clear preexisting orders for cancelling

            for (x3=0; x3<=x2; x3++)
            {
                gotoxy(33,x3);
                printf("                                                                                       ");
            }
            gotoxy(14,16);
            printf("     ");
            gotoxy(32,17);
            printf("                                                                         ");
            breaker = true;
            break;
        }
        // this statement Is used to verify if you don't want to cancel your orders
        else if (chc1 == 'N' || chc1 == 'n')
        {
            gotoxy(14,16);
            printf("     ");
            gotoxy(32,17);
            printf("                                                                 ");
            x2-- ;
            break;
        }
    }
    return;
}

/*
==================================
Function Name: payment
Variable Used: total, subtotal[],  x
Description: This function is used to pay orders.
==================================
*/

void payment(void)
{
    // total formula
    for (x=0; x<10; x++)
    {
        total = total + subtotal[x];
    }

    paymentinput();
    return;
}
/*
==================================
Function Name: Payment input
Variable used: xx, pment, total
Description: This function is used to input the amount to pay.
=================================
*/

void paymentinput(void)
{
    gotoxy(80,13);
    printf("Total is: %d ",total);
    gotoxy(80,14);
    printf("Enter Payment: ");
    gotoxy(95,14);
    scanf("%d",&pment);

    //payment minus total equals to change.
    if (pment >= total)
    {

        change= pment - total;

        //formula for stock and stock end

        for (x=0; x<10; x++)
        {
            stock[x] = stock[x] - qty[x];
            SE[x] = SE[x] - qty[x];
        }

        gotoxy(80,15);
        printf("Change: %d",change);
        gotoxy(32,17);
        printf("Press any key to continue!");
        getch();

        //order clearer
        for(x=0; x<18; x++)
        {
            gotoxy(33,x);
            printf("                                                                                       ");
        }

        gotoxy(32,17);
        printf("                          ");
        xx++; // Order No. incrementer



        ordermenu();

    }

    else
    {
        gotoxy(32,17);
        printf("Insufficent payment!");
        Sleep(999);
        gotoxy(32,17);
        printf("                    ");
        paymentinput();
    }
    return;
}

/*
======================================
Function name: Inventory
Variables Used: SB[ ], SE[ ] sold[ ], sales[ ] grandtotal, price[ ], product [ ],
Description: This is for printing out the inventory which includes product, stock beginning, stock end, sold, sales, and grand total
====================================
*/

void inventory(void)
{
    inventoryboxui();

    // formula to compute stock beginning, and sales and grand total initializer
    for (x=0; x<10; x++)
    {
        SB[x] = SB[x] - sold[x];
        sales[x] = 0;
    }
    grandtotal = 0;

    // formula to solve sold, sales, and grandtotal
    for (x=0; x<10; x++)
    {
        sold[x] = SB[x] - SE[x];
        sales[x] = sold[x] * price[x];
        grandtotal += sales[x];
    }


    gotoxy(5,18);
    printf("PRODUCT");
    gotoxy(20,18);
    printf("SB");
    gotoxy(28,18);
    printf("SE");
    gotoxy(35,18);
    printf("SOLD");
    gotoxy(46,18);
    printf("SALES");
    gotoxy(58,18);
    printf("PRODUCT");
    gotoxy(79,18);
    printf("SB");
    gotoxy(88,18);
    printf("SE");
    gotoxy(98,18);
    printf("SOLD");
    gotoxy(110,18);
    printf("SALES");

    //This statement is used to display products
    for(x=0; x<12; x++)
    {
        if(x<6)
        {
            gotoxy (4,x+19);
            printf("%s", product[x]);
        }
        if(x>5)
        {
            gotoxy (58,x+13);
            printf("%s", product[x]);
        }

    }

    //This statement is used to display stock beginning
    for(x=0; x<10; x++)
    {
        if(x<6)
        {
            gotoxy(20,x+19);
            printf("%d",SB[x]);
        }
        if(x>5)
        {
            gotoxy (78,x+13);
            printf("%d",SB[x]);
        }
    }


      //This statement is used to display stock ending
    for(x=0; x<10; x++)
    {
        if(x<6)
        {
            gotoxy(28,x+19);
            printf("%d",SE[x]);
        }
        if(x>5)
        {
            gotoxy(88,x+13);
            printf("%d",SE[x]);
        }

    }


      //This statement is used to display sold
    for(x=0; x<10; x++)
    {
        if(x<6)
        {
            gotoxy(36,x+19);
            printf("%d",sold[x]);
        }
        if(x>5)
        {
            gotoxy(98,x+13);
            printf("%d",sold[x]);
        }

    }


    //This statement is used to display sales
    for(x=0; x<10; x++)
    {
        if(x<6)
        {
            gotoxy(44,x+19);
            printf("%d",sales[x]);
        }
        if(x>5)
        {
            gotoxy(108,x+13);
            printf("%d",sales[x]);
        }
    }

    gotoxy (95,23);
    printf("Grand Total: %d", grandtotal);


    return;
}


/*
====================================
Function Name: newday
Variable Used: chc1,x
Description: This function is used to proceed to another day.
===================================
*/

void newday(void)
{
    gotoxy(32,17);
    printf("Would you proceed to another day? Press [Y/N]");
    //non-Y and non-N character canceller
    while(chc1 != 'Y' || chc1 != 'y' || chc1 != 'N' || chc1 != 'N')
    {
        chc1 = getch();
        if (chc1 == 'Y' || chc1 == 'y')
        {
            gotoxy(10,16);
            printf("    ");
            gotoxy(32,17);
            printf("                                                               ");
            for (x=0; x<19; x++)
            {
                gotoxy(0,x+18);
                printf("                                                                                                                             ");
            }
            main();
            break;
        }
        else if (chc1 == 'N' || chc1 == 'n')
        {
            printf("\n\n\n\n\n\n\n");
            exit(0);
        }
    }
    return;
}

/*
===========================================
Function name: Order Box UI
Variables Used: x
Description: this function is to print order box UI
===========================================
*/
void orderboxui(void)
{
    // This statement is used to print vertical lines of the UI.
    for (x=0; x<17; x++)
    {
        gotoxy(32, x);
        printf("|");
    }

    // This statement is used to print horizontal lines of the U
    for (x=0; x<32; x++)
    {
        gotoxy(x,17);
        printf("-");
    }

    return;
}

/*
===========================================
Function named: Inventory Box UI
Variables Used: x
Description: This function is to print inventory box UI.
===========================================
*/
void inventoryboxui(void)
{
    // This statement is used to print horizontal lines of the UI.
    for (x=0; x<120; x++)
    {
        gotoxy(x,18);
        printf("-");
        gotoxy(x,25);
        printf("-");
    }

    // This statement is used to print vertical lines of the UI.

    for (x=0; x<8; x++)
    {
        gotoxy(0, x+18);
        printf("|");
        gotoxy(119, x+18);
        printf("|");
    }
    return;
}

