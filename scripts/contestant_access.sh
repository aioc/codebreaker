psql -d codebreaker -c "UPDATE settings SET value = $1 WHERE name = 'contestant_access';"
