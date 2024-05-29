#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

/*
==========================================
DAILY TIME RECORD: A CASE STUDY
==========================================
AREVALO, MA. CRISTINA
BALGOS, KRISTINA
BESANA, PRINCES CAM
BONZA, ANGELYN
DE JUAN, CARMELA
DELA CRUZ, AVA MAUREEN
DOCE, MARC JASON
GLUMALID, ERICKA MAY
GLUMALID, ROCHELLE ANN
UNGUI, ISAAC THOMAS
REPE, RHEA MAY
VILLANUEVA, KENNEDHEN
ZONIO, ARON CHRISTIANE

*/

/*
=================================================
GLOBAL VARIABLES
Variable Definition:
TIM (Time In in Minutes)		ttl_hw (Total Hours Worked)
TOM (Time Out in Minutes)		ttl_ltm (Total Late Minutes)
TIH (Time In in Hours) 			ttl_uth (Total Undertime in Hurs)
TOH (Time Out in hours) 		ttl_utm (Total Undertime in Hours)
HW (Hours Worked)				x - counter for day
LTH (Late in Hours)				chc1 - choices
UTM (Undertime in Hours)
UTH (Undertime in Hours)
=================================================
*/

int TIM[5],TOM[5],TIH[5],TOH[5];
int HW[5], LTM[5],LTH[5],UTM[5],UTH[5];
int ttl_hw=0, ttl_lth=0, ttl_ltm=0, ttl_uth=0, ttl_utm=0;
int x;
char chc1;
/*
=================================================
FUNCTION PROTOTYPES
=================================================
*/
int gotoxy(int x, int y);
void formula(void);
void inputTIH(void);
void inputTIM(void);
void inputTOH(void);
void inputTOM(void);
void result(void);
void total (void);
void ui (void);
int newday ();

/*
=================================================
FUNCTION DEFINITIONS
=================================================
*/

/*
====================================
Function name: main
Variables used: x
Description: the function of this is to run the whole program
====================================
*/

int main()
{
    ui();
    gotoxy(39,1);
    printf("DAILY TIME RECORD(PM SCHEDULE)");
    gotoxy(38,2);
    printf("TIME SCHEDULE: 1:00 PM - 5:00 PM");
    gotoxy(3,4);
    printf("TIME IN");
    gotoxy(20,4);
    printf("TIME OUT");
    gotoxy(42,4);
    printf("HOURS WORKED");
    gotoxy(80,4);
    printf("LATES");
    gotoxy(100,4);
    printf("UNDERTIME");

    //The purpose of this function is to input the time in hour and to solve the formula.


    for (x=0; x<5; x++)
    {
        inputTIH();
        formula();
    }
    total();
    result();
    newday();
}

/*
====================================
Function Name: gotoxy
Variable Used: None
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
===========================================
Function name: inputTIH
Variables Used: x,TIH
Description: This function is for input Time in in hours
===========================================
*/

void inputTIH(void)
{
    /*This statement is for verifying if Time in in hour
    is greater than or equal to 1 and Time in in hour is
    less than or equal to 4 or Time in in hour is equal to 12*/

    gotoxy(1,20);
    printf("Please Input your TIME IN in Hours");
    gotoxy(2,6+(x*2));
    scanf("%d",&TIH[x]);

    if ((TIH[x] >= 1 && TIH[x] <= 4 )|| TIH[x] == 12)
    {
        /*This statement is for verifying if Time in in hour
        is 12 Time in in hour will convert to 0*/
        if (TIH[x] == 12)
        {
            TIH[x] = 0;
        }

        gotoxy(5,6+(x*2));
        printf(":");
        gotoxy(1,20);
        printf("                                  ");
        inputTIM();
    }
    else
    {
        gotoxy(1,20);
        printf("Invalid TIME IN input. Please try again.");
        gotoxy(2,4);
        printf("  ");
        Sleep(999);
        gotoxy(1,20);
        printf("                                            ");
        inputTIH();
    }
}

/*
=================================================
Function name: inputTIM
Variables used: TIM[], x
Description:This function is used to input time in in minutes
=================================================
*/

void inputTIM (void)
{
    gotoxy(1,20);
    printf("Please Input your TIME IN in Minutes ");
    gotoxy(7,6+(x*2));
    scanf("%d",&TIM[x]);
    // This statement can only used to time in from 0 to less than 59 minutes
    if (TIM[x] >= 0 && TIM[x]<= 59)
    {
        gotoxy(1,20);
        printf("                                       ");
        inputTOH();
    }
    else
    {
        gotoxy(1,20);
        printf("Invalid TIME IN input. Please try again.");
        gotoxy(7,x+6);
        printf("  ");
        Sleep(999);
        gotoxy(1,20);
        printf("                                             ");
        inputTIM();
    }
}

/*
=================================================
Function name: inputTOH
Variables used: TOH[],TIH[], x
Description: This function is used to input time out in hours
=================================================
*/

void inputTOH(void)
{
    gotoxy(1,20);
    printf("Please Input your TIME OUT in Hours");
    gotoxy(20,(x*2)+6);
    scanf("%d",&TOH[x]);

    // 12pm solvable value converter
    if (TOH[x] == 12)
    {
        TOH[x] = 0;
    }
    // this statement is used to time out in hours from greater or equal to  0 to less than 6pm //

    if ((TOH[x] >=0 && TOH[x] <= 6) && TOH[x] >= TIH[x])
    {
        gotoxy(22,(x*2)+6);
        printf(":");
        inputTOM();
        gotoxy(1,20);
        printf("                                  ");
    }
    else
    {
        gotoxy(1,20);
        printf("Invalid TIME OUT input. Please try again");
        gotoxy(20,x+6);
        printf("  ");
        Sleep(999);
        gotoxy(1,20);
        printf("                                          ");
        inputTOH();
    }
}

/*
====================================
Function Name: inputTOM
Variable Used: TIH, TOH, TOM, TIM, x
Description: This function is for time out in minutes input
====================================
*/

void inputTOM(void)
{
    gotoxy(1,20);
    printf("Please Input your TIME OUT in Minutes ");
    gotoxy(24,(x*2)+6);
    scanf("%d",&TOM[x]);
    /* This statement is if both TIME IN HOUR and TIME OUT is the same. In this case, the minutes
for TOM must be set between zero - fifty nine minutes and TOM is the same as or beyond the TIM  */

    if (TIH[x] == TOH[x] && ((TOM[x] >= 0 && TOM[x] <= 59) && TOM[x] >= TIM[x]))
    {
        gotoxy(1,20);
        printf("                                       ");
    }
    // This statement is to limit Time Out until 6pm
    else if (TOH[x] == 6 && TOM[x] == 0)
    {
        gotoxy(1,20);
        printf("                                       ");
    }
    /*This statement is for the TOM be set between zero - fifty nine minutes.
    If the TOH is more than TIH and before 6pm */

    else if(TOH[x] > TIH[x] && (TOH[x] < 6 && (TOM[x] >= 0 && TOM[x] <= 59)))
    {
        gotoxy(1,20);
        printf("                                      ");
    }
    else
    {
        gotoxy(1,20);
        printf("Invalid TIME OUT input. Please try again");
        gotoxy(24,x+6);
        printf("  ");
        Sleep(999);
        gotoxy(1,20);
        printf("                                            ");
        inputTOM();
    }

}

/*
===========================================
Function name: formula
Variables Used: TIH[], TOH[], TOM[], TIM[], HW[], LTH[], UTH[], UTM[], LTM[],
Description: This function is for formula.
===========================================
*/

void formula(void)
{

    //Hours Worked
    if (TIH[x]== 0 && TOH[x] == 1 || TOH[x]==0)
    {
        HW[x] = 0;
    }
    else
    {
        /* formula for time subtraction without regrouping */
        if (TOM[x] > TIM[x] || TOM[x] == TIM[x])
        {
            HW[x] = TOH[x] - TIH[x];
        }
        /* Computation for time subtraction with regrouping to get the hours worked.
    Only works if timeout in minutes is less than Time in minute.*/

        else if (TOM[x] < TIM[x])
        {
            HW[x] = ( (((TOH[x] - TIH[x])) + ((TOM[x] +60) - TIM[x])/ 60));
        }
        // Conversion of TIH (display value) into TIH (computable value) for 0 time In.
        if (TIH[x] == 0)
        {
            HW[x] = HW[x] - 1;
        }
    }

    // 4 hour hours worked limiter
    if (HW[x] >4)
    {
        HW[x] = 4;
    }
//print hours worked
    gotoxy(50,(x*2)+6);
    printf ("%d", HW[x]);
//Lates
    /*Condition to determine if the Time In is between 1pm-5pm,
    on which Timing In in these hours will be considered late */

    if (TIH[x] >= 1 && TIH[x] <= 5)
    {
        LTH[x] = TIH[x] - 1;
        LTM[x] = TIM[x];
    }
    //No lates if the input Time In is early.
    else
    {
        LTH[x] = 0;
    }

//print lates
    gotoxy(80,(x*2)+6);
    printf ("%d : %d",LTH[x],LTM[x]);
//Undertime
    // If the time out is 5pm to 6pm undertime is not counted.
    if (TOH[x] >= 5 && TOH[x] <=6)
    {
        UTH[x] = 0;
        UTM[x] = 0;
    }
    /* If the Time Out in Minutes is zero, Time Out in Hours will be subtracted from 5pm
    to compute the Undertime in Hours. Undertime in Minutes will remain zero */

    else if (TOM[x] == 0)
    {
        UTH[x] = 5 - TOH[x];
        UTM[x] = 0;
    }
    /*otherwise, if the time out in minutes is not zero, subtraction
    with regrouping will be applied in order to get the undertime*/

    else
    {
        UTH[x] = 4 - TOH[x];
        UTM[x] = 60 - TOM[x];
    }


//print undertime
    gotoxy(100,(x*2)+6);
    printf ("%d : %d", UTH[x],UTM[x]);

//Total Hours Worked
    /*computation for total hours worked. Total hours worked will be added
    by the hours worked in the current array index*/

    ttl_hw = ttl_hw + HW[x];

    //condition and computation to limit the total hours worked as 20 hours
    if (ttl_hw > 20)
    {
        ttl_hw = 20;
    }

//Total Lates
    //computation to determine total lates in hours:minute format
    ttl_lth = ttl_lth + LTH[x];
    ttl_ltm = ttl_ltm + LTM[x];

    //Condition and computation to convert extra 60 minutes into 1 hour
    if (ttl_ltm > 59)
    {
        ttl_ltm = ttl_ltm - 60;
        ttl_lth += 1;
    }


//Total Undertime
    //Computation to determine the undertime in hours:minutes format.
    ttl_uth = ttl_uth + UTH[x];
    ttl_utm = ttl_utm + UTM[x];

    //condition and computation to convert extra 60 minutes into 1 hour.
    if (ttl_utm > 59)
    {
        ttl_utm = ttl_utm - 60;
        ttl_uth += 1;
    }

}

/*
====================================
Function Name: result
Variable Used: SAL ,ttl_SAL, ttl_penh, ttl_penm
Description: This function is used to total your salary.
====================================
*/
void result(void)
{
    // Local Variable Declaration
    float SAL=100,ttl_SAL,ttl_penh,ttl_penm;

    //formula for total penalty
    ttl_penh = SAL * (ttl_uth + ttl_lth);
    ttl_penm = SAL * ((ttl_utm + ttl_ltm)/60) + (((ttl_utm + ttl_ltm) % 60)/60);
    ttl_SAL = ((SAL * ttl_hw) - (ttl_penh + ttl_penm));

    //limiter for total salaries to be not negative
    if (ttl_SAL < 0)
    {
        ttl_SAL = 0;
    }

    // This statement is to print the perspective message.
    gotoxy(1,20);
    printf (" Your Salary is %0.2f Thank you for working with us. Please come again.",ttl_SAL);
    return;
}

/*
====================================
Function Name: total
Variables Used: ttl_hw, ttl_lth, ttl_ltm, ttl_uth, ttl_utm
Description:  For this statement is for printing out the Total hours work,
total lates in hour and minutes, total under time in hours and minutes.
====================================
*/

void total(void)
{
    gotoxy(20,16);
    printf("TOTAL: ");
    gotoxy(50,16);
    printf("%d", ttl_hw);
    gotoxy(80,16);
    printf("%d : %d", ttl_lth, ttl_ltm);
    gotoxy(100,16);
    printf("%d : % d", ttl_uth, ttl_utm);
}

/*
===========================================
Function name: ui
Variables Used: x
Description: this function is to print DTR ui
===========================================
*/

void ui (void)
{
    // vertical line for table printer
    for(x=0; x<15; x++)
    {
        gotoxy(0,x+3);
        printf("|");
        gotoxy(119,x+3);
        printf("|");
        gotoxy(15,x+3);
        printf("|");
        gotoxy(30,x+3);
        printf("|");
        gotoxy(65,x+3);
        printf("|");
        gotoxy(95,x+3);
        printf("|");
    }


    // horizontal line for table printer
    for(x=0; x<120; x++)
    {
        gotoxy(x,3);
        printf("-");
        gotoxy(x,5);
        printf("-");
        gotoxy(x,7);
        printf("-");
        gotoxy(x,9);
        printf("-");
        gotoxy(x,11);
        printf("-");
        gotoxy(x,13);
        printf("-");
        gotoxy(x,15);
        printf("-");
        gotoxy(x,17);
        printf("-");
    }
}

/*
====================================
Function Name: newday
Variable Used: chc1
Description: This function is used to proceed to another day.
===================================
*/


int newday()
{
    printf("\n\tWould you proceed to another employee? Press [Y/N]");
    while(chc1 != 'Y' || chc1 != 'y' || chc1 != 'N' || chc1 != 'n')
    {
        chc1 = getch();
        if (chc1 == 'Y' || chc1 == 'y')
        {
            system("cls");
            main();
            break;
        }
        else if (chc1 == 'N' || chc1 == 'n')
        {
            exit(0);
        }
    }
}

