package edu.harvard.cs50.fiftygram;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.Manifest;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.content.Intent;
import android.graphics.Bitmap;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.os.ParcelFileDescriptor;
import android.provider.MediaStore;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import com.bumptech.glide.Glide;
import com.bumptech.glide.load.Transformation;
import com.bumptech.glide.request.RequestOptions;
import java.io.FileDescriptor;
import java.io.IOException;
import jp.wasabeef.glide.transformations.gpu.SepiaFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.SketchFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.ToonFilterTransformation;

public class MainActivity extends AppCompatActivity implements ActivityCompat.OnRequestPermissionsResultCallback {

    private Bitmap current;
    private Transformation<Bitmap> currentFilter;
    private AlertDialog.Builder dialogBuilder;
    private ImageView imageView;
    private Bitmap original;
    private Button sketch;
    private Button sepia;
    private Button toon;
    private Button save;
    private Button choose;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        dialogBuilder = new AlertDialog.Builder(this);

        imageView = findViewById(R.id.image_view);

        toon = findViewById(R.id.toon_button);
        sketch = findViewById(R.id.sketch_button);
        choose = findViewById(R.id.button_choose);
        sepia = findViewById(R.id.sepia_button);
        save = findViewById(R.id.save_button);

        requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
    }

    public void savePhoto(View view) {
        if (imageView.getDrawable() != null) {
            current = ((BitmapDrawable) imageView.getDrawable()).getBitmap();

            final String filterName = currentFilter.getClass().getCanonicalName().split("FilterTransformation")[0];

            MediaStore.Images.Media.insertImage(getContentResolver(), current, original.getConfig().name(), "");

            Log.i("cs50", "The image " + original.getConfig().name() + " filtered with " + filterName + " has been saved to the memory" );

            dialogBuilder.setMessage("The image has been saved successfully.").setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    finish();
                }
            });

            AlertDialog alert = dialogBuilder.create();
            alert.show();
        } else {
            Log.e("cs50", "There is no image selected");
        }
    }

    public void apply(Transformation<Bitmap> filter) {
        if (original != null) {
            Glide
                .with(this)
                .load(original)
                .apply(RequestOptions.bitmapTransform(filter))
                .into(imageView);

            currentFilter = filter;
            save.setVisibility(View.VISIBLE);
        }
    }

    public void applySepia(View view) {
        apply(new SepiaFilterTransformation());
    }

    public void applyToon(View view) {
        apply(new ToonFilterTransformation());
    }

    public void applySketch(View view) {
        apply(new SketchFilterTransformation());
    }

    public void choosePhoto(View view) {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.setType("image/*");
        startActivityForResult(intent, 1);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == Activity.RESULT_OK && data != null) {
            try {
                Uri uri = data.getData();
                ParcelFileDescriptor parcelFileDescriptor =
                        getContentResolver().openFileDescriptor(uri, "r");
                FileDescriptor fileDescriptor = parcelFileDescriptor.getFileDescriptor();
                original = BitmapFactory.decodeFileDescriptor(fileDescriptor);
                parcelFileDescriptor.close();
                imageView.setImageBitmap(original);

                sepia.setVisibility(View.VISIBLE);
                sketch.setVisibility(View.VISIBLE);
                toon.setVisibility(View.VISIBLE);

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }
}
