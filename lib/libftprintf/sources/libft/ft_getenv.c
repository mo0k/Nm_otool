/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:12:17 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/09 11:12:52 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <libft.h>

char 	*ft_getenv(const char *name)
{
	int count;

	count = 0;
	if (!name)
		return (0);
	while (environ && environ[count])
	{
		char *sep;

		if (!(sep = ft_strchr(environ[count], '=')))
			return (0);
		else
			*sep = 0;
		if (!ft_strcmp(name, environ[count]))
		{
			*sep = '=';
			return (sep + 1);
		}
		*sep = '=';
		++count;
	}
	return (0);
}
