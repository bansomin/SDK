/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

/*
*在 JAVA 层初始化 AnySDK Framework 框架
* */
import com.anysdk.framework.PluginWrapper;

import android.os.Bundle;
import android.content.Intent;
import android.content.res.Configuration;

public class AppActivity extends Cocos2dxActivity {

    protected void onCreate (Bundle savedState){
        super.onCreate(savedState); //且 super.onCreate(savedState); 请在 PluginWrapper.init(this); 之前调用，因为 init 的时候需要调用 C++ 函数，而 so 文件是在 onCreate 时加载。
        PluginWrapper.init(this);

        PluginWrapper.setGLSurfaceView(Cocos2dxGLSurfaceView.getInstance());
        PluginWrapper.loadAllPlugins();
        //AnySDK 的回调函数默认是在主线程，使用 Cocos2d-x 的话，可以在 onCreate 加上
        // PluginWrapper.setGLSurfaceView(Cocos2dxGLSurfaceView.getInstance());
        // 将回调改成在 GL 线程，不在 GL 线程里操作界面会有问题。
    }

    //重写 Activity 生命周期相关方法
    @Override
    protected void onDestroy() {
        PluginWrapper.onDestroy();
        super.onDestroy();
    }

    @Override
    protected void onPause() {
        PluginWrapper.onPause();
        super.onPause();
    }

    @Override
    protected void onResume() {
        PluginWrapper.onResume();
        super.onResume();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        PluginWrapper.onActivityResult(requestCode, resultCode, data);
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        PluginWrapper.onNewIntent(intent);
        super.onNewIntent(intent);
    }

    @Override
    protected void onStop() {
        PluginWrapper.onStop();
        super.onStop();
    }

    @Override
    protected void onRestart() {
        PluginWrapper.onRestart();
        super.onRestart();
    }

    @Override
    protected void onStart() {
        PluginWrapper.onStart();
        super.onStart();
    }

    @Override
    public void onBackPressed() {
        PluginWrapper.onBackPressed();
        super.onBackPressed();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        PluginWrapper.onConfigurationChanged(newConfig);
        super.onConfigurationChanged(newConfig);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        PluginWrapper.onRestoreInstanceState(savedInstanceState);
        super.onRestoreInstanceState(savedInstanceState);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        PluginWrapper.onSaveInstanceState(outState);
        super.onSaveInstanceState(outState);
    }

    public static native void nativeInitPlugins () ;

}
