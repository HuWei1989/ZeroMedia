package org.windmill.zeromedia.ui

import android.os.Bundle
import org.windmill.zeromedia.base.BaseActivity
import org.windmill.zeromedia.databinding.IndexActivityBinding

/**
 * File description.
 *
 * @author hw
 * @date 2024/7/18
 */
class IndexActivity : BaseActivity() {

    private lateinit var viewBinding: IndexActivityBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        viewBinding = IndexActivityBinding.inflate(layoutInflater)
        setContentView(viewBinding.root)
    }
}