#include <jni.h>
#include <ifaddrs.h>
#include <string.h>

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_Devshuvo_hyperTour_ab_isVpnActive(JNIEnv *env, jclass clazz, jobject context) {
    struct ifaddrs *ifap, *ifa;

    if (getifaddrs(&ifap) == -1) return JNI_FALSE;

    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_name && (
            strstr(ifa->ifa_name, "tun") || 
            strstr(ifa->ifa_name, "ppp") ||
            strstr(ifa->ifa_name, "wg"))) {
            freeifaddrs(ifap);
            return JNI_TRUE;
        }
    }

    freeifaddrs(ifap);
    return JNI_FALSE;
}