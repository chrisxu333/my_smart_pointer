## Naive implementation of C++ smart pointer
![GitHub](https://img.shields.io/github/license/chrisxu333/my_smart_pointer)
![GitHub last commit](https://img.shields.io/github/last-commit/chrisxu333/my_smart_pointer)

Current implementation includes my_shared_ptr and my_unique_ptr, which are all thread-safe. However, there're still some interfaces that are missing from the code, such as overload bool, swap function, implicit conversion prevention, I even want an auxilary class that contains functions like make_shared.

Anyway, feel free to use this as a toy library and PR is very much welcome!