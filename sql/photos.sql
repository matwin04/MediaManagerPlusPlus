CREATE TABLE IF NOT EXISTS photos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    file_path TEXT NOT NULL,
    camera_model TEXT NOT NULL,
    date_taken TEXT NOT NULL
);
