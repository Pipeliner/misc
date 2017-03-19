; constants <- stats.rb
pids equ 9875
vids equ 2038
nlen equ 128;	maximum len was 92
		.model tiny
		.386
		.code
		ORG 100h
_:
		jmp start
	fem db "File error",10,13,'$'
	vb db (vids*2) dup (?)
	vbname db 'vids.bin',0
	vbh dw ?
start:
		call loadVids
		mov ecx, 80000000h

deviceloop:
		call getVidPid
		cmp ax, 0FFFFh;	invalid Vendor ID -- device doesn't exist
		jnz enumfunctions
		add ecx, 0800h
		mov edx, 8
		jmp nextdevice

	enumfunctions:
		call isMultifunctional; 80h if true, 0 otherwise & flags set for eax
		jnz _8
			mov edx, 1
		jmp __
		_8:
			mov edx, 8
		__:
		mov ebx, 0; function index
	functionloop:
			call getVidPid
			cmp ax, 0FFFFh
			jz nextfunction

			call printBusAddr
			call printVidPid
	nextfunction:
			add ecx, 0100h
			inc ebx
			cmp ebx, edx
			jz nextdevice; only 8 (or 1) functions per device

			jmp functionloop

nextdevice:
		cmp edx, 8
		jz _mf
			add ecx, 0700h
		_mf:
		cmp ecx, 81000000h
		jnz deviceloop
; end of device loop

		ret

getVidPid proc
	push dx

	sti
	mov dx, 0CF8h
	mov eax, ecx
	out dx, eax

	mov dx, 0CFCh
	in eax, dx
	cli

	pop dx
	ret
getVidPid endp

getHeaderType proc
	push dx

	add ecx, 0Ch;	header type
	sti
	mov dx, 0CF8h
	mov eax, ecx
	out dx, eax

	mov dx, 0CFCh
	in eax, dx
	cli

	sub ecx, 0Ch
	pop dx
	ret
getHeaderType endp

isMultifunctional proc
	call getHeaderType
	and eax, 800000h
;	jz __nommf
;	call printVidPid
;	__nommf:
;	and eax, 800000h
	ret
isMultifunctional endp
;;;;;;;;;;;;;;;;;;;;;;;;
; in ecx
printBusAddr proc
	jmp pBAstart
	pstr db 'BS:DV.f $'

	pBAstart:

	push eax
	push dx
	push es
	push di

	push cs
	pop es
	mov di, offset pstr
	cld

	; bus,:
	mov eax, ecx
	shr eax, 16
	call h2
	inc di

	; device,.
	mov eax, ecx
	shr eax, 11
	and eax, 00011111b
	call h2
	inc di

	; function
	mov eax, ecx
	shr eax, 8
	and eax, 00000111b
	call h1

	mov dx, offset pstr
	mov ah, 9
	int 21h

	pop di
	pop es
	pop dx
	pop eax

	ret
printBusAddr endp
;;;;;;;;;;;;;;;;;;;;;;;;
; pid:vid in eax
printVidPid proc
	jmp estart
	outstr db 'VNDR:DEVC',10,13,'$'
estart:
	push eax
	push edx
	push es
	push di

	push cs
	pop es
	mov di, offset outstr
	cld

	call h8
	mov dx, offset outstr
	mov ah, 9
	int 21h

	pop di
	pop es
	pop edx
	pop eax
ret
printVidPid endp

loadVids proc
	mov ah, 3dh	; open
	mov al, 0h
	; ds == cs
	mov dx, offset vbname
	int 21h
	jc ferr

	mov ah, 3fh
	mov cx, vids*2
	mov dx, offset vb
	int 21h
	jc ferr
	ret

ferr:
	mov ah, 09h
	mov dx, offset fem
	int 21h
	ret

loadVids endp
;;;;;;;;;;;;;;;;;;;;;;;
h8:		push	eax
		; first lower half since vid there
		call	h4
		mov	al,':'
		stosb
		pop	eax
		shr eax, 16

h4:		push	ax
		mov	al,ah
		call	h2
		pop	ax

h2:		push	ax
		shr	al,4
		call	h1
		pop	ax

h1:		push	ax
		and	al,0Fh
		add	al,90h
		daa
		adc	al,40h
		daa
		stosb
		pop	ax
		ret

end _
