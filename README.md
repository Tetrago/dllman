Cross-platform runtime DLL manager.

## Usage
1. dllman stores all related data in a `ddlman::Library<T>` class, where T is an enum `dllman::Support` (values listed below).
2. Librares can be loaded and unloaded via the `load` and `unload` methods of a library object. Loading WILL unload a loaded library and unload WILL check if a library has been loaded. Note that the destructor WILL unload a loaded library.
3. The `get` method can be used to get pointers.

`dllman::Support`:
- `Native`

## Compatibility

| Support        | Implmenation        | Language          | CMake Option  |
|:--------------:|---------------------|-------------------|---------------|
|Functions Only  | Windows.h           | Native (Windows)  |NATIVE         |
|Functions Only  | libdl               | Native (UNIX)     |NATIVE         |
|No Support      | Mono                | Mono              |CS_MONO        |
|No Support      | CoreClrHost.h       | .NET Core <  3.0  |CS_DNC         |
|No Support      | nethost and hostfxr | .NET Core >= 3.0  |CS_DNC         |
