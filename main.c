#include <stdio.h>
#include <stdbool.h> 
#include <math.h>

/*
*Description: Program that will calculate amortization of mortage loan)
*Date: 10/10/2021*/


//boolean used to return 0 when true
bool quit;

//takes input for # of years and determines whether it is in the defined range
double numberYears(double numYrs, double min, double max) { 
  printf("Enter in the number of years (3 to 40) for this loan or zero to quit: \n");
  scanf("%lf", &numYrs);
  if (numYrs == 0) {
    quit = true;
    printf("Goodbye user\n"); 
    return 0;
    }
    else if (numYrs < min || numYrs > max) {
      while (numYrs < min || numYrs > max) {
      printf("Invalid input, try again or enter zero to quit.\n");
      scanf("%lf", &numYrs);
      if (numYrs == 0) {
        quit = true;
        printf("Goodbye user\n"); 
        return 0;
        }
      }
    }
    return numYrs;
}

//takes input for interest rate and determines whether it is in the defined range
double interestRate(double intRate, double min, double max) {
  printf("Enter in the interest rate (1 to 25) for this loan or zero to quit: \n");
  scanf("%lf", &intRate);
  if (intRate == 0) {
      quit = true;
      printf("Goodbye user\n"); 
      return 0;
    }
  else if (intRate < min || intRate > max) {
      while (intRate < min || intRate > max) {
      printf("Invalid input, try again or enter zero to quit.\n");
      scanf("%lf", &intRate);
      if (intRate == 0) {
        quit = true;
        printf("Goodbye user\n"); 
        return 0;
        }
      }
    }
  return intRate;
}

//takes input for loan amt and determines whether it is in the defined range
double loanAmount(double loanAmt, double min, double max) {
  printf("Enter in the total amount of the loan (5000 to 2 million) or zero to quit: \n");
  scanf("%lf", &loanAmt);
  if (loanAmt == 0) {
      quit = true;
      printf("Goodbye user\n"); 
      return 0;
    }
  else if (loanAmt < min || loanAmt > max) {
      while (loanAmt < min || loanAmt > max) {
      printf("Invalid input, try again or enter zero to quit.\n");
      scanf("%lf", &loanAmt);
      if (loanAmt == 0) {
        quit = true;
        printf("Goodbye user\n"); 
        return 0;
        }
      }
  }
  return loanAmt;
}

//determines monthly interest
double monthlyInterest(double loanAmt, double intAmt) {
  double total = (loanAmt * (intAmt / 100)) / 12;
  return total;
} 

//determines monthly payment
double monthlyPayment(double loanAmt, double intAmt, double numYrs) {
  double annualInt = (intAmt/100) / 12;
  return loanAmt * ((annualInt * pow(1+annualInt, numYrs * 12)) / (pow(1+annualInt, numYrs * 12) - 1));
}

//calcs principal payment 
double principalPayment(double monthPay, double monthInt) {
  return monthPay - monthInt;
}

//calculates new balance
double princBalance(double loanAmt, double princPay) {
  return loanAmt - princPay;
}

//prints ammoritization table and values
double ammoritizationnTable(double numYr, double monthInt, double princPay, double princBal, double intAmt, double monthPay, double loanAmt) {
    
  //total payments
  double intForTotal = (loanAmt * (intAmt / 100)) / 12;
  double totalIntPaid; 
  double totalPrincPaid;
  double totalAmtPaid;

  //counter
  double counter = 0;


  printf("|_Mnt_______Int_______Princ______________Balance_____|\n");
  if (princBal != 0) {
    for(counter=1; counter <= numYr * 12; ++counter) {
    printf("| %3.0f | $ %10.2f | $ %10.2f | $  %10.2f  |\n", counter, monthInt, princPay, princBal);

    monthInt = monthlyInterest(princBal, intAmt);
    monthPay = monthlyPayment(loanAmt, intAmt, numYr);
    princPay = principalPayment(monthPay, monthInt);
    princBal = princBalance(princBal, princPay); 
    totalIntPaid += monthInt;
      }
  }

  totalIntPaid = totalIntPaid + intForTotal;
  totalPrincPaid = loanAmt;
  totalAmtPaid = loanAmt + totalIntPaid;

  printf("Total interest paid:                                 $ %5.2f\n", totalIntPaid);
  printf("Total principal paid:                                $ %5.2f\n", totalPrincPaid);
  printf("Total cost of the loan paid:                         $ %5.2f\n", totalAmtPaid);
  return 0; 
}


int main(void) { 
  //constants for fixed val, max and min, and range
  const double MIN_NUM_YR = 3;
  const double MAX_NUM_YR = 40;
  const double MIN_INT = 1;
  const double MAX_INT = 25;
  const double MIN_LOAN = 5000;
  const double MAX_LOAN = 2000000;

  //variables for functions to draw
  double userYears;
  double userRate; 
  double userLoan;

  //variables to equal to function values
  double intRate;
  double loanAmt;
  double numYear;
  double monthInt;
  double monthPay;
  double princPay;
  double princBal;
  double amTable;

  //calling functions to variables to hold values
  numYear = numberYears(userYears, MIN_NUM_YR, MAX_NUM_YR);
  if (quit == true) {
    return 0;
  }
  intRate = interestRate(userRate, MIN_INT, MAX_INT);
    if (quit == true) {
    return 0;
  }
  loanAmt = loanAmount(userLoan, MIN_LOAN, MAX_LOAN);
    if (quit == true) {
    return 0;
  }

  //monthly int
  monthInt = monthlyInterest(loanAmt, intRate);

  //monthly payment
  monthPay = monthlyPayment(loanAmt, intRate, numYear);

  //principal payment
  princPay = principalPayment(monthPay, monthInt);

  //principal balance
  princBal = princBalance(loanAmt, princPay);

  // amortization table 
  amTable = ammoritizationnTable(numYear, monthInt, princPay, princBal, intRate, monthPay, loanAmt);
}
