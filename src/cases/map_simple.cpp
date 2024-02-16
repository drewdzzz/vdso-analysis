/**
 * The case creates a simple in-memory index (std::map) and inserts there
 * pairs containing number and current time. Hence, `get_time` is called
 * on every insert.
 */

#include <map>
#include <utility>

#include <utils/common.h>

static std::map<
	std::size_t,
	std::pair<std::size_t, double>
> DB;

static const std::size_t ITER_NUM = 1e6;

int
main(void)
{
	time_init();
	for (std::size_t i = 0; i < ITER_NUM; i++) {
		double curr_time = get_time();
		DB.emplace(std::make_pair(i, std::make_pair(i, curr_time)));
	}
	return 0;
}
