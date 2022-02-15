#import <stdio.h>
#import <cs50.h>
#import <math.h>

int checksum(long cc, int t, int g);

int main(void)
{
    // getting input for the credit card no.
    long cc = get_long("Credit Card Number: ");
    
    //cheking for 16 digits credit card nos.
    if (cc > pow(10, 15) - 1 && cc < pow(10, 16)) 
    {
        //using the result from checksum function
        int ffsum = checksum(cc, 8, 8);
        if (ffsum % 10 == 0)
        {
            if (cc / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            //checks the starting digit
            else if ((cc / 100000000000000) < 56 && (cc / 100000000000000 > 50))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    //checking for 13 digit credit card nos.
    else if (cc > pow(10, 12) - 1 && cc < pow(10, 13))
    {
        //using the result from checksum function
        int ffsum = checksum(cc, 6, 8);
        if (ffsum % 10 == 0)
        {
            //checks the starting digit
            if (cc / 1000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    //checking for 15 digit credit card nos.
    else if (cc > pow(10, 14) - 1 && cc < pow(10, 15))
    {
        //using the result from checksum function
        int ffsum = checksum(cc, 7, 8);
        if (ffsum % 10 == 0)
        {
            //checks the starting digit
            if ((cc / 10000000000000 == 34) || (cc / 10000000000000 == 37))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    else
    {
        printf("INVALID\n");
    }
}

//creating a prototype for the checksum function
int checksum(long cc, int t, int g)
{  
    int ffsum = 0;
    int sum = 0; 
    int fsum = 0;
    long dc = cc;

    //checking for alternate digits
    for (int i = 0; i < t; i++)
    {
        int digit = (dc / 10) % 10;
        
        //multiplying them with 2
        int fdigit = digit * 2;
        dc = dc / 100;

        if (fdigit > 9)
        {
            int ddigit = fdigit % 10;
            sum = sum + ddigit + 1;
        }
        else
        {
            sum = sum + fdigit;
        }
    }
    for (int i = 0; i < g; i++)
    {
        int digit = cc % 10;
        cc = cc / 100;
        fsum = fsum + digit;
    } 
    ffsum = sum + fsum;
    return ffsum;
}
