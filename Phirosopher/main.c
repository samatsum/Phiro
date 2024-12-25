/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:13:00 by samatsum          #+#    #+#             */
/*   Updated: 2024/12/25 15:18:41 by samatsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av);

/* ************************************************************************** */
/*
1->argument vector"(引数の配列)の処理。
2->構造体tableを初期化(forkを所有する哲学者を小さいID側に設定)
*/
int	main(int ac, char **av)
{
	t_table	tab;
	t_philo	*philos;
	int		i;

	if (parse_args(ac, av, &tab) != 0)
		return (printf("Argument Error\n"), 1);
	if (init_table(&tab) != 0)
		return (printf("Init Error\n"), 1);
	philos = malloc(sizeof(t_philo) * tab.philo_count);
	if (!philos)
		return (printf("Malloc Error\n"), 1);
	i = -1;
	while (++i < tab.philo_count)
	{
		philos[i].id = i;
		philos[i].meal_count = 0;
		philos[i].last_meal = tab.start_time;
		philos[i].table = &tab;
		pthread_create(&tab.threads[i], NULL, philo_life, &philos[i]);
	}
	i = -1;
	while (++i < tab.philo_count)
		pthread_join(tab.threads[i], NULL);
	free(philos);
	free(tab.forks);
	free(tab.threads);
	return (0);
}
