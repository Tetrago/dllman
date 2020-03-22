Cross-platform runtime DLL manager.

## Usage
1. dllman stores all related data in a `DmLibrary` struct, of which can be created with `dm_new`.
2. Librares can be loaded and unloaded via `dm_load` and `dm_unload`. Loading WILL NOT unload a loaded library and unload WILL check if a library has been loaded.
3. `dm_get` can be used to get functions.
4. Free any created libraryes with `dm_free`. Freeing a loaded library WILL unload it.

## Compatibility

| Support                   | Implmenation        | Language          | CMake Option  |
|:-------------------:|---------------------|-------------------|---------------|
|<ul><li>[x]</li></ul>| Windows.h           | Native (Windows)  |NATIVE_WIN     |
|<ul><li>[x]</li></ul>| libdl               | Native (UNIX)     |NATIVE_LIBDL   |
|<ul><li>[ ]</li></ul>| Mono                | Mono              |CS_MONO        |
|<ul><li>[ ]</li></ul>| CoreClrHost.h       | .NET Core <  3.0  |CS_DNC_CORECLR |
|<ul><li>[ ]</li></ul>| nethost and hostfxr | .NET Core >= 3.0  |CS_DNC_HOSTFXR |
