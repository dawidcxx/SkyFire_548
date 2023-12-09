#include "WorldServerRs.h"
#include <iostream>

WorldServerRs::WorldServerRs()
{
    worldServerRsHandle = dlopen("libworldserver_rs.so", RTLD_LAZY);
    if (!worldServerRsHandle)
    {
        auto errorMessage = "Failed to load worldserver-rs dynlib: " + std::string(dlerror());
        throw std::runtime_error(errorMessage);
    }
    handleSpellFn = loadFunctionPointer<WorldServerRsHandleSpellFn>(worldServerRsHandle, "worldserver_rs_handle_spell");
};

WorldServerRs::~WorldServerRs()
{
    if (worldServerRsHandle)
    {
        dlclose(worldServerRsHandle);
    }
}

bool WorldServerRs::handle_spell(uint32_t spellId)
{
    return handleSpellFn(spellId);
}

template <typename T>
T WorldServerRs::loadFunctionPointer(void *__restrict __handle, const char *__restrict __name)
{
    auto fpPointer = reinterpret_cast<T>(dlsym(__handle, __name));

    if (!fpPointer)
    {
        throw std::runtime_error("Failed to load symbol from dynamic library: " +std::string(__name));
    }
    
    return fpPointer;
}