package edu.harvard.cs50.notes;

import androidx.room.Dao;
import androidx.room.Query;

import java.util.List;

@Dao
public interface NoteDao {
    @Query("INSERT INTO notes (title, content) VALUES ('New note', '')")
    void create();

    @Query("SELECT * FROM notes")
    List<Note> getAll();

    @Query("INSERT INTO notes (id, title, content) VALUES (:id, :title, :content)")
    void save(int id, String title, String content);

    @Query("UPDATE notes SET title = :title, content = :content WHERE id = :id")
    void update(String title, String content, int id);

    @Query("DELETE FROM notes WHERE id = :id")
    void delete(int id);
}
