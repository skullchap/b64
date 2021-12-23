# b64.h
base64 single header encode/decode

```c
#include <stdio.h>
#include "b64.h"

int main(int argc, char **argv)
{
    char* b64encoded = b64Encode(argv[1]);
    printf("%s\n", b64encoded);
    
    char* b64decoded = b64Decode(b64encoded);
    printf("%s\n", b64decoded);
}
```

```bash
$ ./a.out sus
c3Vz
sus
```
