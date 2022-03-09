//Melissa Nguyen
//CS201
//A3
//5/10/2021
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <error.h>

void get_bits(int frac_bit, int exp_bit, int hex); //gets the info for my frac and exp section
void calculations(int frac_bit, int exp_bit, int frac, int exp, int sign);//once I get my values, does the float calculations + displays it

int main(int argc, char *argv[])
{
   if(argc != 4) //not enough arguments passed in
   {
      printf("Error! Not enough arguments!\n");
      exit(EXIT_FAILURE);
   }

   int frac = atoi(argv[1]); //takes the first argument the user entered
   int exp = atoi(argv[2]); //takes the second argument the user entered
   int hex = 0;
   int success = 0;
   char test = '\0';

   //my error checking for taking user input:
   if(frac < 2 || frac > 10)
   {
      printf("Wrong input! Frac bit must be between 2 and 10. \n");
      exit(EXIT_FAILURE);
   }
   if(exp < 3 || exp > 5)
   {
      printf("Wrong input! Exp bit must be between 3 and 5. \n");
      exit(EXIT_FAILURE);
   }

   success = sscanf(argv[3], "%x%c", &hex, &test); //takes the third argument the user entered

   if(success == 0)
   {
      printf("Not a valid hex number.\n");
      exit(EXIT_FAILURE);
   }
   if (success != 0)
   {
      if(hex > 1 << (exp + frac + 1))
      {
         printf("Exceeds max number of bits! Only 7 allowed here.\n");
         exit(EXIT_FAILURE);
      }

      if (test != '\0' || hex == 0)
      {
         printf("Not a valid hex number. \n");
         exit(EXIT_FAILURE);
      }
   }

   //if this part is reach, then the correct user input was taken.
   //I call the get_bits to get my frac and exp isolated, but in this 
   //function I also call the calc and it displays in the calc functions.
   //if I had more time, I would break it down even further.
   get_bits(frac, exp, hex);

   exit(EXIT_SUCCESS);
}


//isolates the frac, exp, and sign
void get_bits(int frac_bit, int exp_bit, int hex)
{
   int frac;
   int exp;
   int sign;

   //this section does the isolating
   frac = hex & ((1 << frac_bit) - 1);
   exp = hex & (((1 << exp_bit) - 1) << frac_bit);
   exp = exp >> exp_bit;

   sign = hex & (1 << (frac_bit + exp_bit));
   sign = hex >> (exp_bit + frac_bit);

   //then check for the special cases
   if((exp << exp_bit) == (((1 << exp_bit) - 1) << frac_bit))
   {
      if(frac == 0)
      {
         if(sign)
            printf("\n-inf\n");
         else
            printf("\n+inf\n");
      }
      else
         printf("\nNan\n");
      return;
   }

   //if no special cases (except the denormalization one), then does the calc
   calculations(frac_bit, exp_bit, frac, exp, sign);

   return;
}

//does the calculation and the display. If I had more time, would have split this up.
void calculations(int frac_bit, int exp_bit, int frac, int exp, int sign)
{
   int E;
   float M;
   float value;
   int bias;

   bias = (pow(2, (exp_bit - 1)) - 1);

   //checks if its denormalized
   if(exp == 0)
   {
      E = 1 - bias;
      M = frac / pow(2, frac_bit);
   }
   //normalized
   else
   {
      E = exp - bias;
      if(E < 0)
         E *= -1;

      M = 1 + (frac / (pow(2, frac_bit)));
   }


   value = pow(-1, sign) * (M * (pow(2, E)));

   printf("\n%f \n\n", value); 

   return;

}
