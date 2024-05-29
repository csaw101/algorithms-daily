#include <stdbool.h>
#include <math.h>

bool is_prime(const int number) {
	if (number < 2) return false;
	if (number == 2) return true;
	if (number % 2 == 0) return false;
	for (int i = 3; i <= floor(sqrt((double) number)); i += 2) {
		if (number % i == 0) {
			return false;
		}
	}
	return true;
}

int next_prime(int number) {
	while (is_prime(number) == false) {
		number++;
	}

	return number;
}
