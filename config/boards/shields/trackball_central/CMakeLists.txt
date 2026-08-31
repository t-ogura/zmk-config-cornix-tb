# Trackball central shield sources.
#
# fatal_reboot.c: reboot instead of halting on a Zephyr fatal error. This
# board runs with HW stack protection (MPU guard), so a stack overflow or
# any other fatal fault would otherwise leave the keyboard's central sitting
# in arch_system_halt() -- from the desk it looks like the device powered
# off. A cold reboot brings the split back within a couple of seconds.
target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/fatal_reboot.c)
