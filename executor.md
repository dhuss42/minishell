# Executor
```c
function executor(t_data* data) {
  if (data->number_of_pipes == 0) {
    // if there is no pipe, there is only one command
    execute_single_command(data);       // ex. ls -la

    // the parent HAS to wait the eventual forked children AND collect the exit_code of the last command executed (in this case the only one)
    parent_role(data);
    return ;
  }
  else {
    // in case of pipes, multiple processes have to be forked - ex. ls | wc | cat ===> 2 pipes, 3 commands, therefore 3 forks.
    execute_pipechain(data);            // ex. ls -la | wc -l | cat -en
    // same as above about the parent; every child has to be waited AND the exit_code collected (only the last one will be stored in data)
    parent_role(data);
    return ;
  }
}
```
```c
function execute_single_command(t_data* data) {
  // if the command is one of the builtin listed in the subject, you don't need to fork, and you need to run the particular function. Also, "cd" would not work properly, in case of forking (I'll explain better) - this part can be done later, just have in mind
  if (is_a_builtin(data->command[0]))
    execute_builtin_same_ps(data);  // no fork
  else {
    // if not a builtin, just fork a process to execute the command
    handle_single_child(data);
  }
}
```
```c
function execute_pipechain(t_data* data) {
  // this part is the core of piping: need to read something and think about it.
  // After some code you'll reach this point:
  handle_pipe_child(data);
}
```
```c
// command_index == means, something that indentifies which command are you handling;
// Example: <input ls -la | wc -l | cat -en >output
// handle_pipe_child(data, 0) ----> will handle <input ls -la
// handle_pipe_child(data, 1) ----> will handle wc -l
// handle_pipe_child(data, 2) ----> will handle cat -en >output
function handle_pipe_child(t_data* data, command_index) {

  // every redirection has to be performed; they can be multiple like: <in1 <in2 <in3 (in this case the input is taken by in3, but you have still to try to open() the other, because if the cannot be oopen for some reason, you'll have to catch the error and block the execution)
  if (handle_redirections(data) == ERROR)
    return (free_process_exit(data));
  if (is_builtin(data, command_index))
    run_builtin_function(data)
  else {
    if (execve(/* (...) */) == -1) {
      // command not found
    }
  }
  return (0);
}
```
