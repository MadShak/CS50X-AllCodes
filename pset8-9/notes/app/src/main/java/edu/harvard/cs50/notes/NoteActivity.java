package edu.harvard.cs50.notes;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.EditText;

public class NoteActivity extends AppCompatActivity {
    private EditText editTitle;
    private EditText editText;
    private AlertDialog.Builder dialogBuilder;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_note);

        dialogBuilder = new AlertDialog.Builder(this);

        Intent intent = getIntent();
        editTitle = findViewById(R.id.note_edit_title);
        editText = findViewById(R.id.note_edit_text);
        editTitle.setText(intent.getStringExtra("title"));
        editText.setText(intent.getStringExtra("content"));
    }

    @Override
    protected void onPause() {
        super.onPause();
        Intent intent = getIntent();

        int id = intent.getIntExtra("id", 0);
        String title = intent.getStringExtra("title");
        String content = intent.getStringExtra("content");

        if (!editTitle.getText().toString().isEmpty())
            title = editTitle.getText().toString();
        if (!editText.getText().toString().isEmpty())
            content = editText.getText().toString();

        MainActivity.database.noteDao().update(title, content, id);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.action_bar, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem menuItem) {
        if (menuItem.getItemId() == R.id.delete_button) {
            dialogBuilder.setMessage("Are you sure?")
                .setPositiveButton("Yep", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Intent intent = getIntent();
                        int id = intent.getIntExtra("id", 0);
                        MainActivity.database.noteDao().delete(id);
                        Log.i("cs50", "The note has been deleted..");
                        finish();
                    }
                }).setNegativeButton("Nope", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.cancel();
                    }
            });

            AlertDialog alert = dialogBuilder.create();
            alert.show();
            return true;
        }
        return false;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }
}
