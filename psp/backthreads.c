#include <pspuser.h>

PSP_MODULE_INFO("mcid_cov", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(-1);

int backXMB(int a, int b, void* c)
{
	sceKernelExitGame();
	return 0;
}


int thread(SceSize a, void* b)
{
	sceKernelRegisterExitCallback(
    sceKernelCreateCallback("cov_back_xmb", backXMB, NULL));
	sceKernelSleepThreadCB();
	return 0;
}

void background(void) __attribute__((constructor));
void background(void)
{
	int id = sceKernelCreateThread("cov_back_thread", thread, 0x11, 0x7D0, 0, 0);
	if (id >= 0)
        sceKernelStartThread(id, 0, 0);
}
