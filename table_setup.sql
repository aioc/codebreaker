CREATE TABLE IF NOT EXISTS users (
	username VARCHAR UNIQUE,
	password VARCHAR,
	admin BOOLEAN,
  visible BOOLEAN,
	PRIMARY KEY (username)
);

CREATE TABLE IF NOT EXISTS results (
	id SERIAL UNIQUE,
	owner VARCHAR,
	score INT,
	status VARCHAR,
	proposed_input VARCHAR,
	broken_output VARCHAR,
	correct_output VARCHAR,
	problem VARCHAR,
	complete BOOLEAN,
	FOREIGN KEY (owner) REFERENCES users(username)
);

IF NOT EXISTS (SELECT 1 FROM pg_catalog.pg_tables WHERE tablename = 'settings') THEN
    CREATE TABLE settings (
	   name VARCHAR UNIQUE,
	   value INT
    );
    INSERT INTO settings(name, value) VALUES ('submissions_allowed', 0);
    INSERT INTO settings(name, value) VALUES ('scoreboard_freeze_id', 100000000);
END IF;
