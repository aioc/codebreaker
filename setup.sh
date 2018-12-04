#!/bin/sh

mkdir -p temp/
psql -U postgres -d codebreaker -f table_setup.sql 2> /dev/null

