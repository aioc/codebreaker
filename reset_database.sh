psql $DATABASE_URL -d "codebreaker" -c "DROP TABLE results; DROP TABLE users; DROP TABLE settings;"
psql $DATABASE_URL -d "codebreaker" -f table_setup.sql
