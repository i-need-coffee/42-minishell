#include "minishell.h"

static int	get_substr_len(char *input);
static int	isseparator(int c);

/*
**	Extracts the next word from the input and adds it as a TOKEN_WORD.
**	Advances the index by the length of the extracted word.
*/
void	add_word_token(t_mini **mini, int *i)
{
	int		len;
	char	*substr;

	len = get_substr_len((*mini)->input + *i);
	substr = ft_substr((*mini)->input, *i, len);
	if (!substr)
		print_error_and_exit(*mini, ERR_ALLOC, EXIT_FAILURE);
	if (!add_token(&(*mini)->tokens, TOKEN_WORD, substr))
	{
		free(substr);
		cleanup_exit(*mini, EXIT_FAILURE);
	}
	free(substr);
	(*i) += len;
}

/*
**	Returns the length of the next word, stopping at unquoted spaces
**	or operator characters.
*/
static int	get_substr_len(char *input)
{
	int	len;
	int	in_s_quotes;
	int	in_d_quotes;

	len = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while (input[len])
	{
		if (input[len] == '\'' && !in_d_quotes)
			in_s_quotes = !in_s_quotes;
		if (input[len] == '"' && !in_s_quotes)
			in_d_quotes = !in_d_quotes;
		if (!in_s_quotes && !in_d_quotes && isseparator(input[len]))
			break ;
		len++;
	}
	return (len);
}

/*
**	Returns 1 if c is an operator character (|, <, >).
*/
static int	isseparator(int c)
{
	return (c == '|' || c == '<' || c == '>');
}
