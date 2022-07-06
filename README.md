# b64.h
base64 single header encode/decode

## Works with C89

```c
#include <stdio.h>
#include "b64.h"

int main(int argc, char **argv)
{
// External buffer
    char b64enc[1024];
    char b64dec[1024];
    
    b64Encode(b64enc, argv[1], strlen(argv[1]));
    printf("%s\n", b64enc);
    
    b64Decode(b64dec, b64enc, strlen(b64enc));
    printf("%s\n", b64dec);

// Heap allocation done by passing NULL to dst, don't forget to free()
    char* b64encoded = b64Encode(NULL, argv[1], strlen(argv[1]));
    printf("%s\n", b64enc);
    
    char* b64decoded = b64Decode(NULL, b64enc, strlen(b64enc));
    printf("%s\n", b64dec);
}
```

```bash
$ ./a.out sus
c3Vz
sus
```


