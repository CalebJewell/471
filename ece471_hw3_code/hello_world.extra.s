.syntax unified

@ Syscall Definitions
.equ SYSCALL_EXIT,     1
.equ SYSCALL_WRITE,    4

@ Other Definitions
.equ STDOUT,	       1

        .globl _start
_start:

	mov	r0,#15 @starting at 15 to increment backwards

	@==========================================
	@ Your code for part 3d goes here =\
	@                                  \/
	@==========================================
loop:
	push {r0}	@pushing r0 because when the program goes to print number r0 gets destroyed
	@==========================================

	bl	print_number		@ print r0 as a decimal number
 
	ldr	r1,=message		@ load message
	bl	print_string		@ print it

	@==========================================
	@ Your Code for part 3d Also goes Here  =\
	@                                        \/
	@==========================================
	pop {r0}	@ getting the origanl value of r0 
	sub r0,r0,#1	@ incrementing backwards from 15
	cmp r0,#0	@ making sure it isn't equal 0 yet
	bge loop	@ if its greater than 0 continue to print
	@==========================================


        @================================
        @ Exit
        @================================
exit:
	mov	r0,#0			@ Return a zero
        mov	r7,#SYSCALL_EXIT	@
        swi	0x0			@ Run the system call


	@====================
	@ print_string
	@====================
	@ Null-terminated string to print 	pointed to by r1
	@ the value in r1 is destroyed by this routine

	
@.thumb

print_string:

	push    {r0,r2,r7,r10,lr}
	@ Save r0,r2,r7,r10,lr on stack
	
	mov	r2,#3			@ The wrong value of r2
					@ Just so the code runs
					@ Your code below will overwrite
					@ with the proper version

	@==========================================
	@ Your code for part 3b goes here =\
	@                                  \/
	@==========================================
print:
	ldrb r3, [r1, r2] @ Getting the address 
	add r2,r2,#1	  @ incrementing r2 so it iterates through the string
	cmp r3,#0   	  @ checking if we are at a null point in the string
	bne print
done:	
	@==========================================
	@ The length of the string pointed to by r1
	@ Should be put in r2 by your code above
	@==========================================

	mov	r0,#STDOUT		@ R0 Print to stdout
					@ R1 points to our string
					@ R2 is the length
	mov	r7,#SYSCALL_WRITE	@ Load syscall number
	swi	0x0			@ System call

	pop	{r0,r2,r7,r10,pc}       @ pop r0,r2,r3,pc from stack

@.arm

        @#############################
	@ print_number
	@#############################
	@ r0 = value to print
	@ r0 is destroyed by this routine

print_number:
	push	{r10,LR}	@ Save r10 and return address on stack
        ldr	r10,=buffer	@ #1
        add	r10,r10,#10	@ #2

divide:
	bl	divide_by_10	@ divide by 10
	add	r8,r8,#0x30	@ adding the value stored in #0x30 with the value stored in r8
	strb	r8,[r10],#-1	@ store to buffer, increment pointer
	adds	r0,r7,#0	@ move quotient to r0, update status flag
	bne	divide		@ if quotient not zero then loop

write_out:
        add	r1,r10,#1	@ adjust pointer to print to beginning

        bl	print_string	@ print the string

        pop	{r10,LR}	@ restore saved values from stack

        mov	pc,lr		@ return from function

	##############################
	# divide_by_10
	##############################
	# r0=numerator
        # r4,r5 trashed
	# r7 = quotient, r8 = remainder

divide_by_10:
	ldr	r4,=429496730		@ 1/10 * 2^32
	sub	r5,r0,r0,lsr #30
	umull	r8,r7,r4,r5		@ {r8,r7}=r4*r5

	mov	r4,#10			@ calculate remainder
	mul	r8,r7,r4
	sub	r8,r0,r8

	mov	pc,lr

.data
message:	.string ": ECE471 is cool\n"

@ BSS
.lcomm buffer,11
