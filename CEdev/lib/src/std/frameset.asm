	.assume adl=1
	.def	__frameset
	
__frameset:
	pop	de
	push	ix
	ld	ix,0
	add	ix,sp
	add	hl,sp
	ld	sp,hl
	ex	de,hl
	jp	(hl)