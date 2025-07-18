/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_direction_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:38:13 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:38:17 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	setup_directors(t_com *new, t_token **tokens)
{
	t_token	*last_in_dir;
	t_token	*last_o_dir;
	t_token	*current;

	current = *tokens;
	last_in_dir = NULL;
	last_o_dir = NULL;
	while (current)
	{
		if (current->type == RD_I || current->type == READ_I)
			last_in_dir = current;
		if (current->type == RD_O || current->type == RD_O_APPEND)
			last_o_dir = current;
		current = current->next;
	}
	if (last_in_dir)
	{
		new->infile = last_in_dir->next->str;
		new->redir_type_in = true;
	}
	if (last_o_dir)
	{
		new->outfile = last_o_dir->prev->str;
		new->redir_type_out = true;
	}
}

bool	handle_i(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			print_error("minishell: unexpected error near 'newline'");
			return (false);
		}
		if (str[i] != '<')
			break ;
		i++;
	}
	if (!str[i])
	{
		print_error("minishell: unexpected error near 'newline'");
		return (false);
	}
	if (i > 2)
	{
		print_error("minishell: syntax error near unexpected token `<'");
		return (false);
	}
	return (check_next(&str[i]));
}

bool	handle_o(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			print_error("minishell: unexpected error near 'newline'");
			return (false);
		}
		if (str[i] != '>')
			break ;
		i++;
	}
	if (!str[i])
	{
		print_error("minishell: unexpected error near 'newline'");
		return (false);
	}
	if (i > 2)
	{
		print_error("minishell: syntax error near unexpected token `>'");
		return (false);
	}
	return (check_next(&str[i]));
}

bool	validate_directors(char *str)
{
	size_t	i;

	if (*str == '<')
		return (handle_i(str));
	else
		return (handle_o(str));
}

size_t	d_mover(char *line)
{
	size_t	res;
	char	c;

	res = 0;
	if (!line)
		return (res);
	c = line[res];
	while (line[res] == c)
		res++;
	res--;
	return (res);
}
