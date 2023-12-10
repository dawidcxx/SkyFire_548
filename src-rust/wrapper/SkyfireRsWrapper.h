#ifndef __WorldServerRs__
#define __WorldServerRs__

#include <dlfcn.h>
#include <cstdint>   
#include <string> 
#include <filesystem>
#include <mutex>

class SkyfireRsWrapper {
public:
    static SkyfireRsWrapper& getInstance() {
        static SkyfireRsWrapper instance;
        return instance;
    }

    void installHotReload();

    bool handle_spell(uint32_t spellId);

    SkyfireRsWrapper();
    ~SkyfireRsWrapper();

private:
    std::filesystem::path dynLibPath;

    void* fileWatcherHandle; 
    void* worldServerRsHandle;
    
    using WorldServerRsHandleSpellFn = bool (*)(uint32_t);

    WorldServerRsHandleSpellFn handleSpellFn;

    std::mutex loadMutex;
    void loadDynLib();
    void loadFunctionPointers();

    template <typename T>
    T loadFunctionPointer(void *__restrict __handle, const char *__restrict __name);

};


#endif