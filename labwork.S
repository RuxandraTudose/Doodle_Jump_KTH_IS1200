  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  
  hexasc:
	andi $a0, $a0, 0xf
	li $v0, 0x30
	addi $t0, $0, 0x09
	ble $a0, $t0, digits
	nop
	
#	li $v0, 0x37
        addi $v0, $v0, 0x7
	add $v0, $v0, $a0
	jr $ra
	nop

digits:
	
	add $v0, $v0, $a0
	jr $ra	
	nop
	
.global delay
    delay:

    li $t0, 0x12c #t0 is ms
    bgtu $t0, $0, while    #if (t0 > 0) go to while
    nop

while:

    beq $t0, $0 , exit #if (t0 == 0) go to exit
    nop    
    sub $t0, $t0, 1
    li $t1, 0x0 #t1 is i=0  
      
  for:
    addi $t1, $t1, 1
    bne $t1, 0x1267, for #if (t1 != 4711) go to for
    nop
    
    bne $t0, $0 , while #if (t0 != 0) while    
    nop
    
exit:

    jr $ra
    nop

.global time2string
	time2string:
	
	#stack : LAST IN FIRST OUT	    
        PUSH $s0
        PUSH $s1
        PUSH $ra

	add $s0, $0, $a0 #copy of address I receive as parameter
	add $s1, $0, $a1 #copy of time info I receive as paramete

	
   
	#first digit		
	move $t0, $s1 #nu pot sa prelucrez in s1 pt ca imi stric copia - bag in ceva temporar
	srl $t0, $t0, 12 #first digit now in t0: 0x1
	
	move $a0, $t0 #move to $ao because that's the register hexasc uses to convert as well 
	jal hexasc #call hexasc
	nop
	sb $v0, 0($s0) #move to address the obtained value
	
	#second digit
	move $t0, $s1 #copy again time info into temporary register 
	sra $t0, $t0, 8 #t0 now 0x16
	andi $t0, $t0, 0x0f #mask first nibble 
	
	move $a0, $t0
	jal hexasc
	nop
	sb $v0, 1($s0)
	
	#add ":"
	li $t0,0x3a #0x3a the ASCII value for ":"
	sb $t0, 2($s0)
	
	move $t0, $s1
	sra $t0, $t0, 4 #shift right one position t0: 0x165
	andi $t0, $t0, 0x00f #mask
	
	move $a0, $t0
	jal hexasc
	nop
	sb $v0, 3($s0)
	
	move $t0, $s1
	andi $t0, $t0, 0x000f #no more shifting, just mask
	
   	move $a0, $t0
    	jal hexasc
    	nop
    	sb $v0, 4($s0)

    	li $t0, 0x00
    	sb $t0, 5($s0)

    	POP $ra
    	POP $s1
    	POP $s0 

    	jr $ra
    	nop
    	
    	
.global enable_interrupt
enable_interrupt: 
    ei 
    jr $ra    
    nop
