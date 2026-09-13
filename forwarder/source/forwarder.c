#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <coreinit/memory.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memheap.h>
#include <coreinit/debug.h>
#include <coreinit/os.h>
#include <fs/fs.h>
#include <coreinit/elfformat.h>
#include <coreinit/elfload.h>
#include <coreinit/dynload.h>

int main(int argc, char **argv) {
    // Acquire coreinit.rpl handle
    unsigned int coreinit_handle;
    if (OSDynLoad_Acquire("coreinit.rpl", &coreinit_handle) != 0) {
        while (1) {}
    }

    // Get function pointers
    unsigned int SYS_Init_addr = 0;
    unsigned int FS_Init_addr = 0;
    unsigned int FS_LoadFile_addr = 0;
    unsigned int ELF_Load_addr = 0;
    unsigned int SYS_LaunchMenu_addr = 0;

    OSDynLoad_FindExport(coreinit_handle, 0, "SYS_Init", &SYS_Init_addr);
    OSDynLoad_FindExport(coreinit_handle, 0, "FS_Init", &FS_Init_addr);
    OSDynLoad_FindExport(coreinit_handle, 0, "FS_LoadFile", &FS_LoadFile_addr);
    OSDynLoad_FindExport(coreinit_handle, 0, "ELF_Load", &ELF_Load_addr);
    OSDynLoad_FindExport(coreinit_handle, 0, "SYS_LaunchMenu", &SYS_LaunchMenu_addr);

    if (!SYS_Init_addr || !FS_Init_addr || !FS_LoadFile_addr || !ELF_Load_addr || !SYS_LaunchMenu_addr) {
        while (1) {}
    }

    // Cast function pointers
    int (*SYS_Init)() = (void*)SYS_Init_addr;
    int (*FS_Init)() = (void*)FS_Init_addr;
    int (*FS_LoadFile)(const char*, void**, unsigned int*) = (void*)FS_LoadFile_addr;
    int (*ELF_Load)(void*, unsigned int, void*, void*, void*, void*) = (void*)ELF_Load_addr;
    int (*SYS_LaunchMenu)() = (void*)SYS_LaunchMenu_addr;

    // Initialize required services
    if (SYS_Init() < 0) {
        while (1) {}
    }
    if (FS_Init() < 0) {
        SYS_LaunchMenu();
    }

    // Load the homebrew from SD card
    const char *path = "sd:/wiiu/apps/hello_world/hello_world.wuhb";
    u32 size;
    void *buf = NULL;
    int ret = FS_LoadFile(path, &buf, &size);
    if (ret < 0 || buf == NULL) {
        SYS_LaunchMenu();
        return 0;
    }

    // Execute the homebrew
    ret = ELF_Load(buf, size, NULL, NULL, NULL, NULL);
    free(buf);

    if (ret < 0) {
        SYS_LaunchMenu();
        return 0;
    }

    // If ELF_Load returns, the homebrew has exited
    SYS_LaunchMenu();

    return 0;
}