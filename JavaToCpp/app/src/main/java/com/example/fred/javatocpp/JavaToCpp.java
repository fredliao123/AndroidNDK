/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.fred.javatocpp;
import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;


public class JavaToCpp extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        /* Create a TextView and set its content.
         * the text is retrieved by calling a native
         * function.
         */
        int[] a = new int[10];
        for(int i = 0; i < 10 ; i++){
            a[i] = i;
        }
        TextView  tv = new TextView(this);
        //tv.setText( stringFromJNI() );
        //int[] b = IntArrayFromJava(a);
        IntArrayFromJavaElement(a, a.length);
        tv.setText( StringFromJava("hello") +"\n" +IntArrayToString(IntArrayFromJava(a)));
        setContentView(tv);
    }

    public String IntArrayToString(int[] a){
        int length = a.length;
        StringBuffer buffer = new StringBuffer();
        for(int i = 0 ; i < length ; i++){
            buffer.append(a[i]);
        }
        return new String(buffer);
    }

    public native String  stringFromJNI();
    public native String StringFromJava(String str);
    public native int[] IntArrayFromJava(int[] a);
    public native void IntArrayFromJavaElement(int[] a, int length);
    static {
        System.loadLibrary("java-to-cpp");
    }
}
