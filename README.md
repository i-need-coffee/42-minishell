_This project has been created as part of the 42 curriculum by jturrel, sjolliet._

# Minishell - 42 Common Core

## Description

Minishell is the first group project from 42's common core.

In this project, we need to reproduce some of the behavior of shell, with the following guidelines:

- Display a prompt when waiting for a new command.
- Have a working **history**.
- Search and launch the right executable (based on the `PATH` variable or using a
relative or an absolute path).
- Use at most **one global variable** to indicate a received signal.
- Not interpret unclosed quotes or special characters which are not required by the
subject such as `\` (backslash) or `;` (semicolon).
- Handle `'` (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
- Handle `"` (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for `$` (dollar sign).
- Implement the following redirections:
  - `<` should redirect input.
  - `>` should redirect output.
  - `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
  - `>>` should redirect output in append mode.
- Implement pipes (`|` character).
- Handle environment variables (`$` followed by a sequence of characters) which should expand to their values.
- Handle `$?` which should expand to the **exit status** of the most recently executed foreground pipeline.
- Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.
- In interactive mode:
  - `ctrl-C` displays a new prompt on a new line.
  - `ctrl-D` exits the shell.
  - `ctrl-\` does nothing.
- Your shell must implement the following **built-in** commands:
  - `echo` with option `-n`
  - `cd` with only a relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options
- The `readline()` function may cause memory leaks, but you are not required to fix them.

## Instructions

### Compilation

Clone the repository and compile the project using `make`:
```bash
git clone <repository_url>
cd <project_name>
make
```

### Usage

Launch minishell:
```bash
./minishell
```

Type commands, redirections and pipes like in bash:
```bash
minishell> cat << EOF
> Hello, World!
> EOF
Hello, World!
minishell> ls | grep supp > outfile
minishell> cat outfile
readline.supp
minishell> cat < infile | grep x | wc -l
2
```

You can also use built-ins:
```bash
minishell> echo a | echo b
b
minishell> echo 'hello'
hello
minishell> pwd
/home/sjolliet/projects/minishell
minishell> cd ..
minishell> pwd
/home/sjolliet/projects
minishell> exit
exit
```

### Environment

The environment is taken directly from bash when launching minishell.
However, if you launch minishell with the following command :
```bash
env -i ./minishell
```

You will get an empty environment with the following variables:
```bash
minishell> env
PWD=/home/sjolliet/projects/minishell
SHLVL=1
```
Just like in bash, the **shell level ($SHLVL)** is incremented every time the program is launched.

You can export, unset and print env variables as well:
```bash
minishell> export NEWKEY=NEWVALUE
minishell> echo $NEWKEY
NEWVALUE
minishell> unset NEWKEY
minishell> echo $NEWKEY

minishell>
```

### Errors and exit status

The errors and exit status are the same as in bash.

For instance, if you type a command that does not exist, you can also print the exit status with the env variable `$?`:
```bash
minishell> catt <infile
minishell: catt: command not found
minishell> echo $?
127
```

Since unclosed quotes do not need to be interpreted, we consider them as a syntax error:
```bash
minishell> echo ''hello'
minishell: incorrect syntax: unclosed quotes
minishell> echo $?
2
```

## Resources

AI tools were used as learning and productivity aids for :

- Understanding how signals work, especially when it comes to exit status
- Creating the readline.supp file to suppress leaks from the readline function
- Understanding what tokens are and how they are used in bash
- Getting help to create the Makefile
