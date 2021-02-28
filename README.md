# About
*encoded-ptr* is a generic wrapper for EncodePointer / DecodePointer Win32 apis. It was made for learning purposes and may not be a good solution to be used in production as each call to [EncodePointer](https://docs.microsoft.com/en-us/previous-versions/bb432254(v=vs.85)) / [DecodePointer](https://docs.microsoft.com/en-us/previous-versions/bb432242(v=vs.85)) queries the kernel and introduces a significant run time overhead.

# Usage
```
#include "encoded-ptr.hpp"

int main()
{
    auto object = encoded_ptr<Object>::create(args);
}
```
