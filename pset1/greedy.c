#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int n, qtrs, dimes, nckls, pnns;
    float i, fqtrs, fdimes, fnckls, fpnns;
    
    /*user is prompted for an amount that is 
    validated as being positive.*/
    
    do
    {
        printf("Enter the amount of change needed: ");
        i = GetFloat();
    }
    while (i < 0);
    
    /*the amount is then converted to an int*/
    n = ((int) round(i * 100));
    
    /*The amount is testing for each coin amount and
     then the remainder is tested and so forth*/
    fqtrs = n / 25;
    qtrs = (int) round(fqtrs);
    n = n % 25;
    fdimes = n / 10;
    dimes = (int) round(fdimes);
    n = n % 10;
    fnckls = n / 5;
    nckls = (int) round(fnckls);
    n = n % 5;
    fpnns = n / 1;
    pnns = (int) round(fpnns);
    n = qtrs + dimes + nckls + pnns;
    printf("%d\n", n);
    
    return 0;
}
