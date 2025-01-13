#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
	// TODO: Create space to store the string "hello"
	char* message = malloc(sizeof("hello") + 1);
	if (message == NULL) {
		fprintf(stderr, "Memory allocation error: %s\n", strerror(errno));
		return 1;
	}
	strcpy(message, "hello");


	// Print out the value before we change message
	printf("Before copying: %s\n", message);

	// Creates another_string that contains a longer string
	char* long_message = "Here's a really long string";

	char* newMessage = realloc(message, strlen(long_message) + 1);
	if (newMessage == NULL) {
		fprintf(stderr, "Memory allocation error: %s\n", strerror(errno));
		free(message); // Free previously allocated memory
		return 1;
	}

	message = newMessage;

	strcpy(message, long_message);


	// Print out the value after we change message
	printf("After copying: %s\n", message);

	free(message);
	return 0;
}
