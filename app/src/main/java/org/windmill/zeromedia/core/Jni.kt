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
    external fun loadFile(pathList: ArrayList<String>): Int

    external fun setMediaCallback(callback: JniCallback): Boolean

    /**
     * 合并两个以上的文件
     * 视频与视频
     * 视频与音频
     * 音频与音频
     */
    external fun mergeMedia(pathList: ArrayList<String>): Boolean

    external fun stopMergeMedia(): Boolean
}