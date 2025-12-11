#include "philo.h"

uint64_t	ft_atol_positive(const char *nptr)
{
	long long	res;

	res = 0;
	if (!nptr)
		return (LONG_MAX);
	while (*nptr)
	{
		res = res * 10 + (*nptr - '0');
		if (res > INT_MAX)
			return (LONG_MAX);
		nptr++;
	}
	return ((long) res);
}
