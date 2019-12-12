-- WARNING: THIS SCRIPT WILL DELETE ALL USER DATA! DO NOT RUN DURING A CODEBREAKER CONTEST
TRUNCATE users CASCADE;
TRUNCATE results CASCADE;

INSERT INTO users(username, password, visible, admin) VALUES ('tutors', 'simmeringaioli', FALSE, TRUE);

INSERT INTO users(username, password, visible, admin) VALUES ('testuser', 'testpass', TRUE, FALSE);
