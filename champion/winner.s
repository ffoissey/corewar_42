.name "Winning"
.comment "I will do my best"

ld %4, r5
ld %300, r3
st r1, 17
st r1, 38

copy_values:
	ldi :copy_values, r2, r4
	live %17
	sti r4, r3, r2
	add r5, r2, r2
	and r2, %64, r16
	zjmp %:copy_values
	live %38
	ld %0, r2
	fork %250
	st r1, 6
live_loop:
	live %6
	zjmp %-5
