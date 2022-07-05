#include "b64.h"
#include <stdio.h>
#include <string.h>

int main() {
  char *input = "gergerg,1414124124124124332\n";
  char *result = b64Encode(NULL, input, strlen(input));
  char *expected_result = "Z2VyZ2VyZywxNDE0MTI0MTI0MTI0MTI0MzMyCg==";
  if (strcmp(result, expected_result)) {
    printf("The result for encoding of string is wrong, left: %s, right: %s",
           result, expected_result);
    return 1;
  } else {
    puts("Encoding basic test passed");
  }
  char *reencoded = b64Decode(NULL, result, strlen(result));
  if (strcmp(reencoded, input)) {
    printf("The result for decoding of string is wrong, left: %s, right: %s",
           reencoded, input);
    return 1;
  } else {
    puts("Decoding basic test passed");
  }
}
