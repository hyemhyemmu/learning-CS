#decision making in RSIC-V

int main(){
 //example 1:
	if (i==j)
		f=g+h;
	else
		f=g-h;


	bne x13,x14,Else
	add x10,x11,x12
	Else: sub x10,x11,x12

//example 2:
	int A[20];
	int sum=0;
	for (int=0;i<20;i++)
		sum+=A[i];

	add x1,x2,x0 // x1=&A[0]
	add x3,x0,x0 // x3=sum=0
	add x4,x0,x0 // x4=i=0
	addi x5,x0,20 // x5=20
	
	//loop:
	Loop:
		bge x4,x5,Done
		lw x6,0(x1)  // x6=A[i]
		add x3,x3,x6 // sum+=x6
		addi x9,x9,4 // A[i+1]
		addi x4,x4,1 // i++
		j Loop
	Done:

//example 3:
	mv rd,rs //copy from rs to rd
	li rd,13 //load number
	nop	 //nop
}


