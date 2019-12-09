package com.example.pms_lab2;

import android.app.Activity;
import android.content.Intent;
import android.view.View;

/**
 * @author Andrey Yablonsky on 20.11.2019
 */
class StartActivityClickListener implements View.OnClickListener {

    private final Activity startContext;
    private final Class<? extends Activity> destActivityClass;

    StartActivityClickListener(Activity startContext, Class<? extends Activity> destActivityClass) {
        this.startContext = startContext;
        this.destActivityClass = destActivityClass;
    }

    @Override
    public void onClick(View v) {
        Intent intent = new Intent(startContext, destActivityClass);
        startContext.startActivity(intent);
        startContext.finish();
    }
}
