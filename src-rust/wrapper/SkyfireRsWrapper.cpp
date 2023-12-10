#include "SkyfireRsWrapper.h"
#include <iostream>
#include <dlfcn.h>
#include <link.h>
#include <string>
#include "FileWatch.hpp"

SkyfireRsWrapper::SkyfireRsWrapper()
{
    std::lock_guard<std::mutex> lock(loadMutex);
    loadDynLib();
    loadFunctionPointers();
};

SkyfireRsWrapper::~SkyfireRsWrapper()
{
    if (worldServerRsHandle)
    {
        dlclose(worldServerRsHandle);
    }

    auto fileWatcher = static_cast<filewatch::FileWatch<std::string> *>(fileWatcherHandle);
    if (fileWatcher)
    {
        delete fileWatcher;
    }
}

void SkyfireRsWrapper::installHotReload()
{
    auto handler = [this](const std::string &path, const filewatch::Event change_type)
    {
        if (change_type == filewatch::Event::added)
        {
            // TODO: this still has a race condition
            // but it works~!
            std::lock_guard<std::mutex> lock(loadMutex);

            if (dlclose(worldServerRsHandle) != 0)
            {
                throw std::runtime_error("Hot reload failed: '" + std::string(dlerror()) + "'");
            }
            this->loadDynLib();
            this->loadFunctionPointers();
        }
    };

    auto fileWatcher = new filewatch::FileWatch<std::string>(dynLibPath, handler);

    fileWatcherHandle = static_cast<void *>(fileWatcher);
}

void SkyfireRsWrapper::loadDynLib()
{
    worldServerRsHandle = dlopen("libskyfire_rs.so", RTLD_NOW | RTLD_LOCAL);
    if (!worldServerRsHandle)
    {
        auto errorMessage = "Failed to load worldserver-rs dynlib: " + std::string(dlerror());
        throw std::runtime_error(errorMessage);
    }

    struct link_map *lm;
    if (dlinfo(worldServerRsHandle, RTLD_DI_LINKMAP, &lm) == 0)
    {
        dynLibPath = std::filesystem::path(std::string(lm->l_name)).parent_path();
    }
    else
    {
        throw std::runtime_error("Failed to retrieve .so info: " + std::string(dlerror()));
    }
}

void SkyfireRsWrapper::loadFunctionPointers()
{
    handleSpellFn = loadFunctionPointer<WorldServerRsHandleSpellFn>(worldServerRsHandle, "worldserver_rs_handle_spell");
}

bool SkyfireRsWrapper::handle_spell(uint32_t spellId)
{
    return handleSpellFn(spellId);
}

template <typename T>
T SkyfireRsWrapper::loadFunctionPointer(void *__restrict __handle, const char *__restrict __name)
{
    auto fpPointer = reinterpret_cast<T>(dlsym(__handle, __name));

    if (!fpPointer)
    {
        throw std::runtime_error("Failed to load symbol from dynamic library: " + std::string(__name));
    }

    return fpPointer;
}