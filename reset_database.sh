DATABASE_URL="--dbname=codebreaker"
psql $DATABASE_URL -c "DROP TABLE results; DROP TABLE users; DROP TABLE settings;"
psql $DATABASE_URL -f table_setup.sql
