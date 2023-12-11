# C - SIMPLE SHELL.
--- 

![Shell Image](https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.jpeg)


### Description.

*  The shell is a simple implementation of a UNIX command line interpreter  has similar functionality to sh and works by reading a command from the user and executing it by calling the appropriate system function.

----
# HOW IT WORKS.
---

## COMPILATION

* To compile the shell,navigate to repository and use the following command:

	`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh. `
---

## USAGE

 * Shell can be run in interactive and non-interactive mode
   By executing the program without any arguments:

#### INTERACTIVE MODE 
   `$ ./hsh`
   `($) /bin/ls`
   `hsh main.c shell.c`
   `($)`
   `($) exit`
   `$`

####NON-INTEREACTIVE MODE

   `$ echo "/bin/ls" | ./hsh`
   `hsh main.c shell.c test_ls_2`
   `$`
   `$ cat test_ls_2`
   `/bin/ls`
   `/bin/ls`
   `$`
   `$ cat test_ls_2 | ./hsh`
   `hsh main.c shell.c test_ls_2`
   `hsh main.c shell.c test_ls_2`
   `$`

---

* **BenieShann** [Shann](https://github.com/BenieShann)

-----------
