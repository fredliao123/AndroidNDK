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
package com.example.fred.javatocpp2;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;


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
        int[] a = new int[100];
        for(int i = 0; i < 100 ; i++){
            a[i] = i;
        }
        TextView  tv = new TextView(this);
        //tv.setText( stringFromJNI() );
        tv.setText( StringFromJava("hello") );//+ "\n" + IntArrayFromJava(a));
        setContentView(tv);
    }

    public native String  stringFromJNI();
    public native String StringFromJava(String str);
    public native String IntArrayFromJava(int[] a);
    static {
        System.loadLibrary("java-to-cpp");
    }
}
