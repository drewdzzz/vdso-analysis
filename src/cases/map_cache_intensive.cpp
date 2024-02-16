/**
 * The case creates a simple in-memory index (std::map) and inserts there
 * pairs containing long string and current time. Hence, `get_time` is called
 * on every insert.
 * 
 * The benchmark is designed so that the cache lines are actively preempted.
 */

#include <map>
#include <string>
#include <utility>

#include <utils/common.h>

static std::map<
	std::size_t,
	std::pair<std::string, double>
> DB;

static char
random_char(void)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
        return alphanum[rand() % (sizeof(alphanum) - 1)];
}

static const std::size_t ITER_NUM = 1e6;
static const std::size_t CACHE_LINE_SIZE = 64;
static const std::size_t VALUE_SIZE = CACHE_LINE_SIZE * 32;


int
main(void)
{
	time_init();
	srand(time(NULL));

	std::string template_value = std::string();
	for (std::size_t i = 0; i < VALUE_SIZE; i++)
		template_value += random_char();

	for (std::size_t i = 0; i < ITER_NUM; i++) {
		std::string value = template_value;
		for (std::size_t i = 0; i < VALUE_SIZE; i += CACHE_LINE_SIZE)
			template_value[i] = random_char();
		double curr_time = get_time();
		DB.emplace(std::make_pair(i, std::make_pair(std::move(value), curr_time)));
	}
	return 0;
}
