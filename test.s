Print Insert a starting value: 
READ x0
Print Insert an ending value: 
READ x1
mult x0, 3, x2
WRITE x2
ADD X0, 1, x0
LE x1, x0, x3
jmp0 x3, 4
Println Counting finished
HALT