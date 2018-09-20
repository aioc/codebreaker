psql -U codebreaker -d codebreaker -c "UPDATE settings SET value = $1 WHERE name = 'contestant_access';"
