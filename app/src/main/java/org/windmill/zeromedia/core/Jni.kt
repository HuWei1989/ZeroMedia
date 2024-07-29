package org.windmill.zeromedia.core

/**
 * File description.
 *
 * @author hw
 * @date 2024/7/18
 */
object Jni {
    init {
        System.loadLibrary("hwmedia")
    }

    /**
     *
     */
    external fun initMedia(): Int

    /**
     *
     */
    external fun loadFile(path: String): Int

    external fun setMediaCallback(callback: JniCallback): Boolean
}