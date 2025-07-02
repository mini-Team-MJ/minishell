/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:07:22 by mhurtamo          #+#    #+#             */
/*   Updated: 2025/06/28 17:07:26 by mhurtamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char    *get_sig_val(int lsig)
{
    int copy;
    char *ret;
    size_t  len;
    
    copy = lsig;
    len = 1;
    while (copy >= 10)
    {
        len++;
        copy /= 10;
    }
    ret = (char *)malloc((len + 1) * sizeof(char));
    if (!ret)
        return (NULL);
    ret[len] = '\0';
    len--;
    while(len > 0 && lsig >= 10)
    {
        ret[len] = (lsig % 10) + 48;
        lsig /= 10;
        len--;
    }
    ret[len] = lsig + 48;
    return (ret);
}


size_t	get_len(char *str)
{
	size_t	i;
	
	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char *custom_dup(char *line)
{
    size_t  i;
    char    *res;
    size_t	l;
    
    if(!line)
        return (0);
    l = custom_len(line);
    res = (char *)malloc((l + 1) * sizeof(char));
    if(!res)
    	return (NULL);
    i = 0;
    while (i <= l)
    {
        res[i] = line[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

size_t	custom_len(char *line)
{
	size_t	i;
	if(!line)
	    return (0);
	i = 0;
	while (line[i] && !is_whitespace(line[i]))
	{
    		if (line[i] == 39)
    			i += handle_sq(&line[i + 1]);
    		if (line[i] == 34)
    			i += handle_dq(&line[i + 1]);
    		i++;
	}
    return (i);
}

size_t  d_mover(char *line)
{
	size_t  res;
	char    c;

	res = 0;
	if (!line)
		return (res);
	c = line[res];
	while(line[res] == c)
		res++;
	res--;
	return(res);
}
