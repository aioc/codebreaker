CREATE TABLE users (
	username VARCHAR UNIQUE,
	password VARCHAR,
	admin BOOLEAN,
  visible BOOLEAN,
	PRIMARY KEY (username)
);

CREATE TABLE results (
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

INSERT INTO users(username, password, visible, admin) VALUES ('tutors', 'simmeringaioli', FALSE, TRUE);

INSERT INTO users(username, password, visible, admin) VALUES ('jaz', 'blah', FALSE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('jerry', 'monash3150', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('1021839', '1021839A', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('samtoday', 'plaintestSAM', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('pony_joe1', 'Angusage14', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('mzhao', 'info1234', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('jl58261', 'carrots21', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('i_am_sb', 'iamsherlocked', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('j_p_smith', '64scOne\', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('jamesburgess', 'Aelianeditor', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('jojo197', 'Scorpion&', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('hfc', '311190c3', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('println_hi_', '07ff08be', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('mckinleykeys', '393b9dbc', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('jinwoopark0', 'f1b9c7c5', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('super_aiderton', '22scOne\', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('blendersleuth', 'walnut88', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('ivansolo2', 'acd64b16', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('technocoder', 'fab30f42', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('maayan', 'b7e3cd13', TRUE, FALSE);
INSERT INTO users(username, password, visible, admin) VALUES ('spyofthemonth', '6461c132', TRUE, FALSE);

CREATE TABLE settings (
	name VARCHAR UNIQUE,
	value INT
);

INSERT INTO settings(name, value) VALUES ('submissions_allowed', 0);
INSERT INTO settings(name, value) VALUES ('scoreboard_freeze_id', 100000000);
