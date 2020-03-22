Cross-platform runtime DLL manager.

## Usage
1. dllman stores all related data in a `DmLibrary` struct, of which can be created with `dm_new`.
2. Librares can be loaded and unloaded via `dm_load` and `dm_unload`. Loading WILL NOT unload a loaded library and unload WILL check if a library has been loaded.
3. `dm_get` can be used to get functions.
4. Free any created libraryes with `dm_free`. Freeing a loaded library WILL unload it.

## Compatibility

| Support        | Implmenation        | Language          | CMake Option  |
|:--------------:|---------------------|-------------------|---------------|
|Functions Only  | Windows.h           | Native (Windows)  |NATIVE         |
|Functions Only  | libdl               | Native (UNIX)     |NATIVE         |
|No Support      | Mono                | Mono              |CS_MONO        |
|No Support      | CoreClrHost.h       | .NET Core <  3.0  |CS_DNC         |
|No Support      | nethost and hostfxr | .NET Core >= 3.0  |CS_DNC         |
