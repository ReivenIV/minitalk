# Client.c

## **Summary of How It Works**
1. The client reads the PID and message from command-line arguments.
2. It validates the PID.
3. It sets up a signal handler (`ack_handler`) to receive acknowledgments.
4. It converts each character into **8 bits** and sends them using `SIGUSR1` (for `1`) and `SIGUSR2` (for `0`).
5. After each bit, it **waits for acknowledgment** from the server.
6. After sending the whole message, it sends **8 `SIGUSR2` signals** to indicate the end.


## **Understanding `client.c` in Minitalk**

The client program is responsible for sending a message to a server process using UNIX signals (`SIGUSR1` and `SIGUSR2`). Each character is sent as a sequence of 8 bits (1 byte), and the server acknowledges each bit received.

---

## **1. Global Variable**
```c
volatile sig_atomic_t g_received_ack;
```
- `g_received_ack` is a global variable that the signal handler will modify.
- `volatile` ensures the compiler does not optimize away reads/writes since signals can change it asynchronously.
- `sig_atomic_t` is a type that guarantees atomic access (safe from interruptions by signals).

---

## **2. Acknowledgment Handler (`ack_handler`)**

#### Sumary :
- This function is executed when the client receives `SIGUSR1` from the server.
- It updates `g_received_ack` to 1, indicating the server received a bit.
```c
void ack_handler(int signum, siginfo_t *info, void *context) // listen_server
{
    (void) context; // Unused parameter
    (void) info; // Unused parameter
    if (signum == SIGUSR1 || signum == SIGUSR2) // Check if we have an income signal type SIGUSR1 or SIGUSR2
        g_acknowledgment_status = 1; // Set acknowledgment status to 1
    else // If the signal is not SIGUSR1 or SIGUSR2 (that means we didn't had any feedback from the server) could mean the pid is wrong or that the server is off for ex. 
    {
        write(2, "problem with the server\n", 20); 
        exit(EXIT_FAILURE); // Exit the program with failure status
    }
}
```

This function is used to handle the acknowledgment signals from the server. When the client sends a signal to the server, it waits for an acknowledgment signal (either SIGUSR1 or SIGUSR2) from the server. The ack_handler function sets the acknowledgment status when such a signal is received, allowing the client to proceed with its operations. You can see it as a first check and the server answers back with an OK. After we know that the comunication is stablish, we set **g_acknowledgment_status = 1;** to proced sending data.

---

## **3. Waiting for Acknowledgment (`wait_sig`)**
This function waits for a response (acknowledgment) from the server after the client sends a signal. If no acknowledgment is received within the specified time, it reports an error and terminates the program.

```c
void wait_sig(void)
{
    int retries = 10000; // Max retries (~1 second total with 100us sleep)
    
    while (!g_acknowledgment_status && retries > 0) // Loop until acknowledgment is received or retries run out
    {
        usleep(100); // Sleep for 100 microseconds
        retries--; // Decrement retries
    }
    
    if (retries == 0) // If retries run out
    {
        write(2, "\e[31mError: No acknowledgment received\n\e[0m", 40); // Print error message to stderr
        exit(EXIT_FAILURE); // Exit the program with failure status
    }

    g_acknowledgment_status = 0; // Reset acknowledgment status
}
```

### **Explanation**
- We set a retry limit (`retries = 10000`), allowing a total wait time of approximately 1 second (`10000 * 100µs = 1s`).
- Inside the loop:
  - If no acknowledgment is received, we sleep for `100` microseconds (`usleep(100);`).
  - We decrement `retries` to prevent an infinite loop.
- If `retries` reaches `0`, we print an error message and exit the program.

### usleep & retries usage is better: 
✅ **Prevents infinite loops** if the server is unresponsive.  
✅ **Reduces CPU usage** by allowing other processes to run while waiting.  

---

## **4. Sending a Message (`send_sig`)**
```c
void send_sig(int pid, char *str)
{
	int	bit;
	int	i;

	while (*str)
	{
		i = 7;
		while (i >= 0)
		{
			bit = (*str >> i) & 1;
			if (bit == 1)
				kill(pid, SIGUSR1);
			if (bit == 0)
				kill(pid, SIGUSR2);
			i--;
			wait_sig();
		}
		str++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		wait_sig();
		i++;
	}
}
```
- The function takes:
  - `pid`: Process ID of the server.
  - `str`: The message to send.
- It loops through each character in the message.
- Each character is broken down into 8 bits.
- It sends `SIGUSR1` for `1` bits and `SIGUSR2` for `0` bits.
- After sending each bit, it calls `wait_sig()` to ensure the server received it before sending the next one.
- At the end of the message, it sends **8 `SIGUSR2` signals** to mark the end.



### Sending Characters:
```c

while (*str)
{
    i = 7;
    while (i >= 0)
    {
        bit = (*str >> i) & 1;
        if (bit == 1)
            kill(pid, SIGUSR1);
        if (bit == 0)
            kill(pid, SIGUSR2);
        i--;
        wait_sig();
    }
    str++;
}
```
- The outer **while** loop iterates over each character in the string **str**.
- The inner **while** loop iterates over each bit of the current character, starting from the most significant bit (7) to the least significant bit (0).
- **bit = (*str >> i) & 1**; extracts the i-th bit of the current character.
- Depending on the value of the bit, it sends either **SIGUSR1** (for bit 1) or **SIGUSR2** (for bit 0) to the server process identified by **pid**.
- After sending each bit, it calls **wait_sig()** to wait for an acknowledgment from the server.

### Sending End-of-Message Signal:

```c
i = 0;
while (i < 8)
{
    kill(pid, SIGUSR2);
    wait_sig();
    i++;
}
```

- After all characters in the string have been sent, the function sends 8 **SIGUSR2** signals.
- This is used to indicate the end of the message. The server can recognize this sequence of 8 **SIGUSR2** signals as a special marker that signifies the end of the transmission.
- Each **SIGUSR2** signal is followed by a call to **wait_sig()** to wait for an acknowledgment from the server.

#### **Example of Bit Sending**
For the character `'A'` (`ASCII 65`):

1. Each bit is sent one by one, with a pause after each bit to wait for acknowledgment.

```
'A' -> 01000001

- `0` → Send `SIGUSR2`
- `1` → Send `SIGUSR1`
- `0` → Send `SIGUSR2`
- `0` → Send `SIGUSR2`
- `0` → Send `SIGUSR2`
- `0` → Send `SIGUSR2`
- `0` → Send `SIGUSR2`
- `1` → Send `SIGUSR1`
``` 

2. After sending 'A', it will send 8 SIGUSR2 signals to indicate the end of the message.
- Send `SIGUSR2` x 8


---

## **5. Main Function**
```c
int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		write(2, "\e[31mError, format : ./client <PID> \"msg\"\n\e[0m", 46);
		return (0);
	}
	pid = ft_atoi(av[1]);
	if (kill(pid, 0) == -1)
	{
		write(2, "\e[31mError, wrong PID\n\e[0m", 26);
		return(0);
	}
	if (!*av[2])
		exit(EXIT_SUCCESS);
	set_sigaction(ack_handler, 3);
	send_sig(pid, av[2]);
	return(0);
}
```
#### **Explanation**
1. **Argument Checking**  
2. **Convert PID from String to Integer with atoi**
3. **Check if PID Exists**
   ```c
   if (kill(pid, 0) == -1)
   ```
   - `kill(pid, 0)` does **not** send a signal but checks if the process exists.
   - If the PID is invalid, an error is printed.
4. **Check if Message is Empty**
   ```c
   if (!*av[2])
   		exit(EXIT_SUCCESS);
   ```
   - If the message is empty, exit immediately.
5. **Set Signal Handler**
   ```c
   set_sigaction(ack_handler, 3);
   ```
6. **Send the Message**
   ```c
   send_sig(pid, av[2]);
   ```
---



---
