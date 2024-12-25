
#include "philo.h"

int	parse_args(int ac, char **av, t_table *table);
int	init_tablele(t_table *table);

/* ************************************************************************** */
/* 1. 引数パース関数 */
int	parse_args(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo nb_philo t_die t_eat t_sleep [must_eat]\n");
		return (1);
	}
	table->philo_count = atoi(av[1]);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->must_eat_count = (ac == 6) ? atoi(av[5]) : -1;
	if (table->philo_count <= 0 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/* 2. テーブル初期化関数(フォーク所有者を小さいID側に設定) */
int	init_tablele(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_fork) * table->philo_count);
	table->threads = malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->forks || !table->threads)
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_init(&(table->forks[i].mutex), NULL);
		/* i番目のフォークは「i」と「(i+1)%count」のうち小さいIDが所有 */
		if (i < (i + 1) % table->philo_count)
			table->forks[i].owner_id = i;
		else
			table->forks[i].owner_id = (i + 1) % table->philo_count;
		i++;
	}
	table->start_time = now_ms();
	return (0);
}