/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_setters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:27:12 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/10 17:27:14 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	setenv_type(t_token *t)
{
	if (ftstrncmp("$?", t->str, 2))
		t->type = LSIG;
	else
		t->type = EV;
}

void	check_if_path(t_token *token)
{
	if (ftstrncmp("./", token->str, 2))
		token->type = REL_PATHF;
	if (ftstrncmp("/", token->str, 1))
		token->type = PATH;
}

void	set_type(t_token *token)
{
	if (ftstrcmp("echo", token->str))
		token->type = ECHO;
	if (ftstrcmp("pwd", token->str))
		token->type = PWD;
	if (ftstrcmp("exit", token->str))
		token->type = EXIT;
	if (ftstrcmp("|", token->str))
		token->type = PIPE;
	if (ftstrcmp("unset", token->str))
		token->type = UNSET;
	if (ftstrcmp("export", token->str))
		token->type = EXPORT;
	if (ftstrcmp("-n", token->str))
		token->type = N;
	if (token->str[0] == '$' && !token->sq)
		setenv_type(token);
	if (ftstrcmp(">", token->str))
		token->type = RD_O;
	if (ftstrcmp(">>", token->str))
		token->type = RD_O_APPEND;
	if (ftstrcmp("<", token->str))
		token->type = RD_I;
	if (ftstrcmp("<<", token->str))
		token->type = READ_I;
	check_if_path(token);
}

void	set_com_type(char *str, t_com *token)
{
	token->type = WORD;
	if (ftstrcmp("echo", str))
		token->type = ECHO;
	if (ftstrcmp("pwd", str))
		token->type = PWD;
	if (ftstrcmp("exit", str))
		token->type = EXIT;
	if (ftstrcmp("unset", str))
		token->type = UNSET;
	if (ftstrcmp("export", str))
		token->type = EXPORT;
	if (ftstrcmp("-n", str))
		token->type = N;
	if (ftstrcmp(">", str))
		token->type = RD_O;
	if (ftstrcmp(">>", str))
		token->type = RD_O_APPEND;
	if (ftstrcmp("<", str))
		token->type = RD_I;
	if (ftstrcmp("<<", str))
		token->type = READ_I;
	if (ftstrncmp("./", str, 2))
		token->type = REL_PATHF;
	if (ftstrncmp("/", str, 1))
		token->type = PATH;
}
