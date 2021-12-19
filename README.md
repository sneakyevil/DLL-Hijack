# DLL-Hijack
Simple one file header for hijacking dll for desired executable to do 3rd party modifying without dll injection.

### Usage
```cpp
#include "xxx.hpp"

int __stdcall DllMain(HMODULE m_hModule, DWORD m_dReason, void* m_pReserved)
{
    if (m_dReason == DLL_PROCESS_ATTACH)
    {
        sneakyevil_DllHijack::Initialize();
        
        // Your code...
    }
    
    return 1;
}
```
