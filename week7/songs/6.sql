SELECT name FROM songs WHERE artist_id IS (SELECT id FROM artists WHERE name IS 'Post Malone');
