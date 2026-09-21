/*
Warm Up Homework 1

Name: Shirui Liu
*/

//#include <stdio.h>

int parse_command(char *inp, int *argc, char *argv[]);
char *itoa(int value, char *str, int base);
void printany();
// void populate_desc(int base, int limit, int flag, DESC *g);



int parse_command(char *inp, int *argc, char *argv[]){
    //have something to keep count of the words we found
    int count = 0;
    //need another pointer to keep track of the current position in the input string
    char *current = inp;
    //need another variable to indicate if we are currently in a word or not
    int in_word = 0; //0 means we are not in a word, 1 means we are in a word


    //loop through the input string until we reach the end
    while (*current != '\0') {
        //skip any whitespace characters
        if (*current == ' '){
            if (in_word){
                //if we were in word previously but the current char is white space
                //we must indicate that we are no longer in a word 
                //otherwise, when we print, we will keep printing until we print everything instead of just one word 
                *current = '\0'; //replace the whitespace with a null terminator to end the current word
                in_word = 0; //indicate that we are no longer in a word
            }
        } else {
            //if its not white space, we want to mark it as the start of new word
            //however, we need to watch out for if we were previously already in a word 
            if (!in_word){
                argv[count] = current; //set the current position as the start of a new word
                in_word = 1; //indicate that we are now in a word
                count++;
            }
        }
        current++;
    
    }
    *argc = count; //set the count of words found to the argc pointer
    return count; //also return the count of words found
}


char *itoa(int value, char *str, int base){

    char map[] = "0123456789abcdef";

    //use a variable to keep track if we are dealing with a negative number
    int is_negative = 0;

    //first we need to check if the value is 0
    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    //check if the base is valid (between 2 and 36)
    if (base != 10 && base != 2 && base != 8 && base != 16) {
        printf("Invalid base: %d. Base must be 2, 8, 10, or 16.\n", base);
        str[0] = '\0'; //return an empty string if the base is invalid
        return str;
    }

    unsigned int h;
    unsigned int q;

    //then we need to check if the value is negative and the base is 10
    if (value < 0 && base == 10) {
        is_negative = 1;
        h = 0u -(unsigned int)value; //prevent overflow of large negative num
    } else {
        h = (unsigned int)value; //cast the value to unsigned int for further processing
    }

    //now we need to convert the value to the specified base
    q = h; 
    int d = 0; 
    while (q > 0) {
        d++; //increment the digit count
        q /= base; //get the quotient of the value divided by the base -> doing this give us the digits we need
    }
    //ex: 36/8 = 4, 4/8 = 0, we just need two digits. 

    q = h; //set q back to h beacuse we need it later


    /* Remainders come out backwards (ones digit first).
    Start i at the last digit slot and move left so the string is in normal order. */

    int i;
    if (is_negative) {
        str[0] = '-';// the minus sign goes in first place
        str[d + 1] = '\0';
        i = d;          //digits go in str[1] .. str[d] for negative value 
    } else {
        str[d] = '\0';
        i = d - 1;      //digits go in str[0] .. str[d-1] for positive value
    }
 

    while ( q > 0) { //while the amount of digits we have to process is greater than 0
        int r = q % base; //still a int not a string

        //No restirction on using table 
        //so we are going use a table -> for only digits in ASCII
        str[i] = map[r];
        q /= base;
        i--;
    } 

    return str;
}







// int main(void)
// {
//     char buf[80];
//     char line[] = "ls  -l   file.txt";
//     char *argv[10];
//     int argc = 0;
//     int n;
//     int i;
//     printf("%s\n", itoa(512, buf, 2));
//     printf("%s\n", itoa(512, buf, 8));
//     printf("%s\n", itoa(512, buf, 10));
//     printf("%s\n", itoa(512, buf, 16));
//     printf("%s\n", itoa(-512, buf, 10));
//     printf("%s\n", itoa(-512, buf, 16));
//     printf("%s\n", itoa(0, buf, 10));
//     printf("%s\n", itoa(7, buf, 2));
//     n = parse_command(line, &argc, argv);
//     printf("count=%d\n", n);
//     for (i = 0; i < argc; i++)
//         printf("%s\n", argv[i]);
//     return 0;
// }