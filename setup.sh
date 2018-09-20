#!/bin/sh

mkdir -p temp/
psql -U codebreaker -d codebreaker -f table_setup.sql 2> /dev/null

