/*
Warm Up Homework 1
Name: Shirui Liu
Date: 2026-09-21
*/


/*library was used for testing purposes*/
//#include <stdio.h>

/*
unsigned short is 2 byte or 16 bits
unsigned char is 1 byte or 8 bits
*/
typedef struct {
    unsigned short limit_0_15; // bits 0 (lowest order) to 15 of limit
    unsigned short base_0_15; // bits 0 to 15 of base
    unsigned char base_16_23; // bits 16 to 23 of base
    unsigned char limit_and_flag; // bits 16 to 19 of limit and 0 to 3 of flag
    unsigned char base_24_31; // bits 24 to 31 of base
} DESC;


/* Prototypes*/
int parse_command(char *inp, int *argc, char *argv[]);
char *itoa(int value, char *str, int base);
void printany(char type, void *data);
void populate_desc(int base, int limit, int flag, DESC *g);



/*
This function splits the character array inp into words, and return the number of words. A sequence of non-blank
characters ending in one or more blank spaces is a word
*/
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

/*
This fucntion convert value into a null-terminated string using the specified base (2, 8, 10 or 16) and store the result
in the str array (pre-allocated)
*/
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


/*
This function can print any primitive C data type (char, int, unsigned,
long, and float) and we can design it to have two arguments to the function
*/

//we can use something to indicate the data type and a pointer to the data*/
void printany(char type, void *data){
    //we have integer, unsigned integer, char, long, and float
    //the user can provide a type to indicate what type of data they are passing in
    if (type == 'i') {
        printf("%d\n", *(int *)data); //type cast so we know how many bytes to read from the pointer address
    } else if (type == 'u') {
        printf("%u\n", *(unsigned int *)data);
    } else if (type == 'c') {
        printf("%c\n", *(char *)data);
    } else if (type == 'l') {
        printf("%ld\n", *(long *)data);
    } else if (type == 'f') {
        printf("%f\n", *(float *)data);
    } else {
        printf("Unknown type: %c\n", type);
    }
}

/*
This function takes as input three integers base, limit and flag, and a DESC pointer g. The
function then populates the memory pointed to by g as per the comments given in the struct description.
*/
void populate_desc(int base, int limit, int flag, DESC *g){
    //first populat the base 
    (*g).base_0_15 = (unsigned short)(base & 0xFFFF); //0xFFFF is the mask for the lower 16 bits of the base
    (*g).base_16_23 = (unsigned char)(base >> 16 & 0xFF); //shift the base right by 16 to keep the higher 8 bites (16-23) and then use masking to get the desired bits
    (*g).base_24_31 = (unsigned char)(base >> 24 & 0xFF); //shift the base right by 24 to keep the higher 8 bits (24-31) and then use masking to get the desired bits

    //now populate the limit and flag
    (*g).limit_0_15 = (unsigned short)(limit & 0xFFFF); //mask the lower 16 bits of the limit
    //To get 16-19 bits of limit, we need to shift the limit to the right by 16 and use masking to get the last 4 bits
    //to get 0-3 bits of flag, we just need to use masking to get the lower 4 bits
    //to combine the two, we use bitwise and we also have to move the flag bits to the left by 4 to leave space for the flag
    (*g).limit_and_flag = ((flag & 0xF) << 4) | (unsigned char)((limit >> 16 & 0xF)); //combine the two parts using bitwise OR
}


/* Main Function for Testing Purposes*/
// int main(void)
// {
//     char buf[40];
//     char inp[] = "hello world  again";
//     char *argv[10];
//     int argc;
//     int k;
 
//     char c = 'A';
//     int i = -42;
//     unsigned int u = 4000000000u;
//     long l = 1234567890L;
//     float f = 3.14f;
//     DESC d;
 
//     //parse_command
//     parse_command(inp, &argc, argv);
//     printf("argc = %d\n", argc);
//     for (k = 0; k < argc; k++) {
//         printf("  argv[%d] = %s\n", k, argv[k]);
//     }
 
//     //itoa
//     printf("%s\n", itoa(512, buf, 2));
//     printf("%s\n", itoa(512, buf, 8));
//     printf("%s\n", itoa(512, buf, 10));
//     printf("%s\n", itoa(512, buf, 16));
//     printf("%s\n", itoa(-512, buf, 10));
//     printf("%s\n", itoa(-512, buf, 16));
//     printf("%s\n", itoa(0, buf, 10));
//     printf("%s\n", itoa(7, buf, 2));
 
//     //printany
//     printany('c', &c);
//     printany('i', &i);
//     printany('u', &u);
//     printany('l', &l);
//     printany('f', &f);
//     printany('z', &i);
 
//     //populate_desc
//     populate_desc(0x12345678, 0xABCDE, 0x7, &d);
//     printf("limit_0_15     = %04x\n", d.limit_0_15);
//     printf("base_0_15      = %04x\n", d.base_0_15);
//     printf("base_16_23     = %02x\n", d.base_16_23);
//     printf("limit_and_flag = %02x\n", d.limit_and_flag);
//     printf("base_24_31     = %02x\n", d.base_24_31);
 
//     return 0;
// }