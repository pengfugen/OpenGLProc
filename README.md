# OpenGLProc
Android 使用NDK处理BItmap及直接控制SurfaceView的Surface的显示  
步骤：  
(1) Surface转成ANativeWindow  
ANativeWindow * window = ANativeWindow_fromSurface(env, surface);  
(2) 锁定缓存区  
ANativeWindow_lock(window, & windowBuffer, NULL);  
(3) 填充缓存区  
(4) 解锁缓存区交给SurfaceFlinger消费并合成，等到VSYNC信号来后开始描画  
ANativeWindow_unlockAndPost(window);  

注意:  
OpenGLSurfaceView和GraphicBuffer的width和height可以不一致，图层合成以GraphicBuffer的大小为准，GraphicBuffer决定了Layer的大小。