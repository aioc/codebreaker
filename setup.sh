#!/bin/sh

mkdir -p temp/
psql -U postgres -f table_setup.sql

