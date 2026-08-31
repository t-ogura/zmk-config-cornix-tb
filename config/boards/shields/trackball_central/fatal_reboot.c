/*
 * Reboot on fatal error instead of halting.
 *
 * Zephyr's default k_sys_fatal_error_handler() is __weak and ends in
 * arch_system_halt(): the CPU spins forever. On a wireless keyboard central
 * that is indistinguishable from "the device turned itself off" -- BLE
 * links drop, USB HID stops, LEDs freeze -- and the only recovery is a
 * manual power cycle. This override flushes the log backends (so a USB
 * logging build still shows the fault banner, e.g. the MPU stack-overflow
 * report naming the offending thread) and then performs a cold reboot,
 * which brings the split back up in a couple of seconds.
 *
 * Diagnostic value is preserved: with CONFIG_ZMK_USB_LOGGING=y the panic
 * output (fault reason, faulting thread, register dump) is emitted
 * synchronously before the reboot.
 */

#include <zephyr/fatal.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>
#include <zephyr/sys/reboot.h>

LOG_MODULE_REGISTER(fatal_reboot, CONFIG_ZMK_LOG_LEVEL);

void k_sys_fatal_error_handler(unsigned int reason, const struct arch_esf *esf) {
    ARG_UNUSED(esf);

    LOG_PANIC();
    LOG_ERR("Fatal error %u -- rebooting (fatal_reboot.c override)", reason);

    /* Give the panic-mode log backends a moment to drain (USB CDC). */
    k_busy_wait(50 * USEC_PER_MSEC);

    sys_reboot(SYS_REBOOT_COLD);
    CODE_UNREACHABLE;
}
