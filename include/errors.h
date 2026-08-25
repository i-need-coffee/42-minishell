/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:02:54 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 17:02:55 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_SYNTAX_PIPE "minishell: syntax error near unexpected token `|'"
# define ERR_REDIR "minishell: syntax error near unexpected token `newline'"
# define ERR_REDIR_OUT "minishell: syntax error near unexpected token `>'"
# define ERR_REDIR_IN "minishell: syntax error near unexpected token `<'"
# define ERR_APPEND "minishell: syntax error near unexpected token `>>'"
# define ERR_HEREDOC "minishell: syntax error near unexpected token `<<'"
# define ERR_SIG "minishell: sigaction failed"
# define ERR_ALLOC "minishell: cannot allocate memory"
# define ERR_QUOTES "minishell: incorrect syntax: unclosed quotes"
# define ERR_PIPE "minishell: pipe"
# define ERR_FORK "minishell: fork"
# define ERR_DUP2 "minishell: dup2"
# define ERR_DUP "minishell: dup"
# define ERR_WAITPID "minishell: waitpid"
# define ERR_WRITE "minishell: write"
# define ERR_RESTORE_FDS "minishell: impossible to restore STDIN and STDOUT"
# define ERR_PWD "minishell: pwd"
# define ERR_ECHO "minishell: echo"
# define ERR_CD "minishell: cd"
# define ERR_CD_ARGS_NUM "minishell: cd: too many arguments"
# define ERR_CD_NO_HOME "minishell: cd: HOME not set"
# define ERR_ENV_ARGS_NUM "minishell: env: too many arguments"
# define ERR_ALLOC_EXPORT "minishell: export: cannot allocate memory"
# define ERR_EXIT "minishell: exit"
# define ERR_EXIT_NUM "numeric argument required"
# define ERR_EXIT_ARGS_NUM "minishell: exit: too many arguments"
# define ERR_CMD_NOT_FOUND "command not found"
# define ERR_IS_A_DIR "is a directory"

#endif