#ifndef __WorldServerRs__
#define __WorldServerRs__


#include <dlfcn.h>
#include <cstdint>

class WorldServerRs {
public:
    static WorldServerRs& getInstance() {
        static WorldServerRs instance;
        return instance;
    }

    bool handle_spell(uint32_t spellId);


private:
    void* worldServerRsHandle;

    using WorldServerRsHandleSpellFn = bool (*)(uint32_t);

    WorldServerRsHandleSpellFn handleSpellFn;


    WorldServerRs();
    ~WorldServerRs();

    template <typename T>
    T loadFunctionPointer(void *__restrict __handle, const char *__restrict __name);

};


#endif