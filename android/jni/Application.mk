# Build both ARMv5TE and ARMv7-A and x86 machine code.
APP_PLATFORM := android-10
#APP_ABI := armeabi armeabi-v7a x86
APP_CPPFLAGS += -frtti
APP_STL := gnustl_static
APP_DEBUG := true
