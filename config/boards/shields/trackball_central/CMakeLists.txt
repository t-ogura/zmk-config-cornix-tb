# Trackball central shield: reuse the battery LED indicator code from the
# peripheral trackball shield (it only subscribes to battery events, so it
# is role-agnostic).
target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../trackball_paw3222/trackball_led.c)
