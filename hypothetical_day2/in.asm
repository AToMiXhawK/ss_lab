HYP	START	0
A	DB	0
B	DB	3
C	EQU	100
	NEG	R2
LOOP	ADD	R2,R1
	STORE	R1,R2,C
	NEG	R3
	JE	HALT
	LOAD	R0,R1,A
	STORE	R1,R2,B
	JL	LOOP
	JG	LOOP
HALT	HLT
	END	LOOP