//Fernando Henrique Zavalloni Proto

/*------------------------------------------
  File   : projectIPC144.c
  Purpose: Create functions of the project
  Author : Fernando Henrique Zavalloni Proto
  Date   : 2016-12-05
  ------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>

// SYMBOLIC CONSTANTS

#define MAX_ITEM_NO 20
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
#define MAX_LENGTH 20
#define LINEAR 1
#define FORM 0

// global - struct Item

struct Item
{
  double price;
  int    sku;
  int    isTaxed;
  int    quantity;
  int    minQuantity;
  char   name[MAX_LENGTH+1]; // 1 for delimiter
};

// global - TAX rate //

const double TAX = 0.13;

// prototypes

void        printWelcome       ( void                                              );
void        printGoodbye       ( void                                              );
void        printTitle         ( void                                              );
void        printFooter        ( double gTotal                                     );
void        clearKeyboard      ( void                                              );
void        pause              ( void                                              );
int         getInt             ( void                                              );
double      getDouble          ( void                                              );
int         getIntLimited      ( int lowerLimit, int upperLimit                    );
double      getDoubleLimited   ( double lowerLimit, double upperLimit              );
int         getYesOrNo         ( void                                              );  
int         getMenuChoice      ( void                                              ); 
void        runInventorySystem ( void                                              );  
double      totalAfterTax      ( struct Item item                                  );
int         isQuantityLow      ( struct Item *p                                    );
struct Item enterItem          ( int sku                                           );
void        displayItem        ( struct Item *p, int linear                        );
void        listItems          ( struct Item item[], int noOfItems                 );
int         locateItem         ( struct Item item[], int noOfRecs, int sku, int *p );
int         loadItems          ( struct Item item[], char fileName[]               );
void        search             ( struct Item item[], int noOfRecs                  );
void        updateItem         ( struct Item *p                                    );


// MAIN FUNCTION

int main ( void )
{
  printWelcome();
  runInventorySystem();
  printGoodbye();
  return 0;
}


// FUNCTIONS

/* --------------------------------------------------
   function  : printWelcome
   purpose   : print the welcome message
   parameter : void
   result    : void
   --------------------------------------------------*/
void printWelcome ( void )
{
  // print the welcome message
  printf ( "\n---=== Welcome to Fernando's Grocery Inventory System ===---\n\n" );
}


/* --------------------------------------------------
   function  : printGoodbye
   purpose   : print the goodbye message
   parameter : void
   result    : void
   --------------------------------------------------*/
void printGoodbye ( void )
{
  // print the goodbye message
  printf ( "\n---=== Good Bye! Fernando's Grocery Inventory System ===---\n\n" );
}


/* --------------------------------------------------
   function  : printTitle
   purpose   : print the title
   parameter : void
   result    : void
   --------------------------------------------------*/
void printTitle ( void )
{
  // print the title
  printf ( "Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n" );
  printf ("----+---+--------------------+--------+-----+-----+-----+------------|---\n" );
   
}


/* --------------------------------------------------
   function  : printFooter
   purpose   : Print the footer and the grand total
   parameter : grand total (double)
   result    : void
   --------------------------------------------------*/
void printFooter ( double gTotal )
{
  // print the footer
  printf ( "--------------------------------------------------------+----------------\n" );
  // print the grand total if it is greater than 0
  if ( gTotal > 0 )
    printf ("                                           Grand Total: |%12.2lf\n", gTotal );
}


/* --------------------------------------------------
   function  : clearKeyboard
   purpose   : clear the keyboard until the user type
               <ENTER>
   parameter : void
   result    : void
   --------------------------------------------------*/
void clearKeyboard ( void )
{
  char key;
  // ask the user a character while it is not <ENTER>
  do
  {
   scanf ( "%c", &key );
  } while ( key != '\n' );
}


/* --------------------------------------------------
   function  : pause
   purpose   : print a message and pause the program
   parameter : void
   result    : void
   --------------------------------------------------*/
void pause ( void )
{
  // pause the program until the user type enter
  printf ( "Press <ENTER> to continue..." );
  clearKeyboard ();
}


/* --------------------------------------------------
   function  : getInt
   purpose   : get an integer value
   parameter : void
   result    : return the value when it is integer
   --------------------------------------------------*/
int getInt ( void )
{
  int value;
  char nl = 'x'; 
  
  // repeat the process while the character input is not new line
  while ( nl != '\n' )
  {
     //get an integer value from the use 
     scanf ( "%d%c", &value, &nl );
    
     //print a message of invalid number if the character is not new line 
     if ( nl != '\n' )
     {
       clearKeyboard ();
       printf( "Invalid integer, please try again: " ); 
     }   
  }
  return value;
}


/* --------------------------------------------------
   function  : getDouble
   purpose   : get a double value
   parameter : void
   result    : return the value when it is double
   --------------------------------------------------*/
double getDouble ( void )
{
  double value;
  char nl = 'x';

  // repeat the process while the character input is not new line
  while ( nl != '\n' )
  {
    // get a double value from the use 
    scanf ( "%lf%c", &value, &nl );
  
    // print a message of invalid number if the character is not new line 
    if ( nl != '\n' )
    {
      clearKeyboard ();
      printf ( "Invalid number, please try again: " ); 
    } 
  }
  return value;
}


/* --------------------------------------------------
   function  : getIntLimited
   purpose   : get an integer value between 2 numbers
   parameter : lower limit(int) and upper limit(int)
   result    : return the value when it is an integer
               and it is between the limits
   --------------------------------------------------*/
int getIntLimited ( int lowerLimit, int upperLimit )
{
  int value;

  // get the value from the user, repeat until it is between the lower and the upper
  do
  { 
  //get the value
  value = getInt ();

  //if value is not between lower and upper print a message
  if ( value < lowerLimit || value > upperLimit )
    printf ( "Invalid value, %d <= value <= %d: ", lowerLimit, upperLimit );
  } while ( value < lowerLimit || value > upperLimit );
  
  return value;
}


/* --------------------------------------------------
   function  : getDoubleLimited
   purpose   : get a double value between 2 numbers
   parameter : lower limit(double) and upper limit(double)
   result    : return the value when it is double and it
               is between the limits
   --------------------------------------------------*/
double getDoubleLimited ( double lowerLimit, double upperLimit )
{
  double value;

  // get the value from the user, repeat until it is between the lower and the upper
  do 
  { 
    //get the value
    value = getDouble();

    //if value is not between lower and upper print a message
    if ( value < lowerLimit || value > upperLimit )
       printf( "Invalid value, %lf <= value <= %lf: ", lowerLimit, upperLimit );
  } while ( value < lowerLimit || value > upperLimit );
  
  return value;
}


/* --------------------------------------------------
   function  : getYesOrNo
   purpose   : get an yes or no answer
   parameter : void
   result    : return true for yes and false for no
   --------------------------------------------------*/
int getYesOrNo ( void )
{
  char ch;
  int ret = false;

  // ask the anwser of a question and repeat it ultil the answer is Y, y, N or n
  do
  {
    //ask a char
    scanf ( "%c", &ch );
    clearKeyboard ();

    //if it is not Y, y, N or n print a helpful message
    if ( ch != 'Y' ) 
      if ( ch != 'y' )
        if  ( ch != 'N' ) 
          if ( ch != 'n' )
            printf ( "Only (Y)es or (N)o are acceptable: " );
  } while ( ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n' );
  
  if ( ch == 'Y' || ch == 'y' )
    ret = true;
  return ret;
}


/* --------------------------------------------------
   function  : getMenuChoice
   purpose   : Print a list of options and ask one of
   			       them
   parameter : void
   result    : return choice
   --------------------------------------------------*/
int getMenuChoice ( void )
{
  int choice;

  //print the options of menu
  printf( "1- List all items\n" );
  printf( "2- Search by SKU\n" );
  printf( "3- Checkout an item\n" );
  printf( "4- Stock an item\n" );
  printf( "5- Update Item\n" );
  printf( "6- Delete item\n" );
  printf( "7- Search by name\n" );
  printf( "0- Exit program\n" );
  printf( "> " );

  //ask the user a choice
  choice = getIntLimited ( 0,7 );

  return choice;
}


/* --------------------------------------------------
   function  : runInventorySystem
   purpose   : run inventory system (core function)
   parameter : void
   result    : void
   --------------------------------------------------*/
void runInventorySystem ( void )
{
  int option, done = 0, sku, itemLoc, index, retLoadItem, answerYesorNo;
  struct Item item [ MAX_ITEM_NO ];
  
  printf ( "Loading inventory data...\n" );
  retLoadItem = loadItems ( item, "inventory.dat" );
  
  // if load data successfully
  if ( retLoadItem == 1 )
  {
    pause ();
    do
    {
      // list the options of menu and ask the user one of them 
      option = getMenuChoice ();

      // get a message depending on menu choice
      switch ( option )
      {  
         // call listItems to list all items of the inventory
         case 1 :  listItems ( item, MAX_ITEM_NO ); pause (); break;
         
         // call search to find a product
         case 2 :  search ( item, MAX_ITEM_NO ); pause (); break;
         case 3 :  printf ( "NOT IMPLEMENTED\n" ); pause (); break;
         case 4 :  printf ( "NOT IMPLEMENTED\n" ); pause (); break;
         
         // update an item data
         case 5 :  printf ( "Please enter a the SKU: " ); 
                   sku = getIntLimited ( SKU_MIN, SKU_MAX ); 
                   itemLoc = locateItem ( item, MAX_ITEM_NO, sku, &index );
                   if ( itemLoc == 1 )
                   {
                     printf ( "Current data:\n" );
                     
                     // call displayItem to display the current data of an item
                     displayItem ( &item[index], FORM );
                     
                    // call update to update an item data
                     updateItem( &item[index] );
                   }
                   else
                     printf( "Item not found!\n" );
                   pause ();
                   break;
         case 6 :  printf( "NOT IMPLEMENTED\n"); pause (); break;
         case 7 :  printf( "NOT IMPLEMENTED\n"); pause (); break;
         
         // ask the user to exit the program
         case 0 :  printf( "Exit the program? (Y)es/(N)o: " );  
                   
                   // set the answer as the return of function getYesOrNo
                   answerYesorNo = getYesOrNo ();
                   
                   // if answer is 1 (Yes) end the program
                   if  ( answerYesorNo == 1 )
                     option = done;
                   
                   // else return to the menu choice
                   else
                     option = 1;
                   break;
      } 
    } while ( option != done );
  }
}
  



/* --------------------------------------------------
   function  : totalAfterTax
   purpose   : Calculate total inventory price after tax
   parameter : struct Item item
   result    : totalPrice
   --------------------------------------------------*/
double totalAfterTax ( struct Item item )
{
  double totalPrice;

  // if product is taxed
  if ( item.isTaxed == 1 )
  
  // calculate the total price, multiplying the item price by quantity and 1 plus the sales tax
    totalPrice = ( item.price * item.quantity ) * ( 1 + TAX );
  
  // else the total price is the item price times the quantity
  else
    totalPrice = ( item.price * item.quantity );

  return totalPrice;
}


/* --------------------------------------------------
   function  : isQuantityLow
   purpose   : Verify if an item quantity is less than 
               the minumum quantity
   parameter : struct Item item
   result    : lowQuantity
   --------------------------------------------------*/
int isQuantityLow ( struct Item *p )
{
  bool lowQuantity;

  // if quantity is lower than minimum quantity, assign true
  if ( p -> quantity < p -> minQuantity )
    lowQuantity = true;
  
  // else assign false
  else
    lowQuantity = false;

  return lowQuantity;
}


/* --------------------------------------------------
   function  : enterItem 
   purpose   : enter item data
   parameter : int sku
   result    : item
   --------------------------------------------------*/
struct Item enterItem ( int sku )
{
  struct Item item;
  
  // ask the SKU
  printf ( "        SKU: %d\n", sku );
  
  //assign the item sku to the sku entered 
  item.sku = sku;
  
  // ask the name
  printf ( "       Name: " );
  scanf ( "%20[^\n]", item.name );
  clearKeyboard ();
  
  // ask the price
  printf ( "      Price: " );
  item.price = getDouble(); 
  
  // ask the quantity
  printf ("   Quantity: " );
  item.quantity = getInt ();
  
  // ask the minimun quantity
  printf ( "Minimum Qty: " );
  item.minQuantity = getInt ();
  
  // ask if it is taxed or not
  printf ( "   Is Taxed: " );
  item.isTaxed = getYesOrNo ();

  return item;
}


/* --------------------------------------------------
   function  : displayItem
   purpose   : display an item in different formats
   parameter : struct Item item and int format
   result    : void
   --------------------------------------------------*/
void displayItem ( struct Item *p, int format )
{
  bool lowQuantity = isQuantityLow ( p );
  double totalPrice = totalAfterTax ( (*p) );
  
  // if format is LINEAR display it in a line
  if ( format == LINEAR )
  {
    // print sku, name and prince
    printf( "|%d|%-20s|%8.2lf|", (*p).sku, (*p).name, (*p).price );
    
    // if it is not taxed print "No"
    if ( (*p).isTaxed == 0 )
      printf ( "   No|" );

    //else print "Yes"
    else
      printf ( "  Yes|" );
    
    // print quantity, minimun quantity and total price
    printf ( "%4d |%4d |%12.2lf|", (*p).quantity, (*p).minQuantity, totalPrice ); 
    
    // if quantity is lower the the minimun quantity print "***"
    if (lowQuantity == true)
      printf( "***\n" );
    else
      printf( "\n" );
  }

  // else if the format is FORM display item  
  else if ( format == FORM )
  {
    // print sku, name, price, quantity and minimun quantity
    printf ( "        SKU: %d\n", (*p).sku );
    printf ( "       Name: %s\n", (*p).name );
    printf ( "      Price: %.2lf\n", (*p).price );
    printf ( "   Quantity: %d\n", (*p).quantity );
    printf ( "Minimum Qty: %d\n", (*p).minQuantity );
    printf ( "   Is Taxed: " );
    
    // if it is not taxed print "No"
    if ( (*p).isTaxed == 0 )
      printf ( "No\n" );
    
    //else print "Yes"
    else 
    printf ( "Yes\n" );
    
    // if quantity is lower the the minimun quantity print an warning message
    if ( lowQuantity == true )
      printf ( "WARNING: Quantity low, please order ASAP!!!\n" );
  }
}


/* --------------------------------------------------
   function  : listItems
   purpose   : list all items of the inventory and
               print the grand total of the inventory
   parameter : struct Item item[] and int noOfItems
   result    : void
   --------------------------------------------------*/
void listItems ( struct Item item[], int noOfItems )
{
  int i;
  double grandTotal = 0.0; 
  double totalPrice;
  
  // call printTitle
  printTitle ();

  for ( i = 0; i < noOfItems; i++ )
  {
    // print a number for each item in order
    printf ( "%-2d  ", i+1 );
    
    // call displayItem to print items in LINEAR FORMAT
    displayItem ( &item[i], LINEAR );
    
    // calculate the grand total after tax
    totalPrice = totalAfterTax ( item[i] );
    grandTotal = grandTotal + totalPrice;
  }
  
  //call printFooter to print the grand total
  printFooter ( grandTotal );
}


/* --------------------------------------------------
   function  : locateItem
   purpose   : locate an item and return true if find it 
   parameter : struct Item item[], int noOfRecs, 
               int sku, int *p
   result    : void
   --------------------------------------------------*/
int locateItem ( struct Item item[], int noOfRecs, int sku, int *p )
{
int i, result;

// loop into all items to check if one item sku match with the sku input in the argument 
for ( i = 0; i < noOfRecs; i++ )
{
  // if sku input match with the item sku pointer to index is the i value and return true
  if ( sku == item[i].sku )
  {
    *p = i;
    result = true;
  }
}
return result;
}

/* --------------------------------------------------
   function  : loadItems
   purpose   : load Items from an external file
   parameter : struct Item item[], char fileName[]
   result    : void
   --------------------------------------------------*/
int loadItems ( struct Item item[], char fileName[] )
{
  int noOfItems;

  FILE *fp;

  // open the file
  fp = fopen ( fileName, "r" );
  
  // if fail, print error message
  if ( fp == NULL )
  {
    printf ( "Cannot open %s\n", fileName );
    return 0;
  }
  
  // read the file
  else
  {
    int i = 0;
    
    // read each record from the file until EOF
    while ( fscanf ( fp, "%d,%[^,],%lf,%d,%d,%d\n", &item[i].sku, item[i].name, 
           &item[i].price, &item[i].isTaxed, &item[i].quantity, &item[i].minQuantity ) != EOF )
    {
      i++;
    }
    noOfItems = i;
    return 1;
  }
  // close the file
  fclose ( fp ); 
}

/* --------------------------------------------------
   function  : search
   purpose   : search an item and display its data
   parameter : struct Item item[], int NoOfRecs
   result    : void
   --------------------------------------------------*/
void search ( struct Item item[], int noOfRecs )
{
  int sku, searchIndex, itemFound;
  
  // ask the user to enter the SKU and locate it
  printf ( ">Please enter the SKU: " );
  sku = getIntLimited ( SKU_MIN,SKU_MAX );
  itemFound = locateItem ( item, noOfRecs, sku, &searchIndex );
  
  // if find it, display in FORM format
  if ( itemFound == 1 )
    displayItem ( &item[searchIndex], FORM );
  
  // else print a messege to inform the item was not found
  else
    printf ( "Item not found!\n" );
}


/* --------------------------------------------------
   function  : updateItem
   purpose   : update data of an item
   parameter : struct Item *p
   result    : void
   --------------------------------------------------*/
void updateItem ( struct Item *p )
{
  struct Item item;
  int sku;
  char answer;
  
  sku = (*p).sku;
  
  // ask to enter new data
  printf ( "Enter new data:\n" );
  item = enterItem ( sku );
  
  // ask to overwrite the record or not
  printf ( "Overwrite old data? (Y)es/(N)o: " );
  answer = getYesOrNo ();
  
  // if yes update the record and print a message
  if ( answer == 1 )
  {
    (*p) = item; 
    printf ( "--== Updated! ==--\n" );
  }

  // print a message
  else
    printf ( "--== Aborted! ==--\n" );
}
