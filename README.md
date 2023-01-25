# Pipex
#### This project will let you discover in detail a UNIX mechanism that you already know by using it in your program.

*Version : 2*

---

### Mandatory part
##### Program name
* pipex
##### External functs. 
* open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
* ft_printf and any equivalent
YOU coded
##### Description
* This project is about handling pipes.

* Your program will be executed as follows:
	> ./pipex file1 cmd1 cmd2 file2

* It must behave exactly the same as the shell command below:
	> $> < file1 cmd1 | cmd2 > file2

* You have to handle errors thoroughly. In no way your program should quit unexpectedly (segmentation fault, bus error, double free, and so forth).

* Your program mustn’t have memory leaks.

* If you have any doubt, handle the errors like the shell command: < file1 cmd1 | cmd2 > file2
### Bonus part
##### Description
* Handle multiple pipes.
	>  $> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
	
	Should behave like
	> < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

* Support « and » when the first parameter is "here_doc".
	>  $> ./pipex here_doc LIMITER cmd cmd1 file
	
	Should behave like
	> cmd << LIMITER | cmd1 >> file

---

