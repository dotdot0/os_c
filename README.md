# A small OS in c

- Build: 

Install NASM
- For Debian Based:
`apt install nasm`
- For Fedora:
`dnf install nasm`

Now run:
```
cd boot
nasm -f bin boot.asm -o boot.bin
```

- Running

Install QEMU
- For Debian Based:
```
apt install qemu-system
```
- For Fedora:
```
dnf install qemu
```

Now run:
```
qemu-system-x86_64 boot.bin
```