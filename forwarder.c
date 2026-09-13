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

static int launch_homebrew(const char *path)
{
    int ret;
    u32 size;
    void *buf;

    ret = FS_LoadFile(path, &buf, &size);
    if (ret < 0) {
        OSFatal("Failed to load file");
    }

    ret = ELF_Load(buf, size, NULL, NULL, NULL, NULL);
    if (ret < 0) {
        OSFatal("Failed to load ELF");
    }

    free(buf);

    return 0;
}

int main(int argc, char **argv)
{
    // Initialize the system
    if (SYS_Init() < 0) {
        OSFatal("SYS_Init failed");
    }

    if (FS_Init() < 0) {
        OSFatal("FS_Init failed");
    }

    if (VPAD_Init() < 0) {
        OSFatal("VPAD_Init failed");
    }

    if (AC_Init() < 0) {
        OSFatal("AC_Init failed");
    }

    // Launch our homebrew app
    launch_homebrew("sd:/wiiu/apps/hello_world/hello_world.wuhb");

    // When the app returns, launch the menu
    SYS_LaunchMenu();

    return 0;
}
