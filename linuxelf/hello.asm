
hello:     file format elf64-x86-64


Disassembly of section .interp:

0000000000400200 <.interp>:
  400200:	2f                   	(bad)  
  400201:	6c                   	ins    BYTE PTR es:[rdi],dx
  400202:	69 62 36 34 2f 6c 64 	imul   esp,DWORD PTR [rdx+0x36],0x646c2f34
  400209:	2d 6c 69 6e 75       	sub    eax,0x756e696c
  40020e:	78 2d                	js     40023d <_init-0x16b>
  400210:	78 38                	js     40024a <_init-0x15e>
  400212:	36 2d 36 34 2e 73    	ss sub eax,0x732e3436
  400218:	6f                   	outs   dx,DWORD PTR ds:[rsi]
  400219:	2e 32 00             	xor    al,BYTE PTR cs:[rax]

Disassembly of section .note.ABI-tag:

000000000040021c <.note.ABI-tag>:
  40021c:	04 00                	add    al,0x0
  40021e:	00 00                	add    BYTE PTR [rax],al
  400220:	10 00                	adc    BYTE PTR [rax],al
  400222:	00 00                	add    BYTE PTR [rax],al
  400224:	01 00                	add    DWORD PTR [rax],eax
  400226:	00 00                	add    BYTE PTR [rax],al
  400228:	47                   	rex.RXB
  400229:	4e 55                	rex.WRX push rbp
  40022b:	00 00                	add    BYTE PTR [rax],al
  40022d:	00 00                	add    BYTE PTR [rax],al
  40022f:	00 02                	add    BYTE PTR [rdx],al
  400231:	00 00                	add    BYTE PTR [rax],al
  400233:	00 06                	add    BYTE PTR [rsi],al
  400235:	00 00                	add    BYTE PTR [rax],al
  400237:	00 20                	add    BYTE PTR [rax],ah
  400239:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .note.gnu.build-id:

000000000040023c <.note.gnu.build-id>:
  40023c:	04 00                	add    al,0x0
  40023e:	00 00                	add    BYTE PTR [rax],al
  400240:	14 00                	adc    al,0x0
  400242:	00 00                	add    BYTE PTR [rax],al
  400244:	03 00                	add    eax,DWORD PTR [rax]
  400246:	00 00                	add    BYTE PTR [rax],al
  400248:	47                   	rex.RXB
  400249:	4e 55                	rex.WRX push rbp
  40024b:	00 81 0a b1 79 9e    	add    BYTE PTR [rcx-0x61864ef6],al
  400251:	e8 66 b9 a5 03       	call   3e5bbbc <_end+0x385b294>
  400256:	08 d0                	or     al,dl
  400258:	85 90 d3 45 a4 9c    	test   DWORD PTR [rax-0x635bba2d],edx
  40025e:	48 17                	rex.W (bad) 

Disassembly of section .gnu.hash:

0000000000400260 <.gnu.hash>:
  400260:	01 00                	add    DWORD PTR [rax],eax
  400262:	00 00                	add    BYTE PTR [rax],al
  400264:	01 00                	add    DWORD PTR [rax],eax
  400266:	00 00                	add    BYTE PTR [rax],al
  400268:	01 00                	add    DWORD PTR [rax],eax
	...

Disassembly of section .dynsym:

0000000000400280 <.dynsym>:
	...
  400298:	0b 00                	or     eax,DWORD PTR [rax]
  40029a:	00 00                	add    BYTE PTR [rax],al
  40029c:	12 00                	adc    al,BYTE PTR [rax]
	...
  4002ae:	00 00                	add    BYTE PTR [rax],al
  4002b0:	10 00                	adc    BYTE PTR [rax],al
  4002b2:	00 00                	add    BYTE PTR [rax],al
  4002b4:	12 00                	adc    al,BYTE PTR [rax]
	...
  4002c6:	00 00                	add    BYTE PTR [rax],al
  4002c8:	22 00                	and    al,BYTE PTR [rax]
  4002ca:	00 00                	add    BYTE PTR [rax],al
  4002cc:	20 00                	and    BYTE PTR [rax],al
	...

Disassembly of section .dynstr:

00000000004002e0 <.dynstr>:
  4002e0:	00 6c 69 62          	add    BYTE PTR [rcx+rbp*2+0x62],ch
  4002e4:	63 2e                	movsxd ebp,DWORD PTR [rsi]
  4002e6:	73 6f                	jae    400357 <_init-0x51>
  4002e8:	2e 36 00 70 75       	cs add BYTE PTR ss:[rax+0x75],dh
  4002ed:	74 73                	je     400362 <_init-0x46>
  4002ef:	00 5f 5f             	add    BYTE PTR [rdi+0x5f],bl
  4002f2:	6c                   	ins    BYTE PTR es:[rdi],dx
  4002f3:	69 62 63 5f 73 74 61 	imul   esp,DWORD PTR [rdx+0x63],0x6174735f
  4002fa:	72 74                	jb     400370 <_init-0x38>
  4002fc:	5f                   	pop    rdi
  4002fd:	6d                   	ins    DWORD PTR es:[rdi],dx
  4002fe:	61                   	(bad)  
  4002ff:	69 6e 00 5f 5f 67 6d 	imul   ebp,DWORD PTR [rsi+0x0],0x6d675f5f
  400306:	6f                   	outs   dx,DWORD PTR ds:[rsi]
  400307:	6e                   	outs   dx,BYTE PTR ds:[rsi]
  400308:	5f                   	pop    rdi
  400309:	73 74                	jae    40037f <_init-0x29>
  40030b:	61                   	(bad)  
  40030c:	72 74                	jb     400382 <_init-0x26>
  40030e:	5f                   	pop    rdi
  40030f:	5f                   	pop    rdi
  400310:	00 47 4c             	add    BYTE PTR [rdi+0x4c],al
  400313:	49                   	rex.WB
  400314:	42                   	rex.X
  400315:	43 5f                	rex.XB pop r15
  400317:	32 2e                	xor    ch,BYTE PTR [rsi]
  400319:	32 2e                	xor    ch,BYTE PTR [rsi]
  40031b:	35                   	.byte 0x35
	...

Disassembly of section .gnu.version:

000000000040031e <.gnu.version>:
  40031e:	00 00                	add    BYTE PTR [rax],al
  400320:	02 00                	add    al,BYTE PTR [rax]
  400322:	02 00                	add    al,BYTE PTR [rax]
	...

Disassembly of section .gnu.version_r:

0000000000400328 <.gnu.version_r>:
  400328:	01 00                	add    DWORD PTR [rax],eax
  40032a:	01 00                	add    DWORD PTR [rax],eax
  40032c:	01 00                	add    DWORD PTR [rax],eax
  40032e:	00 00                	add    BYTE PTR [rax],al
  400330:	10 00                	adc    BYTE PTR [rax],al
  400332:	00 00                	add    BYTE PTR [rax],al
  400334:	00 00                	add    BYTE PTR [rax],al
  400336:	00 00                	add    BYTE PTR [rax],al
  400338:	75 1a                	jne    400354 <_init-0x54>
  40033a:	69 09 00 00 02 00    	imul   ecx,DWORD PTR [rcx],0x20000
  400340:	31 00                	xor    DWORD PTR [rax],eax
  400342:	00 00                	add    BYTE PTR [rax],al
  400344:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .rela.dyn:

0000000000400348 <.rela.dyn>:
  400348:	d8 08                	fmul   DWORD PTR [rax]
  40034a:	60                   	(bad)  
  40034b:	00 00                	add    BYTE PTR [rax],al
  40034d:	00 00                	add    BYTE PTR [rax],al
  40034f:	00 06                	add    BYTE PTR [rsi],al
  400351:	00 00                	add    BYTE PTR [rax],al
  400353:	00 03                	add    BYTE PTR [rbx],al
	...

Disassembly of section .rela.plt:

0000000000400360 <.rela.plt>:
  400360:	f8                   	clc    
  400361:	08 60 00             	or     BYTE PTR [rax+0x0],ah
  400364:	00 00                	add    BYTE PTR [rax],al
  400366:	00 00                	add    BYTE PTR [rax],al
  400368:	07                   	(bad)  
  400369:	00 00                	add    BYTE PTR [rax],al
  40036b:	00 01                	add    BYTE PTR [rcx],al
	...
  400379:	09 60 00             	or     DWORD PTR [rax+0x0],esp
  40037c:	00 00                	add    BYTE PTR [rax],al
  40037e:	00 00                	add    BYTE PTR [rax],al
  400380:	07                   	(bad)  
  400381:	00 00                	add    BYTE PTR [rax],al
  400383:	00 02                	add    BYTE PTR [rdx],al
	...
  40038d:	00 00                	add    BYTE PTR [rax],al
  40038f:	00 08                	add    BYTE PTR [rax],cl
  400391:	09 60 00             	or     DWORD PTR [rax+0x0],esp
  400394:	00 00                	add    BYTE PTR [rax],al
  400396:	00 00                	add    BYTE PTR [rax],al
  400398:	07                   	(bad)  
  400399:	00 00                	add    BYTE PTR [rax],al
  40039b:	00 03                	add    BYTE PTR [rbx],al
	...

Disassembly of section .init:

00000000004003a8 <_init>:
  4003a8:	48 83 ec 08          	sub    rsp,0x8
  4003ac:	48 8b 05 25 05 20 00 	mov    rax,QWORD PTR [rip+0x200525]        # 6008d8 <_DYNAMIC+0x1d0>
  4003b3:	48 85 c0             	test   rax,rax
  4003b6:	74 05                	je     4003bd <_init+0x15>
  4003b8:	e8 43 00 00 00       	call   400400 <__gmon_start__@plt>
  4003bd:	48 83 c4 08          	add    rsp,0x8
  4003c1:	c3                   	ret    

Disassembly of section .plt:

00000000004003d0 <puts@plt-0x10>:
  4003d0:	ff 35 12 05 20 00    	push   QWORD PTR [rip+0x200512]        # 6008e8 <_GLOBAL_OFFSET_TABLE_+0x8>
  4003d6:	ff 25 14 05 20 00    	jmp    QWORD PTR [rip+0x200514]        # 6008f0 <_GLOBAL_OFFSET_TABLE_+0x10>
  4003dc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

00000000004003e0 <puts@plt>:
  4003e0:	ff 25 12 05 20 00    	jmp    QWORD PTR [rip+0x200512]        # 6008f8 <_GLOBAL_OFFSET_TABLE_+0x18>
  4003e6:	68 00 00 00 00       	push   0x0
  4003eb:	e9 e0 ff ff ff       	jmp    4003d0 <_init+0x28>

00000000004003f0 <__libc_start_main@plt>:
  4003f0:	ff 25 0a 05 20 00    	jmp    QWORD PTR [rip+0x20050a]        # 600900 <_GLOBAL_OFFSET_TABLE_+0x20>
  4003f6:	68 01 00 00 00       	push   0x1
  4003fb:	e9 d0 ff ff ff       	jmp    4003d0 <_init+0x28>

0000000000400400 <__gmon_start__@plt>:
  400400:	ff 25 02 05 20 00    	jmp    QWORD PTR [rip+0x200502]        # 600908 <_GLOBAL_OFFSET_TABLE_+0x28>
  400406:	68 02 00 00 00       	push   0x2
  40040b:	e9 c0 ff ff ff       	jmp    4003d0 <_init+0x28>

Disassembly of section .text:

0000000000400410 <_start>:
  400410:	31 ed                	xor    ebp,ebp
  400412:	49 89 d1             	mov    r9,rdx
  400415:	5e                   	pop    rsi
  400416:	48 89 e2             	mov    rdx,rsp
  400419:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
  40041d:	50                   	push   rax
  40041e:	54                   	push   rsp
  40041f:	49 c7 c0 a0 05 40 00 	mov    r8,0x4005a0
  400426:	48 c7 c1 30 05 40 00 	mov    rcx,0x400530
  40042d:	48 c7 c7 06 05 40 00 	mov    rdi,0x400506
  400434:	e8 b7 ff ff ff       	call   4003f0 <__libc_start_main@plt>
  400439:	f4                   	hlt    
  40043a:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

0000000000400440 <deregister_tm_clones>:
  400440:	b8 27 09 60 00       	mov    eax,0x600927
  400445:	55                   	push   rbp
  400446:	48 2d 20 09 60 00    	sub    rax,0x600920
  40044c:	48 83 f8 0e          	cmp    rax,0xe
  400450:	48 89 e5             	mov    rbp,rsp
  400453:	76 1b                	jbe    400470 <deregister_tm_clones+0x30>
  400455:	b8 00 00 00 00       	mov    eax,0x0
  40045a:	48 85 c0             	test   rax,rax
  40045d:	74 11                	je     400470 <deregister_tm_clones+0x30>
  40045f:	5d                   	pop    rbp
  400460:	bf 20 09 60 00       	mov    edi,0x600920
  400465:	ff e0                	jmp    rax
  400467:	66 0f 1f 84 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]
  40046e:	00 00 
  400470:	5d                   	pop    rbp
  400471:	c3                   	ret    
  400472:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 nop WORD PTR cs:[rax+rax*1+0x0]
  400479:	1f 84 00 00 00 00 00 

0000000000400480 <register_tm_clones>:
  400480:	be 20 09 60 00       	mov    esi,0x600920
  400485:	55                   	push   rbp
  400486:	48 81 ee 20 09 60 00 	sub    rsi,0x600920
  40048d:	48 c1 fe 03          	sar    rsi,0x3
  400491:	48 89 e5             	mov    rbp,rsp
  400494:	48 89 f0             	mov    rax,rsi
  400497:	48 c1 e8 3f          	shr    rax,0x3f
  40049b:	48 01 c6             	add    rsi,rax
  40049e:	48 d1 fe             	sar    rsi,1
  4004a1:	74 15                	je     4004b8 <register_tm_clones+0x38>
  4004a3:	b8 00 00 00 00       	mov    eax,0x0
  4004a8:	48 85 c0             	test   rax,rax
  4004ab:	74 0b                	je     4004b8 <register_tm_clones+0x38>
  4004ad:	5d                   	pop    rbp
  4004ae:	bf 20 09 60 00       	mov    edi,0x600920
  4004b3:	ff e0                	jmp    rax
  4004b5:	0f 1f 00             	nop    DWORD PTR [rax]
  4004b8:	5d                   	pop    rbp
  4004b9:	c3                   	ret    
  4004ba:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]

00000000004004c0 <__do_global_dtors_aux>:
  4004c0:	80 3d 59 04 20 00 00 	cmp    BYTE PTR [rip+0x200459],0x0        # 600920 <__TMC_END__>
  4004c7:	75 11                	jne    4004da <__do_global_dtors_aux+0x1a>
  4004c9:	55                   	push   rbp
  4004ca:	48 89 e5             	mov    rbp,rsp
  4004cd:	e8 6e ff ff ff       	call   400440 <deregister_tm_clones>
  4004d2:	5d                   	pop    rbp
  4004d3:	c6 05 46 04 20 00 01 	mov    BYTE PTR [rip+0x200446],0x1        # 600920 <__TMC_END__>
  4004da:	f3 c3                	repz ret 
  4004dc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

00000000004004e0 <frame_dummy>:
  4004e0:	bf 00 07 60 00       	mov    edi,0x600700
  4004e5:	48 83 3f 00          	cmp    QWORD PTR [rdi],0x0
  4004e9:	75 05                	jne    4004f0 <frame_dummy+0x10>
  4004eb:	eb 93                	jmp    400480 <register_tm_clones>
  4004ed:	0f 1f 00             	nop    DWORD PTR [rax]
  4004f0:	b8 00 00 00 00       	mov    eax,0x0
  4004f5:	48 85 c0             	test   rax,rax
  4004f8:	74 f1                	je     4004eb <frame_dummy+0xb>
  4004fa:	55                   	push   rbp
  4004fb:	48 89 e5             	mov    rbp,rsp
  4004fe:	ff d0                	call   rax
  400500:	5d                   	pop    rbp
  400501:	e9 7a ff ff ff       	jmp    400480 <register_tm_clones>

0000000000400506 <main>:
  400506:	55                   	push   rbp
  400507:	48 89 e5             	mov    rbp,rsp
  40050a:	48 83 ec 10          	sub    rsp,0x10
  40050e:	89 7d fc             	mov    DWORD PTR [rbp-0x4],edi
  400511:	48 89 75 f0          	mov    QWORD PTR [rbp-0x10],rsi
  400515:	bf b4 05 40 00       	mov    edi,0x4005b4
  40051a:	e8 c1 fe ff ff       	call   4003e0 <puts@plt>
  40051f:	b8 00 00 00 00       	mov    eax,0x0
  400524:	c9                   	leave  
  400525:	c3                   	ret    
  400526:	66 2e 0f 1f 84 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  40052d:	00 00 00 

0000000000400530 <__libc_csu_init>:
  400530:	41 57                	push   r15
  400532:	41 89 ff             	mov    r15d,edi
  400535:	41 56                	push   r14
  400537:	49 89 f6             	mov    r14,rsi
  40053a:	41 55                	push   r13
  40053c:	49 89 d5             	mov    r13,rdx
  40053f:	41 54                	push   r12
  400541:	4c 8d 25 a8 01 20 00 	lea    r12,[rip+0x2001a8]        # 6006f0 <__frame_dummy_init_array_entry>
  400548:	55                   	push   rbp
  400549:	48 8d 2d a8 01 20 00 	lea    rbp,[rip+0x2001a8]        # 6006f8 <__init_array_end>
  400550:	53                   	push   rbx
  400551:	4c 29 e5             	sub    rbp,r12
  400554:	31 db                	xor    ebx,ebx
  400556:	48 c1 fd 03          	sar    rbp,0x3
  40055a:	48 83 ec 08          	sub    rsp,0x8
  40055e:	e8 45 fe ff ff       	call   4003a8 <_init>
  400563:	48 85 ed             	test   rbp,rbp
  400566:	74 1e                	je     400586 <__libc_csu_init+0x56>
  400568:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  40056f:	00 
  400570:	4c 89 ea             	mov    rdx,r13
  400573:	4c 89 f6             	mov    rsi,r14
  400576:	44 89 ff             	mov    edi,r15d
  400579:	41 ff 14 dc          	call   QWORD PTR [r12+rbx*8]
  40057d:	48 83 c3 01          	add    rbx,0x1
  400581:	48 39 eb             	cmp    rbx,rbp
  400584:	75 ea                	jne    400570 <__libc_csu_init+0x40>
  400586:	48 83 c4 08          	add    rsp,0x8
  40058a:	5b                   	pop    rbx
  40058b:	5d                   	pop    rbp
  40058c:	41 5c                	pop    r12
  40058e:	41 5d                	pop    r13
  400590:	41 5e                	pop    r14
  400592:	41 5f                	pop    r15
  400594:	c3                   	ret    
  400595:	66 66 2e 0f 1f 84 00 	data16 nop WORD PTR cs:[rax+rax*1+0x0]
  40059c:	00 00 00 00 

00000000004005a0 <__libc_csu_fini>:
  4005a0:	f3 c3                	repz ret 

Disassembly of section .fini:

00000000004005a4 <_fini>:
  4005a4:	48 83 ec 08          	sub    rsp,0x8
  4005a8:	48 83 c4 08          	add    rsp,0x8
  4005ac:	c3                   	ret    

Disassembly of section .rodata:

00000000004005b0 <_IO_stdin_used>:
  4005b0:	01 00                	add    DWORD PTR [rax],eax
  4005b2:	02 00                	add    al,BYTE PTR [rax]
  4005b4:	48                   	rex.W
  4005b5:	65 6c                	gs ins BYTE PTR es:[rdi],dx
  4005b7:	6c                   	ins    BYTE PTR es:[rdi],dx
  4005b8:	6f                   	outs   dx,DWORD PTR ds:[rsi]
  4005b9:	20 77 6f             	and    BYTE PTR [rdi+0x6f],dh
  4005bc:	72 6c                	jb     40062a <_IO_stdin_used+0x7a>
  4005be:	64 21 00             	and    DWORD PTR fs:[rax],eax

Disassembly of section .eh_frame_hdr:

00000000004005c4 <.eh_frame_hdr>:
  4005c4:	01 1b                	add    DWORD PTR [rbx],ebx
  4005c6:	03 3b                	add    edi,DWORD PTR [rbx]
  4005c8:	30 00                	xor    BYTE PTR [rax],al
  4005ca:	00 00                	add    BYTE PTR [rax],al
  4005cc:	05 00 00 00 0c       	add    eax,0xc000000
  4005d1:	fe                   	(bad)  
  4005d2:	ff                   	(bad)  
  4005d3:	ff                   	(bad)  
  4005d4:	7c 00                	jl     4005d6 <_IO_stdin_used+0x26>
  4005d6:	00 00                	add    BYTE PTR [rax],al
  4005d8:	4c fe                	rex.WR (bad) 
  4005da:	ff                   	(bad)  
  4005db:	ff 4c 00 00          	dec    DWORD PTR [rax+rax*1+0x0]
  4005df:	00 42 ff             	add    BYTE PTR [rdx-0x1],al
  4005e2:	ff                   	(bad)  
  4005e3:	ff a4 00 00 00 6c ff 	jmp    QWORD PTR [rax+rax*1-0x940000]
  4005ea:	ff                   	(bad)  
  4005eb:	ff c4                	inc    esp
  4005ed:	00 00                	add    BYTE PTR [rax],al
  4005ef:	00 dc                	add    ah,bl
  4005f1:	ff                   	(bad)  
  4005f2:	ff                   	(bad)  
  4005f3:	ff 0c 01             	dec    DWORD PTR [rcx+rax*1]
	...

Disassembly of section .eh_frame:

00000000004005f8 <__FRAME_END__-0xf0>:
  4005f8:	14 00                	adc    al,0x0
  4005fa:	00 00                	add    BYTE PTR [rax],al
  4005fc:	00 00                	add    BYTE PTR [rax],al
  4005fe:	00 00                	add    BYTE PTR [rax],al
  400600:	01 7a 52             	add    DWORD PTR [rdx+0x52],edi
  400603:	00 01                	add    BYTE PTR [rcx],al
  400605:	78 10                	js     400617 <_IO_stdin_used+0x67>
  400607:	01 1b                	add    DWORD PTR [rbx],ebx
  400609:	0c 07                	or     al,0x7
  40060b:	08 90 01 07 10 14    	or     BYTE PTR [rax+0x14100701],dl
  400611:	00 00                	add    BYTE PTR [rax],al
  400613:	00 1c 00             	add    BYTE PTR [rax+rax*1],bl
  400616:	00 00                	add    BYTE PTR [rax],al
  400618:	f8                   	clc    
  400619:	fd                   	std    
  40061a:	ff                   	(bad)  
  40061b:	ff 2a                	jmp    FWORD PTR [rdx]
	...
  400625:	00 00                	add    BYTE PTR [rax],al
  400627:	00 14 00             	add    BYTE PTR [rax+rax*1],dl
  40062a:	00 00                	add    BYTE PTR [rax],al
  40062c:	00 00                	add    BYTE PTR [rax],al
  40062e:	00 00                	add    BYTE PTR [rax],al
  400630:	01 7a 52             	add    DWORD PTR [rdx+0x52],edi
  400633:	00 01                	add    BYTE PTR [rcx],al
  400635:	78 10                	js     400647 <_IO_stdin_used+0x97>
  400637:	01 1b                	add    DWORD PTR [rbx],ebx
  400639:	0c 07                	or     al,0x7
  40063b:	08 90 01 00 00 24    	or     BYTE PTR [rax+0x24000001],dl
  400641:	00 00                	add    BYTE PTR [rax],al
  400643:	00 1c 00             	add    BYTE PTR [rax+rax*1],bl
  400646:	00 00                	add    BYTE PTR [rax],al
  400648:	88 fd                	mov    ch,bh
  40064a:	ff                   	(bad)  
  40064b:	ff 40 00             	inc    DWORD PTR [rax+0x0]
  40064e:	00 00                	add    BYTE PTR [rax],al
  400650:	00 0e                	add    BYTE PTR [rsi],cl
  400652:	10 46 0e             	adc    BYTE PTR [rsi+0xe],al
  400655:	18 4a 0f             	sbb    BYTE PTR [rdx+0xf],cl
  400658:	0b 77 08             	or     esi,DWORD PTR [rdi+0x8]
  40065b:	80 00 3f             	add    BYTE PTR [rax],0x3f
  40065e:	1a 3b                	sbb    bh,BYTE PTR [rbx]
  400660:	2a 33                	sub    dh,BYTE PTR [rbx]
  400662:	24 22                	and    al,0x22
  400664:	00 00                	add    BYTE PTR [rax],al
  400666:	00 00                	add    BYTE PTR [rax],al
  400668:	1c 00                	sbb    al,0x0
  40066a:	00 00                	add    BYTE PTR [rax],al
  40066c:	44 00 00             	add    BYTE PTR [rax],r8b
  40066f:	00 96 fe ff ff 20    	add    BYTE PTR [rsi+0x20fffffe],dl
  400675:	00 00                	add    BYTE PTR [rax],al
  400677:	00 00                	add    BYTE PTR [rax],al
  400679:	41 0e                	rex.B (bad) 
  40067b:	10 86 02 43 0d 06    	adc    BYTE PTR [rsi+0x60d4302],al
  400681:	5b                   	pop    rbx
  400682:	0c 07                	or     al,0x7
  400684:	08 00                	or     BYTE PTR [rax],al
  400686:	00 00                	add    BYTE PTR [rax],al
  400688:	44 00 00             	add    BYTE PTR [rax],r8b
  40068b:	00 64 00 00          	add    BYTE PTR [rax+rax*1+0x0],ah
  40068f:	00 a0 fe ff ff 65    	add    BYTE PTR [rax+0x65fffffe],ah
  400695:	00 00                	add    BYTE PTR [rax],al
  400697:	00 00                	add    BYTE PTR [rax],al
  400699:	42 0e                	rex.X (bad) 
  40069b:	10 8f 02 45 0e 18    	adc    BYTE PTR [rdi+0x180e4502],cl
  4006a1:	8e 03                	mov    es,WORD PTR [rbx]
  4006a3:	45 0e                	rex.RB (bad) 
  4006a5:	20 8d 04 45 0e 28    	and    BYTE PTR [rbp+0x280e4504],cl
  4006ab:	8c 05 48 0e 30 86    	mov    WORD PTR [rip+0xffffffff86300e48],es        # ffffffff867014f9 <_end+0xffffffff86100bd1>
  4006b1:	06                   	(bad)  
  4006b2:	48 0e                	rex.W (bad) 
  4006b4:	38 83 07 4d 0e 40    	cmp    BYTE PTR [rbx+0x400e4d07],al
  4006ba:	6c                   	ins    BYTE PTR es:[rdi],dx
  4006bb:	0e                   	(bad)  
  4006bc:	38 41 0e             	cmp    BYTE PTR [rcx+0xe],al
  4006bf:	30 41 0e             	xor    BYTE PTR [rcx+0xe],al
  4006c2:	28 42 0e             	sub    BYTE PTR [rdx+0xe],al
  4006c5:	20 42 0e             	and    BYTE PTR [rdx+0xe],al
  4006c8:	18 42 0e             	sbb    BYTE PTR [rdx+0xe],al
  4006cb:	10 42 0e             	adc    BYTE PTR [rdx+0xe],al
  4006ce:	08 00                	or     BYTE PTR [rax],al
  4006d0:	14 00                	adc    al,0x0
  4006d2:	00 00                	add    BYTE PTR [rax],al
  4006d4:	ac                   	lods   al,BYTE PTR ds:[rsi]
  4006d5:	00 00                	add    BYTE PTR [rax],al
  4006d7:	00 c8                	add    al,cl
  4006d9:	fe                   	(bad)  
  4006da:	ff                   	(bad)  
  4006db:	ff 02                	inc    DWORD PTR [rdx]
	...

00000000004006e8 <__FRAME_END__>:
  4006e8:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .init_array:

00000000006006f0 <__frame_dummy_init_array_entry>:
  6006f0:	e0 04                	loopne 6006f6 <__frame_dummy_init_array_entry+0x6>
  6006f2:	40 00 00             	add    BYTE PTR [rax],al
  6006f5:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .fini_array:

00000000006006f8 <__do_global_dtors_aux_fini_array_entry>:
  6006f8:	c0 04 40 00          	rol    BYTE PTR [rax+rax*2],0x0
  6006fc:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .jcr:

0000000000600700 <__JCR_END__>:
	...

Disassembly of section .dynamic:

0000000000600708 <_DYNAMIC>:
  600708:	01 00                	add    DWORD PTR [rax],eax
  60070a:	00 00                	add    BYTE PTR [rax],al
  60070c:	00 00                	add    BYTE PTR [rax],al
  60070e:	00 00                	add    BYTE PTR [rax],al
  600710:	01 00                	add    DWORD PTR [rax],eax
  600712:	00 00                	add    BYTE PTR [rax],al
  600714:	00 00                	add    BYTE PTR [rax],al
  600716:	00 00                	add    BYTE PTR [rax],al
  600718:	0c 00                	or     al,0x0
  60071a:	00 00                	add    BYTE PTR [rax],al
  60071c:	00 00                	add    BYTE PTR [rax],al
  60071e:	00 00                	add    BYTE PTR [rax],al
  600720:	a8 03                	test   al,0x3
  600722:	40 00 00             	add    BYTE PTR [rax],al
  600725:	00 00                	add    BYTE PTR [rax],al
  600727:	00 0d 00 00 00 00    	add    BYTE PTR [rip+0x0],cl        # 60072d <_DYNAMIC+0x25>
  60072d:	00 00                	add    BYTE PTR [rax],al
  60072f:	00 a4 05 40 00 00 00 	add    BYTE PTR [rbp+rax*1+0x40],ah
  600736:	00 00                	add    BYTE PTR [rax],al
  600738:	19 00                	sbb    DWORD PTR [rax],eax
  60073a:	00 00                	add    BYTE PTR [rax],al
  60073c:	00 00                	add    BYTE PTR [rax],al
  60073e:	00 00                	add    BYTE PTR [rax],al
  600740:	f0 06                	lock (bad) 
  600742:	60                   	(bad)  
  600743:	00 00                	add    BYTE PTR [rax],al
  600745:	00 00                	add    BYTE PTR [rax],al
  600747:	00 1b                	add    BYTE PTR [rbx],bl
  600749:	00 00                	add    BYTE PTR [rax],al
  60074b:	00 00                	add    BYTE PTR [rax],al
  60074d:	00 00                	add    BYTE PTR [rax],al
  60074f:	00 08                	add    BYTE PTR [rax],cl
  600751:	00 00                	add    BYTE PTR [rax],al
  600753:	00 00                	add    BYTE PTR [rax],al
  600755:	00 00                	add    BYTE PTR [rax],al
  600757:	00 1a                	add    BYTE PTR [rdx],bl
  600759:	00 00                	add    BYTE PTR [rax],al
  60075b:	00 00                	add    BYTE PTR [rax],al
  60075d:	00 00                	add    BYTE PTR [rax],al
  60075f:	00 f8                	add    al,bh
  600761:	06                   	(bad)  
  600762:	60                   	(bad)  
  600763:	00 00                	add    BYTE PTR [rax],al
  600765:	00 00                	add    BYTE PTR [rax],al
  600767:	00 1c 00             	add    BYTE PTR [rax+rax*1],bl
  60076a:	00 00                	add    BYTE PTR [rax],al
  60076c:	00 00                	add    BYTE PTR [rax],al
  60076e:	00 00                	add    BYTE PTR [rax],al
  600770:	08 00                	or     BYTE PTR [rax],al
  600772:	00 00                	add    BYTE PTR [rax],al
  600774:	00 00                	add    BYTE PTR [rax],al
  600776:	00 00                	add    BYTE PTR [rax],al
  600778:	f5                   	cmc    
  600779:	fe                   	(bad)  
  60077a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
  60077d:	00 00                	add    BYTE PTR [rax],al
  60077f:	00 60 02             	add    BYTE PTR [rax+0x2],ah
  600782:	40 00 00             	add    BYTE PTR [rax],al
  600785:	00 00                	add    BYTE PTR [rax],al
  600787:	00 05 00 00 00 00    	add    BYTE PTR [rip+0x0],al        # 60078d <_DYNAMIC+0x85>
  60078d:	00 00                	add    BYTE PTR [rax],al
  60078f:	00 e0                	add    al,ah
  600791:	02 40 00             	add    al,BYTE PTR [rax+0x0]
  600794:	00 00                	add    BYTE PTR [rax],al
  600796:	00 00                	add    BYTE PTR [rax],al
  600798:	06                   	(bad)  
  600799:	00 00                	add    BYTE PTR [rax],al
  60079b:	00 00                	add    BYTE PTR [rax],al
  60079d:	00 00                	add    BYTE PTR [rax],al
  60079f:	00 80 02 40 00 00    	add    BYTE PTR [rax+0x4002],al
  6007a5:	00 00                	add    BYTE PTR [rax],al
  6007a7:	00 0a                	add    BYTE PTR [rdx],cl
  6007a9:	00 00                	add    BYTE PTR [rax],al
  6007ab:	00 00                	add    BYTE PTR [rax],al
  6007ad:	00 00                	add    BYTE PTR [rax],al
  6007af:	00 3d 00 00 00 00    	add    BYTE PTR [rip+0x0],bh        # 6007b5 <_DYNAMIC+0xad>
  6007b5:	00 00                	add    BYTE PTR [rax],al
  6007b7:	00 0b                	add    BYTE PTR [rbx],cl
  6007b9:	00 00                	add    BYTE PTR [rax],al
  6007bb:	00 00                	add    BYTE PTR [rax],al
  6007bd:	00 00                	add    BYTE PTR [rax],al
  6007bf:	00 18                	add    BYTE PTR [rax],bl
  6007c1:	00 00                	add    BYTE PTR [rax],al
  6007c3:	00 00                	add    BYTE PTR [rax],al
  6007c5:	00 00                	add    BYTE PTR [rax],al
  6007c7:	00 15 00 00 00 00    	add    BYTE PTR [rip+0x0],dl        # 6007cd <_DYNAMIC+0xc5>
	...
  6007d5:	00 00                	add    BYTE PTR [rax],al
  6007d7:	00 03                	add    BYTE PTR [rbx],al
  6007d9:	00 00                	add    BYTE PTR [rax],al
  6007db:	00 00                	add    BYTE PTR [rax],al
  6007dd:	00 00                	add    BYTE PTR [rax],al
  6007df:	00 e0                	add    al,ah
  6007e1:	08 60 00             	or     BYTE PTR [rax+0x0],ah
  6007e4:	00 00                	add    BYTE PTR [rax],al
  6007e6:	00 00                	add    BYTE PTR [rax],al
  6007e8:	02 00                	add    al,BYTE PTR [rax]
  6007ea:	00 00                	add    BYTE PTR [rax],al
  6007ec:	00 00                	add    BYTE PTR [rax],al
  6007ee:	00 00                	add    BYTE PTR [rax],al
  6007f0:	48 00 00             	rex.W add BYTE PTR [rax],al
  6007f3:	00 00                	add    BYTE PTR [rax],al
  6007f5:	00 00                	add    BYTE PTR [rax],al
  6007f7:	00 14 00             	add    BYTE PTR [rax+rax*1],dl
  6007fa:	00 00                	add    BYTE PTR [rax],al
  6007fc:	00 00                	add    BYTE PTR [rax],al
  6007fe:	00 00                	add    BYTE PTR [rax],al
  600800:	07                   	(bad)  
  600801:	00 00                	add    BYTE PTR [rax],al
  600803:	00 00                	add    BYTE PTR [rax],al
  600805:	00 00                	add    BYTE PTR [rax],al
  600807:	00 17                	add    BYTE PTR [rdi],dl
  600809:	00 00                	add    BYTE PTR [rax],al
  60080b:	00 00                	add    BYTE PTR [rax],al
  60080d:	00 00                	add    BYTE PTR [rax],al
  60080f:	00 60 03             	add    BYTE PTR [rax+0x3],ah
  600812:	40 00 00             	add    BYTE PTR [rax],al
  600815:	00 00                	add    BYTE PTR [rax],al
  600817:	00 07                	add    BYTE PTR [rdi],al
  600819:	00 00                	add    BYTE PTR [rax],al
  60081b:	00 00                	add    BYTE PTR [rax],al
  60081d:	00 00                	add    BYTE PTR [rax],al
  60081f:	00 48 03             	add    BYTE PTR [rax+0x3],cl
  600822:	40 00 00             	add    BYTE PTR [rax],al
  600825:	00 00                	add    BYTE PTR [rax],al
  600827:	00 08                	add    BYTE PTR [rax],cl
  600829:	00 00                	add    BYTE PTR [rax],al
  60082b:	00 00                	add    BYTE PTR [rax],al
  60082d:	00 00                	add    BYTE PTR [rax],al
  60082f:	00 18                	add    BYTE PTR [rax],bl
  600831:	00 00                	add    BYTE PTR [rax],al
  600833:	00 00                	add    BYTE PTR [rax],al
  600835:	00 00                	add    BYTE PTR [rax],al
  600837:	00 09                	add    BYTE PTR [rcx],cl
  600839:	00 00                	add    BYTE PTR [rax],al
  60083b:	00 00                	add    BYTE PTR [rax],al
  60083d:	00 00                	add    BYTE PTR [rax],al
  60083f:	00 18                	add    BYTE PTR [rax],bl
  600841:	00 00                	add    BYTE PTR [rax],al
  600843:	00 00                	add    BYTE PTR [rax],al
  600845:	00 00                	add    BYTE PTR [rax],al
  600847:	00 fe                	add    dh,bh
  600849:	ff                   	(bad)  
  60084a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
  60084d:	00 00                	add    BYTE PTR [rax],al
  60084f:	00 28                	add    BYTE PTR [rax],ch
  600851:	03 40 00             	add    eax,DWORD PTR [rax+0x0]
  600854:	00 00                	add    BYTE PTR [rax],al
  600856:	00 00                	add    BYTE PTR [rax],al
  600858:	ff                   	(bad)  
  600859:	ff                   	(bad)  
  60085a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
  60085d:	00 00                	add    BYTE PTR [rax],al
  60085f:	00 01                	add    BYTE PTR [rcx],al
  600861:	00 00                	add    BYTE PTR [rax],al
  600863:	00 00                	add    BYTE PTR [rax],al
  600865:	00 00                	add    BYTE PTR [rax],al
  600867:	00 f0                	add    al,dh
  600869:	ff                   	(bad)  
  60086a:	ff 6f 00             	jmp    FWORD PTR [rdi+0x0]
  60086d:	00 00                	add    BYTE PTR [rax],al
  60086f:	00 1e                	add    BYTE PTR [rsi],bl
  600871:	03 40 00             	add    eax,DWORD PTR [rax+0x0]
	...

Disassembly of section .got:

00000000006008d8 <.got>:
	...

Disassembly of section .got.plt:

00000000006008e0 <_GLOBAL_OFFSET_TABLE_>:
  6008e0:	08 07                	or     BYTE PTR [rdi],al
  6008e2:	60                   	(bad)  
	...
  6008f7:	00 e6                	add    dh,ah
  6008f9:	03 40 00             	add    eax,DWORD PTR [rax+0x0]
  6008fc:	00 00                	add    BYTE PTR [rax],al
  6008fe:	00 00                	add    BYTE PTR [rax],al
  600900:	f6 03 40             	test   BYTE PTR [rbx],0x40
  600903:	00 00                	add    BYTE PTR [rax],al
  600905:	00 00                	add    BYTE PTR [rax],al
  600907:	00 06                	add    BYTE PTR [rsi],al
  600909:	04 40                	add    al,0x40
  60090b:	00 00                	add    BYTE PTR [rax],al
  60090d:	00 00                	add    BYTE PTR [rax],al
	...

Disassembly of section .data:

0000000000600910 <__data_start>:
	...

0000000000600918 <__dso_handle>:
	...

Disassembly of section .bss:

0000000000600920 <__bss_start>:
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	47                   	rex.RXB
   1:	43                   	rex.XB
   2:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
   5:	28 44 65 62          	sub    BYTE PTR [rbp+riz*2+0x62],al
   9:	69 61 6e 20 34 2e 39 	imul   esp,DWORD PTR [rcx+0x6e],0x392e3420
  10:	2e 32 2d 31 30 29 20 	xor    ch,BYTE PTR cs:[rip+0x20293031]        # 20293048 <_end+0x1fc92720>
  17:	34 2e                	xor    al,0x2e
  19:	39 2e                	cmp    DWORD PTR [rsi],ebp
  1b:	32 00                	xor    al,BYTE PTR [rax]
  1d:	47                   	rex.RXB
  1e:	43                   	rex.XB
  1f:	43 3a 20             	rex.XB cmp spl,BYTE PTR [r8]
  22:	28 44 65 62          	sub    BYTE PTR [rbp+riz*2+0x62],al
  26:	69 61 6e 20 34 2e 38 	imul   esp,DWORD PTR [rcx+0x6e],0x382e3420
  2d:	2e 34 2d             	cs xor al,0x2d
  30:	31 29                	xor    DWORD PTR [rcx],ebp
  32:	20 34 2e             	and    BYTE PTR [rsi+rbp*1],dh
  35:	38 2e                	cmp    BYTE PTR [rsi],ch
  37:	34 00                	xor    al,0x0
