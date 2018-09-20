#!/bin/sh

mkdir -p temp/
psql -d codebreaker -f table_setup.sql 2> /dev/null

