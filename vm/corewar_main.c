/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msymkany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 17:52:03 by msymkany          #+#    #+#             */
/*   Updated: 2017/08/03 18:01:51 by msymkany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	read_args(int ar, char **av, t_general *gen)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (++i < ar)
	{
		if (is_flag(av, &i, gen)) // checks if arg is a flag and adds to struct
			;
		else if (is_champ(av[i]))
		{
			if (gen->champ_num == MAX_PLAYERS)
				ft_error("To many champions");
			gen->no_flag[j++] = i;
			gen->champ_num++;
		}
	}
//	is_valid_champ(av[i], gen->champs, j);
}

int		main(int ar, char **av)
{
    t_general   *gen;
	size_t 		j; //test

	j = 1; // test
    if (ar == 1)
        ft_usage();
    gen = gen_init();
	read_args(ar, av, gen);
//	while (j <= 3) // test
//	{
//		is_valid_champ(av[j], gen, 0);
//		j++;
//	}
//	gen->champ_num = 3; // test
//	write_to_map(gen);

//	while(1)
//		;
	return (0);
}
