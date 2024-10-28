-- Main table to act as an index for media files
CREATE TABLE IF NOT EXISTS main_table (
                                          id INTEGER PRIMARY KEY AUTOINCREMENT,
                                          name TEXT,
                                          type TEXT,
                                          path TEXT,
                                          added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Music-specific table
CREATE TABLE IF NOT EXISTS music (
                                     id INTEGER PRIMARY KEY AUTOINCREMENT,
                                     title TEXT,
                                     artist TEXT,
                                     album TEXT,
                                     genre TEXT,
                                     release_year INTEGER,
                                     path TEXT,
                                     added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Movies-specific table
CREATE TABLE IF NOT EXISTS movies (
                                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                                      title TEXT,
                                      director TEXT,
                                      genre TEXT,
                                      release_year INTEGER,
                                      duration INTEGER, -- Duration in minutes
                                      path TEXT,
                                      added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- TV Shows-specific table
CREATE TABLE IF NOT EXISTS tv (
                                  id INTEGER PRIMARY KEY AUTOINCREMENT,
                                  title TEXT,
                                  season INTEGER,
                                  episode INTEGER,
                                  genre TEXT,
                                  release_year INTEGER,
                                  path TEXT,
                                  added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Photos-specific table
CREATE TABLE IF NOT EXISTS photos (
                                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                                      title TEXT,
                                      resolution TEXT,
                                      format TEXT,
                                      date_taken TEXT,
                                      path TEXT,
                                      added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Videos-specific table
CREATE TABLE IF NOT EXISTS videos (
                                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                                      title TEXT,
                                      format TEXT,
                                      duration INTEGER,
                                      path TEXT,
                                      added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Podcasts-specific table
CREATE TABLE IF NOT EXISTS podcasts (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
                                        title TEXT,
                                        host TEXT,
                                        episode_number INTEGER,
                                        duration INTEGER,
                                        path TEXT,
                                        added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Games-specific table
CREATE TABLE IF NOT EXISTS games (
                                     id INTEGER PRIMARY KEY AUTOINCREMENT,
                                     title TEXT,
                                     platform TEXT,
                                     genre TEXT,
                                     release_year INTEGER,
                                     path TEXT,
                                     added_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);