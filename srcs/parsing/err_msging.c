/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msging.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:40:12 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/07/17 17:40:15 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_error(char *msg)
{
	size_t	i;

	if (!msg)
		return ;
	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

char	*join_strings(char *s1, char *s2)
{
	char	*joined;
	size_t	len;
	size_t	i;
	
	len = get_len(s1) + get_len(s2);
	joined = (char *)malloc((len + 1) * sizeof(char));
	if (!full_msg)
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[len])
	{
		joined[i] = s2[len];
		len++;
	}
	return (joined);
}

void	err_msg(char *s1, char *s2)
{
	char	*full_msg;

	len = get_len(s1) + get_len(s2);
	if (!full_msg)
		return ;
	full_msg = join_strings(s1, s2);
	if (!full_msg)
		return ;
}

