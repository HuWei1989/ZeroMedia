package org.windmill.zeromedia.core

/**
 * File description.
 *
 * @author hw
 * @date 2024/7/18
 */
class Jni {
    init {
        System.loadLibrary("hwmedia")
    }
    external fun initMedia()
}