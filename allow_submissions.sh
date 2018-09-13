psql -d codebreaker -c "UPDATE settings SET value = $1 WHERE name = 'submissions_allowed';"
