/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:09:44 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/12 16:48:35 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_data	*data;

	if (check_input(ac, av))
		return (EXIT_FAILURE);
	data = read_file(av[1]);
	if (!data)
		return(EXIT_FAILURE);
	if (check_data(data))
		return (free_data(data),EXIT_FAILURE);
	free_data(data);
	printf("OK\n");
}
