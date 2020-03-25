Cross-platform runtime DLL manager.

## Usage

#### Native Library

Windows specific conventions used. dllman is compatible with both Mac and Linux. Use `__attribute__((visibility("default")))` if needed.

`print.c` compiled into `print.dll`:
```
__declspec(dllexport) void print(const char* message)
{
  printf("Printing Message: %s\n", message);
}
```


Standard `main.c`:
```
#include "dllman/native.h"

int main()
{
  dllman::NativeLibrary lib{};
  lib.load({ "print.dll" });
  
  void(*print)(const char*) = lib.load({ "print" });
  print("This is a message that will be printed.");
  
  return 0;
}
```

Container `main.c`:
```
#include "dllman/native.h"
#include "dllman/container.h"

class Print
{
  dllman::Container<dllman::NativeLibrary> lib_{{ "print.dll" }}; // Must be before properties in class in order to initialize first.
public:
  void(*print)(const char*) = lib_[{ "print" }]; // GetDesc
}

int main()
{
  Print lib{};
  lib.print("This is a message that will be printed.");

  return 0;
}

```

#### CoreClr Library

##### Note:
- Compiling an executable `csproj` with `dotnet publish --self-contained` WILL create necessary runtime libs in the same output folder. This method will be used in the example. You can manually specify a folder as the second `LoadDesc` parameter. These folders can be found with `dotnet --list-runtimes`.

- You can use the function `locate_runtime_library_path` to attempt to locate latest runtime. The first parameter is an optional preferred version that will be returned if found, otherwise latest.

`Utils.cs` compiled into `Test.dll`:
```
using System;
using System.Runtime.InteropServices;

namespace Test
{
  public class Utils
  {
    static void Main(string[] args)
    {
      // This only exists to force dotnet to generate runtime libs.
    }
    
    public static void Print([MarshalAs(UnmanagedType.LPStr)]string msg)
    {
      Console.WriteLine($"C# Message: {msg}");
    }
  }
}
```

`main.c`:
```
#include "dllman/corclr.h"

int main()
{
  dllman::CoreClrLibrary lib;
  lib.load({ "Test.dll" }); // Here you can specify a runtime libraries path.
  
  void(*print)(const char*) = lib.get({ "Print", "Test.Utils" });
  print("This is a message that will be printed.");

  return 0;
}
```

## Reference

Classes
- NativeLibrary
- CoreClrLibrary

All classes extend `Library` and have the methods as shown:

| Name    | Parameters | Function                                                                 |
|---------|------------|--------------------------------------------------------------------------|
| load    | LoadDesc   | Loads library. Will unload existing and will be unloaded on destruction. |
| unload  |            | Unloads library.                                                         |
| get     | GetDesc    | Gets a method from loaded library or `nullptr` when none is loaded.      |

GetDesc
- `name_`:        Name to get.
- `typeName_`:    Name of type it is within (C# Usage).

LoadDesc
- `path_`:        Path of library.
- `runtimeLibs_`: Location of runtime libraries, will use `path_` if empty (CoreClr Usage).

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
