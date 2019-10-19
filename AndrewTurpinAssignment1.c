/* COP3502C Midterm Assignment One
    This program is written by: Andrew Turpin */




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//#define SIZE 50
//#define EMPTY -1
//char stack[50];
int top=-1;



//other function declarations
char* convertToPostfix(char* str);
int evaluate(char* str);


//stack definition
struct stack
{
    unsigned size;
    int top;
   int* arr;

};

//stack creation
struct stack*creation(unsigned size){
struct stack* stack=(struct stack*)malloc(sizeof(struct stack));//allocates memory for stack
if(!stack)return NULL;

stack->top=-1;
stack->size=size;
stack->arr=(int*)malloc(stack->size*sizeof(int));//allocates memory for int* of stack by some given arbitrary length
return stack;
}


//check for empty stack
int empty(struct stack* stack){
return stack->top==-1;
}


//peek at the top of the stack
char peek(struct stack* stack){
  return stack->arr[stack->top];
}


//pop out the top value of the stack
char pop(struct stack* stack){
  if(!empty(stack))
  return stack->arr[stack->top--];
  return '_';
}

//pop integer function
int popi(struct stack* stack){
  if(!empty(stack))
  return stack->arr[stack->top--];
  return '_';
}

//push in a value to the stack
void push( struct stack* stack,char o){
  stack->arr[++stack->top]=o;

}

//push integer into stack function
void pushi( struct stack* stack,int o){
  stack->arr[++stack->top]=o;

}







//MENU FUNCTION
char* menu(){
 char temp;//temp to hold menu selection choice
printf("MENU: \n");
printf("1. Type e to enter an infix \n");
printf("2. Type x to exit the program \n");
scanf(" %c", &temp);

char stringtemp[50];//stringtemp to hold temp string inputted by user to then malloc a dynamic                        string with the temp strings length
//add parenthesis to the open and end of the function for the postfix conversion
char open[2]="(";
char close[2]=")";

 switch (temp){
case 'e' : {

 printf("please type the equation here\n\n");
 //the ^\n parses the string at the new line for inputting
  scanf(" %[^\n]s",stringtemp);




  int len = strlen(stringtemp);//get length of string to then dynamically allocate                                    another string by this length
char *p=(char*)malloc((len+2)*sizeof(char));//dynamically allocating out string
strcpy(p, stringtemp);//copying over contents of local string to this newly allocated dynamic string
 int i=0, j=1;
 //integer counters
//p[1]='(';
for(i=1,j=1;i<=strlen(stringtemp);i++){
  //if it's not a space add it to the postfix string and increment j
  if (stringtemp[i] != ' ') {
    p[j]=stringtemp[i];
    j++;
  }
}
//p[j]=')';
p[j]='\0';//end the postfix with a null

  return p;//returning the dynamic string back to main
  break;
}

case 'x' : {
printf("\n now exiting the program");


char exit[4]="exit";//setting exit function with the string "exit" as described in the                        instructions
int exitlen=strlen(exit);//get length for the dynamic exit string
char *e=(char*)malloc(exitlen*sizeof(char));//create the dynamic exit string
strcpy(e,exit);//copy contents of local exit string to new dynamic exit string
  return e;//return dynamic exit string

}
}
return "0";
}











//Any function or variable starting in a p indicates its a stack variable or stack function JUST FOR THE PARENTHESIS PART
int ptop=-1;
char pstack[50];

void ppush(char x){//push function for parenthesis stack
  pstack[ptop]=x;
  ptop++;
}

void ppop(){//pop function for parenthesis stack
  if(ptop==-1){//if ptop is already empty than there is an imbalance
    printf("Imbalanced parenthesis \n");
    exit(0);
  }
  else{//else pop out the parenthesis
    ptop--;
  }
}

int ppeek(){//peek the top of the parenthesis stack
  if(ptop==-1){//if it's empty return 1
  return 1;}
  else{//if it isn't empty return 0
  return 0;}
}


//function to check if the parenthesis are balanced
int isBalancedParenthesis(char* str) {

  int i=0;//loop iterator

  struct stack* stackp=creation(strlen(str));//create parenthesis stack
for(i=0;str[i]!='\0';i++){//as long as the iteration doesn't encounter a null point                                   keep going through loop
  if(str[i]=='('){
    ppush(str[i]);//if theres an open parenthesis push it into pstack
  }
  else if (str[i]==')'){//if theres a close parenthesis pop out of the pstack
    ppop();
  }
}

if(ppeek()==1){return 1;}//if the ppeek function returns 1 that means theres no left over parenthesis, meaning the check passes
else if (ppeek()==0){return 0;}//this means that there are left over parenthesis in the stack so it is not balanced, so return 0 back to the main

else
  return 0;
}







//function to check if it is an operand( a number)
int isOperand(char o){
return (o>='0'&&o<='9');

}

//function to check if the given charecter is an operator, if it is return 1, if not return 0
int isOperator(char c){
  if(c=='+'|| c== '-'||c=='/'||c=='*'||c=='^'||c=='%'){
      return 1;}
  else
      return 0;
}

//highest priority is 3, lowest is 1
int getOperatorPriority(char c){//this function gets the corresponding priority PEMDAS wise of the operators and gives that back to the infix to post fix function to deal with
if(c=='^')
  return 3;
else if(c=='%'||c=='/'||c=='*')
  return 2;

else if(c=='-'||c=='+')
  return 1;

else return -1;
}


int convertToInt(char c){//simple "conver this charecter into an integer" function

return (int)(c - '0');//return said changed char to int
}



//this function calculates mathimateically the result of the two integers passed into it and the corresponding operator is was given, then returns that new numerical value
int calculate(int a, int b, char op){
int result;

switch (op){
  case '+' : result=a+b;
      return result;
      break;
  case '-' : result=b-a;
      return result;
      break;
  case '/' : result=b/a;
      return result;
      break;
  case '*' : result=b*a;
      return result;
      break;
  case '%' : result=b%a;
      return result;
      break;
  case '^' : {//made a small power loop to calculate
    int count;
    int temp=1;
    for(count=0;count<a;++count){
      temp=temp*b;
    }


    result=temp;
      return result;
      break;}

default :return 0;//defualt to catch illegal operators
}

}





//Main function
int main(void){
  char* str;//1 excess line
  char* postFix;//2 excess line
  while(strcmp(str = menu(), "exit")!=0)
  break;//3 excess line. This break was put here as it was the only way for me to get the given while loop by the professor to not repeate indefinetly.
  {if (isBalancedParenthesis(str))
  {
    postFix =convertToPostfix(str);
     evaluate(postFix);
     printf("Parenthises check passed\n");//personal parentesis test checker, excess line 4
    }
    else
      printf("Parenthesis imbalanced\n");
    }
        return 0;
    }




//this function converts the infix to postfix, any variable that ends in 'c' like stackc has to deal with the infix to postfix calculations
 char* convertToPostfix(char* str){
   struct stack* stackc=creation(strlen(str));//make the postfix stack with size equal to string length
   if(!stackc)//if the stack is empty, return null
      return NULL;
char *pf=(char*)malloc(52*sizeof(char));

      int i=0;//loop placeholders
      int j=0;
      for(i=0,j=-1;str[i];++i){

          //if the index is an operand,
          if(isOperand(str[i])){
          pf[++j]=str[i];
          while(isOperand(str[i+1])){//while we keep getting more following itegers, append them to the int making it multi digit
            pf[++j]=str[i+1];
            i++;//incrememnt i to get out of loop
          }
          pf[++j]=' ';//add space at the end to distinguish the numbers from one another, or "tokenize" them
          }

          //else, if the index is an open parenthesis, push it into the stack
          else if(str[i]=='(')
              push(stackc,str[i]);
              //ELSE if the index is a closing parenthesis, pop from out of the stack untill the next open parenthesis is found
              else if(str[i]==')'){
                  while(!empty(stackc)&&peek(stackc)!='('){
                      pf[++j]=pop(stackc);}


                          pop(stackc);


              }
              else{//these next few statements means we encountered an operator, so we check it's priority and pop the last input of the stack, then store the operand that was encountered
                while(!empty(stackc)&&getOperatorPriority(str[i])<=getOperatorPriority(peek(stackc)))
                  pf[++j]=pop(stackc);
                  push(stackc,str[i]);
              }
      }

      //if there are any letover operators in the stack at the end of the loop, pop them out to the postfix
while(!empty(stackc)){
  pf[++j]=pop(stackc);}


printf("\nPostfix output: %s \n",pf);//This prints the postfix and the next line just returns it back to the main for the evaluation
return pf;//return the postfix back to the main for the evaluate function
 }



//this is the evaluation function,
int evaluate(char* postFix){
  struct stack* stacke=creation(strlen(postFix));//creats stacke, this stacke is the evaluation stack
  int k;//loop incrementor
  for(k=0;postFix[k];k++)
        {
            if(isdigit(postFix[k])){//if the index is a number, convert it's string index to an int
              int num = convertToInt(postFix[k]);
            while(isdigit(postFix[k+1])){//while the following numbers are also numbers, add them to the already existing number to essentially count for double digits.
              num = num * 10 + (convertToInt(postFix[k+1]));
              k++;// increment k to make sure the index moves on
            }

            pushi(stacke,num);//push this new converted int to the stack stacke
            }

            else if (postFix[k] == ' ') {//if we encounter a space we simply continue meaning we correctly tokenized the new ints and seperate them accordingly
              continue;
            }

            else {//means we encounterd an operator, so we pop the last 2 numbers to apply the given operator on
                  int a=popi(stacke);
                  int b=popi(stacke);
                   int result;//result for the next lines operation
                  result=calculate(a,b,postFix[k]);//take the last two poped numbers, and do the corresponding calculation given the selected operator

                  pushi(stacke,result);//push that number back into the stack for the next round of math


                  }


                }



             int end= popi(stacke);//this pop statement gets the end number after all the math is done within the loop







            printf("\nEvaluation: %d\n\n",end);//print the final evaluated number
           return 0;
        }










