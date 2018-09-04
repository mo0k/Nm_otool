/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:31:07 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 23:03:29 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_opts.h>

int				*get_mask()
{
	static int	bit_mask[32] = 
	{
		0x00000001, 0x00000002, 0x00000004, 0x00000008,
		0x00000010, 0x00000020, 0x00000040, 0x00000080,
		0x00000100, 0x00000200, 0x00000400, 0x00000800,
		0x00001000, 0x00002000, 0x00004000, 0x00008000,
		0x00010000, 0x00020000, 0x00040000, 0x00080000,
		0x00100000, 0x00200000, 0x00400000, 0x00800000,
		0x01000000, 0x02000000, 0x04000000, 0x08000000,
		0x10000000, 0x20000000, 0x40000000, 0x80000000
	};
	return (bit_mask);
}

static int 		check(int nb_arg, char **args, uint32_t *index, uint32_t *opts)
{
	if (nb_arg < 1)
		return (NO_ARGS);
	if (!args || !*args)
		return (ARGS_NULL);
	if (!index)
		return (NO_INDEX);
	if (!opts)
		return (NO_VAR_OPTION);
	return(SUCCESS);
}

int				get_opts(int nb_arg, char **args, uint32_t *index, uint32_t *opts)
{
	int 		i;
	int 		j;
	char 		*ptr;
	int			error;

	if ((error = check(nb_arg, args, index, opts)))
		return (error);
	i = -1;
	while (args[++i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j])
		{
			if ((ptr = strchr(OPTIONS, args[i][j])) != NULL)
				SET_BIT(*opts, ptr - OPTIONS);
			else
				return (BAD_OPTION);
		}
		//++i;
	}
	*index = i + 1;
	P_DEBUG_VARGS("opt:0x%02x\t%d\t%d\n", *opts, *opts, i);
	return (SUCCESS);
}

int				print_error(int error)
{
	char 		message[44];
	static char	strerror[6][32] = 
	{
		"success",
		"no arguments",
		"args argument missing or null",
		"index argument missing or null",
		"opts argument missing or null",
		"option not valid"
	};
	
	memmove(message, "Error opts: ", 12);
	memmove(message + 12, strerror[error], 32);
	return (printf("%s\n", message));
}
