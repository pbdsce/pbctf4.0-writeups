# Challenge Name: Order in Chaos

**Category:** Reverse Engineering / Binary Analysis  

---

## Challenge Description
You’re given an executable named `chaos`. When run, it displays a **5×5 grid of numbers** that constantly change in a seemingly random fashion.

Your mission: **find the hidden flag**.

---

## Solution Walkthrough

### Step 1 — Initial Recon
Running the binary shows a rapidly refreshing grid of numbers. Most numbers appear to change each frame — but upon careful observation, some remain constant across refreshes.

These constant numbers are the clue.

---

### Step 2 — Capturing Output
Redirect the program’s output to a file to examine the static numbers without the animation:

```bash
./chaos > output.txt
```

By reviewing `output.txt`, it becomes easier to spot the non-random values that repeat in the same positions.

---

### Step 3 — Extracting the Data
Those static numbers correspond directly to **ASCII codes**.  
The extracted list of constants is:

```python
nums = [112, 98, 99, 116, 102, 123, 51, 120, 112, 51, 114, 55, 95, 100, 51, 55, 51, 99, 55, 49, 118, 51, 125]
print(''.join(chr(n) for n in nums))
```

---

### Step 4 — Decoding
Running the above script outputs:

```
pbctf{3xp3r7_d373c71v3}
```
