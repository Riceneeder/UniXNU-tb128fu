// SPDX-License-Identifier: BSD-2-Clause-Patent
// No-op definitions of the probe hooks the patched XNU references while tb128fu_defconfig leaves their component out.
// Each hook runs only on its boot argument, which board.toml does not pass; the kernel link needs the symbol anyway.

// offline-component-load-probes.patch, bsd_init: called on offline-legacy-register=1 (NativeLegacyDisplay). Weak: with
// CONFIG_XNU_NATIVE_LEGACY_DISPLAY the display archive's LegacyDisplayProbe.cpp defines the real probe.
void native_legacy_display_probe(void);
__attribute__((weak)) void native_legacy_display_probe(void)
{
}

// boot_progress_poll is a weak reference of NativeUfs/NativeVirtioBlock; CONFIG_XNU_BOOT_PROGRESS links the real
// definition from build/boot-progress, and an undefined weak symbol stays a null call when the page is off.

// The display archive defines the diagnostics storage and the GPU hand-off. The first kernel of a fresh tree is linked
// without it (it needs a previous kernel), so these weak definitions keep that link complete; the second kernel's
// strong definitions replace them.
struct IOMemoryDescriptor;
__attribute__((weak)) struct IOMemoryDescriptor *native_gop_handoff_memory(void)
{
    return 0;
}
__attribute__((weak)) int native_gop_handoff_call(unsigned int op, void *task, const void *in,
                                                  unsigned long in_size, void *out, unsigned long out_size)
{
    (void)op;
    (void)task;
    (void)in;
    (void)in_size;
    (void)out;
    (void)out_size;
    return 0;
}
__attribute__((weak)) char tb128fu_gpu_dvfs[2][120];
__attribute__((weak)) char tb128fu_ddr_rows[3][120];
__attribute__((weak)) char tb128fu_rpm_rows[3][120];
__attribute__((weak)) char tb128fu_usb_rows[5][120];
__attribute__((weak)) void tb128fu_usb_log_put(const void *data, unsigned long length)
{
    (void)data;
    (void)length;
}
