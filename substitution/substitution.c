#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_key(string key);
int linear_search(char key, string base);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (check_key(argv[1]) != 0)
    {
        printf("Key must contain only 26 charachters, all of which must be alphanumneric and appear only once");
        return 1;
    }

    else
    {
        string KEY = argv[1];
        string plain_text = get_string("plaintext: ");

        printf("ciphertext: ");

        for (int i = 0, n = strlen(plain_text); i < n; i++)
        {
            if (islower(plain_text[i]))
            {
                printf("%c", tolower(KEY[plain_text[i] - 97]));
            }
            else if (isupper(plain_text[i]))
            {
                printf("%c", toupper(KEY[plain_text[i] - 65]));
            }
            else
            {
                printf("%c", plain_text[i]);
            }
        }
        printf("\n");
        return 0;
    }
}

int check_key(string key)
{
    if (strlen(key) != 26)
    {
        return 1;
    }
    else
    {
        char key_array[26];
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if (!(islower(key[i]) || isupper(key[i])))
            {
                return 2;
            }

            else if (linear_search(key[i], key_array) != -1)
            {
                return 3;
            }
            else
            {
                key_array[i] = toupper(key[i]);
            }
        }
        return 0;
    }
}

int linear_search(char key, string base)
{
    for (int i = 0, n = strlen(base); i < n; i++)
    {
        if (base[i] == key)
        {
            return i;
        }
    }
    return -1;
}