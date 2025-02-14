

## Summary
- The **kill** function sends a signal to a process.
- **SIGUSR1** and **SIGUSR2** are user-defined signals that can be used for any purpose in your application.
- In "server.c", **SIGUSR1** is used to represent a bit value of 1 when constructing a character from bits.



```c
// src: server.c
void	signal_parser(int signal, siginfo_t *info, void *context)
{
	static char	c = 0;      				  		   // Static variable to store the current character
	static int	bit = 0;  							   // Static variable to store the current bit position

	(void) context;        							   // Unused parameter
	c = (c << 1) | (signal == SIGUSR1);				   // Shift left and add the received bit
	bit++;                   						   // Increment bit position
	if (bit == 8)            						   // If 8 bits are received (one character)
	{
		if (c == 0 && g_str) 						   // If the character is null and g_str is not null
		{
			ft_printf("%s\n", g_str);  				   // Print the received string
			free(g_str);               				   // Free the allocated memory
			g_str = NULL;              				   // Reset g_str to NULL
		}
		else
		{
			g_str = ft_addchar(g_str, c);  			   // Add the character to g_str
			if (!g_str)                    			   // If memory allocation fails
				return ;                   			   // Return from the function
		}
		c = 0;                						   // Reset the character
		bit = 0;                					   // Reset the bit position
	}
	**kill**(info->si_pid, SIGUSR1);   				   // Send acknowledgment signal to the client
}
```
---

# **kill** Function

The **kill** function is used to send a signal to a process or a group of processes. The syntax for the **kill** function is:
```c
	int kill(pid_t pid, int sig);
```


- **pid**: The process ID of the target process. If pid is greater than 0, the signal is sent to the process with the ID pid. If pid is 0, the signal is sent to all processes in the same process group as the sender.
- **sig**: The signal to be sent. This can be any valid signal number.


In "server.c", the **kill** function is used to send the SIGUSR1 signal to the client process:
```c
	kill(info->si_pid, SIGUSR1);
```
Reminder :: info is a siginfo_t
to see the hole data struct of siginfo_t check : https://www.mkssoftware.com/docs/man5/siginfo_t.5.asp

Here, **info->si_pid** is the process ID of the client process that sent the signal to the server. The server sends back the **SIGUSR1** signal to acknowledge the receipt of the signal.


---

# **SIGUSR1** and **SIGUSR2**

- **SIGUSR1**: A user-defined signal that can be used for custom purposes in your program. It is typically used to notify a process of a specific event.

- **SIGUSR2**: Another user-defined signal similar to SIGUSR1, but it can be used for a different custom purpose. It allows you to have two distinct custom signals in your program.

**SIGUSR1** and **SIGUSR2** are user-defined signals in Unix-like operating systems. They are intended for application-specific purposes. These signals do not have predefined meanings, so you can use them for any purpose in your application.

- **SIGUSR1**: Signal number 10 (on most systems). It is used In "server.c" to represent a bit value of 1.
- **SIGUSR2**: Signal number 12 (on most systems). It is not used in your provided code, but it can be used similarly to **SIGUSR1** for other purposes.
In "server.c", the **SIGUSR1** signal is used to indicate a bit value of 1 when constructing a character from bits:
```
c = (c << 1) | (signal == SIGUSR1);
```
This line shifts the current character c to the left by one bit and adds the received bit (1 if the signal is **SIGUSR1**, 0 otherwise).

---
## Line treating bits, with examples to understand how it works :
```c
 c = (c << 1) | (signal == SIGUSR1);
```


### Explanation
1. Shift Left **(c << 1)**: This operation shifts the bits of c one position to the left. This makes room for the new bit that will be added.

2. Bitwise OR (|): This operation adds the new bit to the least significant position of c.
3. Comparison (signal == SIGUSR1): This comparison checks if the received signal is SIGUSR1. If it is, the result is 1; otherwise, it is 0.
Example
Let's go through an example step by step:

1. Initial State:

- Assume c is initially 00000000 (in binary).
- Assume bit is initially 0.

2. First Signal (SIGUSR1):
- signal == SIGUSR1 evaluates to 1.
- c << 1 shifts c left: 00000000 becomes 00000000.
- c = (c << 1) | 1 results in 00000001.
- bit is incremented to 1.

3. Second Signal (SIGUSR2):
- signal == SIGUSR1 evaluates to 0.
- c << 1 shifts c left: 00000001 becomes 00000010.
- c = (c << 1) | 0 results in 00000010.
- bit is incremented to 2.

4. Third Signal (SIGUSR1):
- **signal == SIGUSR1** evaluates to 1.
- **c << 1** shifts c left: 00000010 becomes 00000100.
- **c = (c << 1) | 1** results in 00000101.
- **bit** is incremented to 3.

5. Fourth Signal (SIGUSR2):
- **signal == SIGUSR1** evaluates to 0.
- **c << 1** shifts c left: 00000101 becomes 00001010.
- **c = (c << 1) | 0** results in 00001010.
- **bit** is incremented to 4.

### Summary
Each time a signal is received, the current value of c is shifted left by one bit, and the new bit (determined by whether the signal is SIGUSR1 or SIGUSR2) is added to the least significant bit of c. This process continues until 8 bits have been received, forming a complete character.