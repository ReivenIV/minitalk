explanation done with gpt my dear: 

```c
void set_signal_action(void(*handler)(int, siginfo_t*, void*), int sigusr)
{
    struct	sigaction	sig; // Declare a sigaction structure

    sig.sa_sigaction = handler; // Set the handler function for the signal
    sigemptyset(&sig.sa_mask); // Initialize the signal mask to empty
    sig.sa_flags = SA_SIGINFO | SA_RESTART; // Set flags to get detailed signal info and restart interrupted system calls

    if (sigusr == 1)
        sigaction(SIGUSR1, &sig, NULL); // Set the action for SIGUSR1
    else if (sigusr == 2)
        sigaction(SIGUSR2, &sig, NULL); // Set the action for SIGUSR2
    else
    {
        sigaction(SIGUSR1, &sig, NULL); // Set the action for SIGUSR1
        sigaction(SIGUSR2, &sig, NULL); // Set the action for SIGUSR2
    }
}

```

| Step | Action | Explanation |
|------|--------|------------|
| 1️⃣ | Create `sigaction` struct | Stores signal handling info |
| 2️⃣ | Set `sig.sa_sigaction = handler;` | Assigns the function to handle the signal |
| 3️⃣ | Use `sigemptyset(&sig.sa_mask);` | Makes sure no signals are blocked |
| 4️⃣ | Set flags (`SA_SIGINFO | SA_RESTART`) | Gives extra info and prevents system calls from failing |
| 5️⃣ | Use `sigaction(SIGUSR1, &sig, NULL);` | Registers the signal handler |


Here's a step-by-step explanation of your `set_signal_action` function in **simple words**, using **examples** to make it easier to understand.

---

## Understanding `set_signal_action`
This function **sets up how the program will react** when it receives **SIGUSR1** or **SIGUSR2** signals.

### 1️⃣ Function Prototype
```c
void set_signal_action(void(*handler)(int, siginfo_t*, void*), int sigusr)
```
- `handler`: A function that will be called when the signal arrives.
- `sigusr`: A number to choose **which signal** to configure:
  - `1` → Configure `SIGUSR1`
  - `2` → Configure `SIGUSR2`
  - `Other value` → Configure **both** signals.

---

### 2️⃣ Creating a `sigaction` structure
```c
struct sigaction sig;
```
This structure **stores information** about how the program should react when receiving a signal.

---

### 3️⃣ Assigning the signal handler
```c
sig.sa_sigaction = handler;
```
- This **links** the signal to a function (`handler`) that will run when the signal arrives.

Example:
```c
void my_handler(int signal, siginfo_t *info, void *context)
{
    write(1, "Signal received!\n", 17);
}
```
If we pass `my_handler` to `set_signal_action()`, every time the signal arrives, `"Signal received!"` will be printed.

---

### 4️⃣ Clearing the signal mask
```c
sigemptyset(&sig.sa_mask);
```
This **ensures no signals are blocked** while handling another one.

Example:
- If **SIGUSR1** arrives while handling **SIGUSR2**, we **allow** it to be processed.

---

### 5️⃣ Setting flags
```c
sig.sa_flags = SA_SIGINFO | SA_RESTART;
```
- `SA_SIGINFO`: Provides **extra information** about the signal (like who sent it).
- `SA_RESTART`: If a signal interrupts a system call (like `read()`), it **restarts** the call instead of failing.

Example:
- Imagine your program is **waiting for user input** (`scanf()`), and a signal interrupts it.
- Without `SA_RESTART`, `scanf()` **would stop** with an error.
- With `SA_RESTART`, `scanf()` **continues** as if nothing happened.

---

### 6️⃣ Configuring signals
```c
if (sigusr == 1)
    sigaction(SIGUSR1, &sig, NULL);
else if (sigusr == 2)
    sigaction(SIGUSR2, &sig, NULL);
else
{
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);
}
```
- If `sigusr == 1`, only **SIGUSR1** is configured.
- If `sigusr == 2`, only **SIGUSR2** is configured.
- If another value is passed, **both** signals are configured.


## What does "configured" mean?
When you call `sigaction(SIGUSR1, &sig, NULL);`, it **tells the operating system**:

> "Hey, whenever SIGUSR1 arrives, run the function I provided (`handler`)."

So, **"configured" means setting up the signal handler** for the given signal.

### 🔹 Example Breakdown
#### Case: `set_signal_action(handler, 1);`
```c
sigaction(SIGUSR1, &sig, NULL);
```
- This means: **Only SIGUSR1 will trigger the `handler` function**.
- If **SIGUSR2 arrives**, the program **won’t react** because it wasn’t configured.

#### Case: `set_signal_action(handler, 2);`
```c
sigaction(SIGUSR2, &sig, NULL);
```
- Now, **only SIGUSR2** is handled.

#### Case: `set_signal_action(handler, 3);`
```c
sigaction(SIGUSR1, &sig, NULL);
sigaction(SIGUSR2, &sig, NULL);
```
- **Both** SIGUSR1 and SIGUSR2 are handled.

---

## Example Usage
### Code:
```c
int main()
{
    set_signal_action(&my_handler, 3);
    
    while (1)
        pause(); // Wait for signals
    
    return 0;
}
```
### What Happens?
1. The program **registers** `my_handler` for `SIGUSR1` and `SIGUSR2`.
2. It **waits** (does nothing) until a signal arrives.
3. When you send a signal (`kill -SIGUSR1 <PID>`), it prints **"Signal received!"**.

---


