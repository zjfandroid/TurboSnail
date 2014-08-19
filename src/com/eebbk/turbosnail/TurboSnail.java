/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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
package com.eebbk.turbosnail;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;
import android.os.Handler;

import com.eebbk.gamebase.data.DataCallBack;
import com.eebbk.gamebase.data.DataControl;
import com.eebbk.gamebase.pojo.GameType;
import com.eebbk.gamebase.pojo.InfoChart;
import com.eebbk.gamebase.pojo.InfoChart.InfoRanking;

public class TurboSnail extends Cocos2dxActivity{
	
	private static Handler mHandler = new Handler();
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// TurboSnail should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

	public static void submitGameScore(final int score) 
	{
		mHandler.post(new Runnable() {
			
			@Override
			public void run() {
				
				DataControl.getInstance().submitGameScore(getContext(), score, GameType.ARENA, new DataCallBack<InfoChart.InfoRanking>() {

					@Override
					public void onSuccess(InfoRanking data) {
						if(null != data){
							int rank = Integer.parseInt(data.getRankNumber());
							int score = Integer.parseInt(data.getTotalScore());
							System.out.println(rank + "________onSuccess_________" + score);
							setRank(rank,score);						
						}
					}

					@Override
					public void onFailure(String msg) {
						System.out.println("________onFailure_________" + msg);
					}
				});
			}
		});
	}    
	
    public static native int setRank(int rank,int score);
    
    static {
    	System.loadLibrary("bbkcocos2d");
        System.loadLibrary("cocos2dcpp");
    }     
}
