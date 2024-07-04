#include<stdio.h>
int main()
{ 
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/4.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    
    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];
    
    asm volatile(
    	//iloop
    	"li t0, 0\n\t" //i
    	"Fori:\n\t"
    	//jloop
    	"li t1, 0\n\t" //j
    	"Forj:\n\t"
    	//kloop
    	"li t2, 0\n\t" //f
    	"li t5, 0\n\t"//temp
    	"Fork:\n\t"
    	//p_x
    	"slli t3, t2, 1\n\t" //t3=2f
    	"add t3, t3, t1\n\t" //t3=2f+j
    	"slli t3, t3, 2\n\t" //t3*4bites
    	"add t3, %[p_x], t3\n\t"//t3=p_x+j+2*f ,is pointer
    	"lw t3, 0(t3)\n\t" //t3=p_x+j+2*f ,is val
    	//p_h
    	"slli t4, t0, 1\n\t" //t4=2i
    	"add t4, t4, t0\n\t" //t4=2i+i
    	"add t4, t4, t2\n\t" //t4=3i+f
    	"slli t4, t4, 2\n\t" //t4*4bites
    	"add t4, %[p_h], t4\n\t"//t4=p_h+3*i+f ,is pointer
    	"lw t4, 0(t4)\n\t" //t4=p_h+3*i+f ,is val
    	//x*h into t5
    	"mul t3,t3,t4\n\t"
    	"add t5,t5,t3\n\t"
    	//iloopend
    	"addi t2, t2, 1\n\t"
    	"li t3 ,3\n\t"
    	"blt t2, t3, Fork\n\t" //f<3
    	//p_y
    	"slli t6, t0, 1\n\t" //t6=2i
    	"add t6, t6, t1\n\t" //t6=2i+j
    	"slli t6, t6, 2\n\t" //t6*4bites
    	"add t6, %[p_y], t6\n\t"//t6=p_h+3*i+f ,is pointer
    	"sw t5, 0(t6)\n\t"
    	//jloopend
    	"addi t1, t1, 1\n\t"
    	"li t3 ,2\n\t"
    	"blt t1, t3, Forj\n\t" //j<2
    	//kloopend
    	"addi t0, t0, 1\n\t"
    	"li t3 ,3\n\t"
    	"blt t0, t3, Fori\n\t" //i<3
	:
	:[p_x]"r"(p_x) , [p_h]"r"(p_h) , [p_y]"r"(p_y)
    );

    p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
