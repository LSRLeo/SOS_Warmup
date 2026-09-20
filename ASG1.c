/*
Warm Up Homework 1

Name: Shirui Liu
*/


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

}

