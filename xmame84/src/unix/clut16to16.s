# vim:filetype=mips

# Slaanesh 2014

.set noreorder # don't reorder any instructions
.set noat      # don't use $at

.text
.align 4

# void clut16to16_rot0(unsigned short *dst, unsigned short *src, unsigned int *pal, int pixel_count)
#                                $a0                  $a1                $a2       $a3

.global clut16to16_rot0

clut16to16_rot0:
    srl     $a3, 2				# Divide count by 4 as we do 4 pixels in one iteration
clut16to16_rot0_loop:
    lhu     $t0, 0($a1)		    # Load 4 src pens
    lhu     $t1, 2($a1)
    lhu     $t2, 4($a1)
    lhu     $t3, 6($a1)
    sll     $t0, 2		    	# Convert number to 32-bit pointers
    sll     $t1, 2
    sll     $t2, 2
    sll     $t3, 2
    addu    $t0, $a2
    addu    $t1, $a2
    addu    $t2, $a2
    addu    $t3, $a2
    lhu     $t0, 0($t0)		    # Lookup "int *pal"
    lhu     $t1, 0($t1)	
    lhu     $t2, 0($t2)
    lhu     $t3, 0($t3)
    ins     $t0, $t1, 16, 16	# Merge 4 pixels into two 32-bit words
    ins     $t2, $t3, 16, 16
    sw      $t0, 0($a0)
    sw      $t2, 4($a0)
# sh      $t0, 0($a0)
# sh      $t1, 2($a0)
# sh      $t2, 4($a0)
# sh      $t3, 6($a0)
    addiu   $a0, 8				# Increment dst	(4x 16-bit pixels)
    addiu   $a3, -1				# Decrement loop counter
    bnez    $a3, clut16to16_rot0_loop
    addiu   $a1, 8				# Increment src (4x 16-bit indexes) (delay slot)
    jr      $ra
    nop
