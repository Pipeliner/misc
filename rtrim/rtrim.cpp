#include <cstring>
#include <cstdio>
#include <cstdlib>

void trivialTrimRight(char *str) {
	if (!str)
		return;

	char *spaces = nullptr;
	while (*str) {
		if (*str == ' ' && !spaces)
			spaces = str;
		else if (*str != ' ' && spaces)
			spaces = nullptr;

		str++;
	}

	if (spaces)
		*spaces = '\0';
}

int test() {
	const int sample_count = 8;
	int errors = 0;

	const char *sample_strings[sample_count] = 
	{
		"nothing to trim",
		"trim multiple chars     ",
		"trim one char ",
		"                   ",
		" ",
		"a",
		"",
		nullptr
	};

	const char *sample_results[sample_count] =
	{
		"nothing to trim",
		"trim multiple chars",
		"trim one char",
		"",
		"",
		"a",
		"",
		nullptr
	};

	for (int i = 0; i < sample_count; i++) {
		const char *sample = sample_strings[i];
		char *copy = nullptr;
		if (sample)
			copy = strdup(sample);

		const char *expected = sample_results[i];

		trivialTrimRight(copy);
		if (expected == nullptr && copy != nullptr) {
			printf("Trimmed nullptr to '%s'.\n", copy);
			errors++;
		} else if (expected && strcmp(copy, expected)) {
			printf("Trimmed '%s' to '%s' instead of expected '%s'.\n", 
				sample, copy, expected);
			errors++;
		}

		free(copy);
	}

	return errors;
}

int main() {
	int errors = test();
	printf("%d errors.\n", errors);
	return errors;
}