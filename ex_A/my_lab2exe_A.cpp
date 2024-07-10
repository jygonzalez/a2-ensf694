/**
 *  File Name: lab2exe_A.cpp
 *  Assignment: ENSF 694 Lab 2 Exercise A
 *  Created by: Mahmood Moussavi
 *  Completed by: Yael Gonzalez
 *  Submission Date: July 10, 2024
 */

int my_strlen(const char *s);
/**  
 *  Duplicates strlen from <cstring>, except return type is int.
 *  REQUIRES:
 *     s points to the beginning of a string.
 *  PROMISES:
 *     Returns the number of chars in the string, not including the
 *     terminating null.
 */

void my_strncat(char *dest, const char *source, int n);
/**
 *  Duplicates my_strncat from <cstring>, except return type is void.
 *  REQUIRES:
 *     dest and source each point to the beginning of a string.
 *     n > 0, where n is the number of characters to be concatenated
 *     from source onto dest.
 *     source strlen >= n.
 *     dest >= dest + n, i.e., enough space in dest to contain its
 *     current length plus the added characters.
 *  PROMISES:
 *     concatenates up to n characters from the source string to the
 *     end of the dest string.
 */

#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
    char str1[7] = "banana";
    const char str2[] = "-tacit";
    const char *str3 = "-toe";

    /* point 1 */
    char str5[] = "ticket";
    char my_string[100] = "";
    int bytes;
    int length;

    /* using my_strlen function */
    length = my_strlen(my_string);
    cout << "\nLine 1: my_string length is " << length;

    /* using sizeof operator */
    bytes = sizeof(my_string);
    cout << "\nLine 2: my_string size is " << bytes << " bytes.";

    /* using strcpy libarary function */
    strcpy(my_string, str1);
    cout << "\nLine 3: my_string contains: " << my_string;

    length = my_strlen(my_string);
    cout << "\nLine 4: my_string length is " << length << ".";

    my_string[0] = '\0';
    cout << "\nLine 5: my_string contains:\"" << my_string << "\"";

    length = my_strlen(my_string);
    cout << "\nLine 6: my_string length is " << length << ".";

    bytes = sizeof(my_string);
    cout << "\nLine 7: my_string size is still " << bytes << " bytes.";

    /* my_strncat append the first 3 characters of str5 to the end of my_string */
    my_strncat(my_string, str5, 3);
    cout << "\nLine 8: my_string contains:\"" << my_string << "\"";

    length = my_strlen(my_string);
    cout << "\nLine 9: my_string length is " << length << ".";

    my_strncat(my_string, str2, 4);
    cout << "\nLine 10: my_string contains:\"" << my_string << "\"";

    /* my_strncat append ONLY up ot '\0' character from str3 -- not 6 characters */
    my_strncat(my_string, str3, 6);
    cout << "\nLine 11: my_string contains:\"" << my_string << "\"";

    length = my_strlen(my_string);
    cout << "\nLine 12; my_string has " << length << " characters.";

    cout << "\n\nUsing strcmp - C library function: ";

    cout << "\n\"ABCD\" is less than \"ABCDE\" ... strcmp returns: " << strcmp("ABCD", "ABCDE");

    cout << "\n\"ABCD\" is less than \"ABND\" ... strcmp returns: " << strcmp("ABCD", "ABND");

    cout << "\n\"ABCD\" is equal than \"ABCD\" ... strcmp returns: " << strcmp("ABCD", "ABCD");

    cout << "\n\"ABCD\" is less than \"ABCd\" ... strcmp returns: " << strcmp("ABCD", "ABCd");

    cout << "\n\"Orange\" is greater than \"Apple\" ... strcmp returns: " << strcmp("Orange", "Apple") << endl;

    return 0;
}

int my_strlen(const char *s)
{
    const char *e = s;

    // Move the pointer 'e' to the last char (stops at '\0')
    while (*e)
        e++;

    return (int)(e - s); // e (end) - s (start) = string length
}

void my_strncat(char *dest, const char *source, int n)
{
    // Move the pointer 'dest' to the last char (stops at '\0')
    while (*dest)
        dest++;

    // Iterate n times. For each cycle, assign value of source to dest
    // and move both pointers
    for (int i = 0; i < n; i++)
    {
        *dest = *source;
        dest++;
        source++;
    }
    
    // After adding n values of source to dest, make sure to return a 
    // c-string, i.e., add a '\0' at the end.
    *dest = '\0';
}
