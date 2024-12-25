
#include "philo.h"

void	*philo_life(void *arg);
void	release_fork(t_philo *p, int fork_id, int new_owner);
void	request_fork(t_philo *p, int fork_id);

/* ************************************************************************** */
/* 3. フォークを要求する関数(Chandy/Misra: 所有者にリクエスト→空けば譲渡) */
void	request_fork(t_philo *p, int fork_id)
{
	t_table *t = p->table;
	while (1)
	{
		pthread_mutex_lock(&t->forks[fork_id].mutex);
		if (t->forks[fork_id].owner_id == p->id)
		{
			pthread_mutex_unlock(&t->forks[fork_id].mutex);
			break ;
		}
		else
		{
			/* 所有者が自分でないならロックを解除し小休止後リトライ */
			pthread_mutex_unlock(&t->forks[fork_id].mutex);
			usleep(1000);
		}
	}
}

/* ************************************************************************** */
/* 4. フォーク解放+所有権譲渡(食べ終わったらお隣さんに渡してもよい) */
void	release_fork(t_philo *p, int fork_id, int new_owner)
{
	t_table *t = p->table;
	pthread_mutex_lock(&t->forks[fork_id].mutex);
	t->forks[fork_id].owner_id = new_owner;
	pthread_mutex_unlock(&t->forks[fork_id].mutex);
}

/* ************************************************************************** */
/* 5. 哲学者のメインループ(考える->Fork要求->食べる->寝る) */
void	*philo_life(void *arg)
{
	t_philo	*ph = (t_philo *)arg;
	int		left_id = ph->id; /* 左フォークID=哲学者IDに対応 */
	int		right_id = (ph->id + ph->table->philo_count - 1)
						% ph->table->philo_count;

	while (1)
	{
		print_log(ph, "is thinking");
		request_fork(ph, left_id);
		request_fork(ph, right_id);
		ph->last_meal = now_ms();
		print_log(ph, "is eating");
		usleep(ph->table->time_to_eat * 1000);
		ph->meal_count++;
		release_fork(ph, left_id, (ph->id + 1) % ph->table->philo_count);
		release_fork(ph, right_id, (ph->id + ph->table->philo_count - 1) % ph->table->philo_count);
		print_log(ph, "is sleeping");
		usleep(ph->table->time_to_sleep * 1000);
		if (ph->table->must_eat_count > 0 && ph->meal_count
			>= ph->table->must_eat_count)
			break ;
	}
	return (NULL);
}