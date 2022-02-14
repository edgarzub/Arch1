#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool delim_character(char c, char delim);
bool non_delim_character(char c, char delim);
char *word_start(char* str,char delim);
char *end_word(char* str,char delim);
int count_tokens(char* str,char delim);
char *copy_str(char *inStr, short len, char delim);
char** tokenize(char* str, char delim);
void print_all_tokens(char** tokens);

int main(){
   char delimeter[1];
   char input[100];
   printf("Please enter the delimeter\n$$");
   scanf("%c",delimeter);
   printf("Please enter the words with the delimeter\n$$");
   scanf("%s",input);

   char* input_pinter=&input[0];

   


   char** token=tokenize(input_pinter,delimeter[0]);

   print_all_tokens(token);






}
/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim)
{

if(c==delim){
   return true;
}else{
   return false;
}


}

/* Return true (non-zero) if c is a non-delimiter
   character.
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim)
{

if(c!=delim){
   return true;
}else if(c==0){
   return false;

}else{
   return false;
}

}

/* Returns a pointer to the first character of the next
   word starting with a non-delimiter character. Return a zero pointer if
   str does not contain any words.*/
char *word_start(char* str,char delim)
{
   if(str==NULL){
      return NULL;
   
   }else if(non_delim_character(*str,delim)){
      return str;

   }else{
      return word_start((str+1),delim);
   }
   
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char* str,char delim)
{
   if(*str==0){
      return str-1;
   
   }else if(delim_character(*str,delim)){
      return str-1;

   }else{
      return end_word((str+1),delim);
   }


}

/* Counts the number of words or tokens*/
int count_tokens(char* str,char delim)
{
   if(*str==0){
      return 1;
   
   }else if(delim_character(*str,delim)){
      return 1+count_tokens((str+1),delim);

   }else{
      return count_tokens((str+1),delim);
   }


}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim)
{
   char *str=(char*) malloc( (len +1) *(sizeof(char*) ) );
   

   for(int i=0;i<len;i++){
      *str=*inStr;
      //printf("This is:%c\n",*str);
      str++;
      inStr++;
      
   }
   
   return str-len;

}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   delimiter-separated tokens from zero-terminated str.
   For example, tokenize("hello world string"), with a character delimiter
   of a space " " would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char** tokenize(char* str, char delim)
{
int size=count_tokens(str,delim);
char **tokenizer=(char**)malloc(sizeof(char*)*(size+1));

for(int i=0;i<size;i++){
   short lenght=0;
   char *start=word_start(str,delim);
   //char *end=end_word(str,delim);
   printf("El index start que sigue es:  %c\n",*start);

   while(non_delim_character(*start,delim)){
      lenght++;
      start++;
   }

   printf("tamano de la palabra es: %d\n",lenght);
   *tokenizer=copy_str(str,lenght,delim);
   tokenizer++;
   str=end_word(str,delim)+2;
   printf("El index que sigue es:  %c\n",*str);


}
   return tokenizer-size;


}

void print_all_tokens(char** tokens)
{
   printf("Your tokens are:\n");
   while(tokens != NULL){
      
      printf("%s\n", *tokens);
      tokens++;
   }

}

