Cross-platform runtime DLL manager.

## Usage

Classes
- NativeLibrary
- CoreClrLibrary

All classes extend `Library` and have the methods as shown:

| Name    | Function                                                                 |
|---------|--------------------------------------------------------------------------|
| load    | Loads library. Will unload existing and will be unloaded on destruction. |
| unload  | Unloads library.                                                         |
| get     | Gets a method from loaded library or `nullptr` when none is loaded.      |

## Compatibility

| Support        | Implmenation        | Language          | CMake Option              |
|:--------------:|---------------------|-------------------|---------------------------|
| Supported      | Windows.h           | Native (Windows)  | INCLUDE_NATIVE            |
| Supported      | libdl               | Native (UNIX)     | INCLUDE_NATIVE            |
| Not Supported  | Mono                | Mono              | INCLUDE_CS_MONO           |
| Supported      | CoreClr             | .NET Core         | INCLUDE_CS_DNC_CORECLR    |
| Not Supported  | HostFXR             | .NET Core         | INCLUDE_CS_DNC_HOSTFXR    |

Note
- `INCLUDE_CS_DNC_CORECLR` will override `INCLUDE_NATIVE` to `ON`. It is required for library loading.
