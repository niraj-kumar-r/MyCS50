#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long int cardNumber = get_long("Number: ");
    long int copyCard = cardNumber;
    int checksum = 0;
    int cardNumberLength = 0;
    int firstDigit = 0;
    int secondDigit = 0;
    bool simpleFlag = true;

    while (copyCard != 0)
    {
        int d = copyCard % 10;

        secondDigit = firstDigit;
        firstDigit = d;

        if (simpleFlag)
        {
            checksum += d;
            // because each digit can only be from 0 to 9
            // so sum of their digits is the digit itself

            simpleFlag = false;
        }
        else
        {
            d *= 2;
            while (d != 0)
            {
                int dig = d % 10;
                checksum += dig;
                d /= 10;
            }
            // multiplying every other digit with 2
            // starting from the last second digit
            // and adding the sum of thier digits to cheksum
            simpleFlag = true;
        }

        copyCard /= 10;
        cardNumberLength += 1;
    }

    int startingNumber = (firstDigit * 10) + secondDigit;

    if (checksum % 10 == 0)
    {
        if (cardNumberLength == 15 && (startingNumber == 34 || startingNumber == 37))
        {
            printf("AMEX\n");
        }
        else if (cardNumberLength == 16 && (firstDigit == 5 && (secondDigit >= 1 && secondDigit <= 5)))
        {
            printf("MASTERCARD\n");
        }
        else if ((cardNumberLength == 13 || cardNumberLength == 16) && firstDigit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
        // checking all conditions
    }
    else
    {
        printf("INVALID\n");
    }
}