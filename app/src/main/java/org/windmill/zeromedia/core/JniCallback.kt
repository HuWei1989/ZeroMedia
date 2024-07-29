package org.windmill.zeromedia.core

/**
 * File description.
 *
 * @author hw
 * @date 2024/7/29
 */
abstract class JniCallback {
    abstract fun playProgress(progress: Float, current: Int, total: Int)
}