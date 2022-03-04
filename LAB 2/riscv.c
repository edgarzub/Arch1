#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();
char** parse(char** tokens,char* str);
int option(char** str);
/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	char* tokens[20];
	int op;
	int RS1,RS2,RS3;
	char* ptr1=NULL,*ptr2=NULL,*ptr3=NULL;
	char* temp[20];
	
	
	//Get toknes
	parse(tokens,instr);

	//Get operation and print option
	op=option(tokens);
	printf("\n%d",op);

	//Example ADD X2 X5 X4
	if(op==1){
		printf("\nestamos dentro");
		//Getting registers
		ptr1=strtok(tokens[1],"X");
		ptr2=strtok(tokens[2],"X");
		ptr3=strtok(tokens[3],"X");

		//Get numerical value of registers
		RS3=atoi(ptr1);
		RS1=atoi(ptr2);
		RS2=atoi(ptr3);
		//operation
		reg[RS3]=reg[RS1]+reg[RS2];
		printf("The ADD has been completed");
	}else if(op==2){
		printf("THis is an ADDI");
		ptr1=strtok(tokens[1],"X");
		ptr2=strtok(tokens[2],"X");
		ptr3=strtok(tokens[3],"X");

		RS3=atoi(ptr1);
		RS1=atoi(ptr2);
		RS2=atoi(ptr3);

		reg[RS3]=reg[RS1]+RS2;


	}else if(op==3){
		ptr1=strtok(tokens[1],"X");

		int32_t adress;
		int i=0,offset;
		char* mem_file = "mem.txt";
		//parse the second token
		for(ptr2=strtok(tokens[2],"(X)"); ptr2!=NULL;ptr2=strtok(NULL,"(X)")){
			temp[i]=ptr2;
			i++;
		}
		offset=atoi(temp[0]);

		RS1=atoi(temp[1]);

		adress=reg[atoi(ptr1)];
		int32_t destination=RS1+offset;
		write_address(adress,destination,mem_file);
		


	}else if(op==4){
		//lw X2 5(x5)
		//look in postion 10 in mem file
		//gab value
		//load into register 2.
		ptr1=strtok(tokens[1],"X");

		int32_t adress;
		int i=0,offset;
		char* mem_file = "mem.txt";
		//parse the second token
		for(ptr2=strtok(tokens[2],"(X)"); ptr2!=NULL;ptr2=strtok(NULL,"(X)")){
			temp[i]=ptr2;
			i++;
		}
		offset=atoi(temp[0]);
		RS1=atoi(temp[1]);
		adress=reg[RS1]+offset;
		
		int32_t read=read_address(adress,mem_file);
		reg[atoi(ptr1)]=read;

	}

	return true;
}

int option(char** str){
	char* ptr=str[0];
	printf("%s",ptr);

	if(strcmp("ADD",ptr) == 0){
		printf("\nEs un add!!!!");
		return 1;
	}else if(strcmp("ADDI",ptr)==0){
		printf("\nEs un addi !!!!");
		return 2;
	}else if(strcmp("SW",ptr)==0){
		return 3;
	}else if(strcmp("LW",ptr)==0){
		return 4;
	}else{
		return 0;
	}
}

char** parse(char** tokens,char* str){
	char *ptr=NULL;
	int i=0;

	ptr=strtok(str," ");

	while(ptr!=NULL){
		tokens[i++]=ptr;
		ptr=strtok(NULL," ");
	}
	return tokens;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Prints all 32 registers in column-format
 * LW X6 8(X4)
 * 8+4=12
 * 
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	write_read_demo();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");


	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}
