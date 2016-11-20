#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string word = argv[1];
    string salt = argv[2];
    string hash = crypt(word, salt);
    printf("%s\n", hash);
}