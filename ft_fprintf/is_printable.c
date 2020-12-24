
#include "lprintf.h"

int		is_printable(char c)
{
	if (c >= 32 && c <= 127)
		return (1);
	return (0);
}
