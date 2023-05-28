# Cheat SDK

## Conventions
1. Classes prefix: "C", interfaces prefix: "I"
```cpp
class CSomeClass;
class ISomeInterface;
```

2. Structs postfix: "_t"
```cpp
struct SomeStruct_t;
```

3. Enums prefix: "E"
```cpp
enum ESomeEnum
```

4. Macroses 
```cpp
#define SOME_MACROS
```

#

## Code Style 
*Use [PascalCase](https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/coding-style/coding-conventions) with variable type prefix*

1. Local variables:
```cpp
int     iSomeInt;
float   flSomeFloat;
bool    bSomeBool;
```
2. Member class & struct variables have a prefix "m_":
```cpp
class CSomeClass
{
public:
  int     m_iSomeInt;
  float   m_flSomeFloat;
  bool    m_bSomeBool;
};

struct SomeStruct_t
{
  int     m_iSomeInt;
  float   m_flSomeFloat;
  bool    m_bSomeBool;
};
```

#

## Dependencies

1. [Dear ImGui](https://github.com/ocornut/imgui/)
2. [Json](https://github.com/nlohmann/json/)
4. [Minhook](https://github.com/TsudaKageyu/minhook/)
