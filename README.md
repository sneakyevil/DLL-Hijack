# Version-Hijack
Simple one file header for hijacking windows version.dll for desired executable to do 3rd party modifying without dll injection.

### Usage
```cpp
#include "VersionHijack.hpp"

int __stdcall DllMain(HMODULE m_hModule, DWORD m_dReason, void* m_pReserved)
{
    if (m_dReason == DLL_PROCESS_ATTACH)
    {
        VersionHijack::Initialize();
        
        // Your code...
    }
    
    return 1;
}
```
