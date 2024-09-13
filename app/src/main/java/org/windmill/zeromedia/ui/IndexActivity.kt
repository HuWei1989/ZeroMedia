package org.windmill.zeromedia.ui

import android.Manifest
import android.os.Bundle
import android.os.Environment
import android.view.View
import android.view.View.OnClickListener
import androidx.activity.ComponentActivity
import com.tbruyelle.rxpermissions3.RxPermissions
import org.windmill.zeromedia.R
import org.windmill.zeromedia.base.BaseActivity
import org.windmill.zeromedia.core.Jni
import org.windmill.zeromedia.databinding.IndexActivityBinding

/**
 * File description.
 *
 * @author hw
 * @date 2024/7/18
 */
class IndexActivity : BaseActivity(), OnClickListener {

    private lateinit var viewBinding: IndexActivityBinding

    private val permission by lazy { RxPermissions(this) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        viewBinding = IndexActivityBinding.inflate(layoutInflater)
        setContentView(viewBinding.root)
        viewBinding.btnMediaInit.setOnClickListener(this)
        viewBinding.btnMediaFileList.setOnClickListener(this)
    }

    override fun onClick(v: View?) {
        when (v?.id) {
            R.id.btn_media_init -> {
                permission.requestEachCombined(
                    Manifest.permission.WRITE_EXTERNAL_STORAGE,
                    Manifest.permission.READ_EXTERNAL_STORAGE
                ).subscribe { permission ->
                    if (permission.granted) {
                        Jni.initMedia()
                    } else if (permission.shouldShowRequestPermissionRationale) {

                    } else {

                    }
                }
            }

            R.id.btn_media_file_list -> {
                permission.requestEachCombined(
                    Manifest.permission.WRITE_EXTERNAL_STORAGE,
                    Manifest.permission.READ_EXTERNAL_STORAGE
                ).subscribe { permission ->
                    if (permission.granted) {
                        Jni.loadFile(
                            arrayListOf(
                                "${Environment.getExternalStorageDirectory().absolutePath}/TestVideo/1.mp4",
                                "${Environment.getExternalStorageDirectory().absolutePath}/TestVideo/2.mp4",
                                "${Environment.getExternalStorageDirectory().absolutePath}/TestVideo/3.mp4",
                                "${Environment.getExternalStorageDirectory().absolutePath}/TestVideo/4.mp4"
                            )
                        )
                    } else if (permission.shouldShowRequestPermissionRationale) {

                    } else {

                    }
                }

            }
        }
    }
}