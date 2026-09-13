#include "/opt/devkitpro/wut/include/whb/log.h"
#include "/opt/devkitpro/wut/include/whb/log_console.h"
#include "/opt/devkitpro/wut/include/whb/log_udp.h"
#include "/opt/devkitpro/wut/include/coreinit/thread.h"
#include "/opt/devkitpro/wut/include/coreinit/time.h"

int main() {
    // Initialize the log console
    WHBLogConsoleInit();
    WHBLogPrintf("Hello, World!\n");

    // Wait for a while so the user can see the message
    // We'll wait for 5 seconds (5 * 1000 milliseconds)
    OSSleepTicks(OSMillisecondsToTicks(5000));

    // Deinitialize the log console
    WHBLogConsoleFree();

    return 0;
}