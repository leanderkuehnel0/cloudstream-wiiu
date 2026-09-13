#include <whb/log.h>
#include <whb/log_console.h>
#include <whb/log_udp.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <coreinit/memory.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memheap.h>
#include <coreinit/front.h>
#include <coreinit/screen.h>
#include <coreinit/os.h>
#include <coreinit/foundation.h>
#include <coreinit/async.h>
#include <coreinit/cache.h>
#include <coreinit/debug.h>
#include <coreinit/error.h>
#include <coreinit/title.h>
#include <fs/fs.h>
#include <fs/fsa.h>
#include <vpad/input.h>
#include <acp/acp.h>
#include <proc_ui/procui.h>
#include <gx2/gx2.h>
#include <gx2/draw.h>
#include <gx2r/rpg.h>
#include <gx2r/state.h>
#include <gx2r/sampler.h>
#include <gx2r/shader.h>
#include <gx2r/target_buffer.h>
#include <gx2r/tex.h>
#include <gx2r/vertex_shader.h>
#include <gx2r/pixel_shader.h>
#include <gx2r/vertex_attrib.h>
#include <gx2r/index_buf.h>
#include <gx2r/constant_buf.h>
#include <gx2r/texture.h>
#include <gx2r/surface.h>
#include <gx2r/context.h>
#include <gx2r/misc.h>
#include <coreinit/elfformat.h>
#include <coreinit/elfload.h>

int main(int argc, char **argv) {
    // Initialize required services
    if (SYS_Init() < 0) {
        // If we can't initialize, we can't do much. Just halt.
        while (1) {}
    }
    if (FS_Init() < 0) {
        SYS_LaunchMenu();
    }
    if (VPAD_Init() < 0) {
        // Not critical, continue
    }
    if (AC_Init() < 0) {
        // Not critical, continue
    }

    // Load the homebrew from SD card
    const char *path = "sd:/wiiu/apps/hello_world/hello_world.wuhb";
    u32 size;
    void *buf = NULL;
    int ret = FS_LoadFile(path, &buf, &size);
    if (ret < 0 || buf == NULL) {
        // Failed to load file, launch menu
        SYS_LaunchMenu();
        return 0;
    }

    // Execute the homebrew
    ret = ELF_Load(buf, size, NULL, NULL, NULL, NULL);
    free(buf);

    if (ret < 0) {
        // Failed to load ELF, launch menu
        SYS_LaunchMenu();
        return 0;
    }

    // If ELF_Load returns, the homebrew has exited
    // Launch the menu to return to the home screen
    SYS_LaunchMenu();

    return 0;
}