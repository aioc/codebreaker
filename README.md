# codebreaker18
_by jimjam, and original design and server by dxsmiley_

This is a new implementation of codebreaker to replace the current setup, a modified version of CMS. It is much more lightweight, generally faster to setup, administer and judge, and easier to use for students and tutors.

## Setup

codebreaker18 is designed to run on a basic AWS E2 instance, but can also be run on a local computer, and connected to via LAN.

The following instructions will assume you are running on the AWS free tier Ubuntu 18.04 offering, but should not be hard to adapt to whatever you are trying to run this on (with a little Google-Fu).

### Install required dependencies

```
# FIXME: yum-requirements.txt doesn't have all the dependencies needed.
# You'll have to install missing dependencies as you encounter them.
sudo apt-get update && sudo apt-get install $(cat yum-requirements.txt)
```

### Python3 dependencies

This server was developed using Python 3.6, so install that for the least hassle. It will probably work with Python 3.anything though.

Install the python dependencies (inside a virtualenv, ideally):

```
virtualenv cb -p `which python3`
source cb env/bin/activate
pip3 install -r requirements.txt
```

### Postgres Database

codebreaker18 expects a Postgres database named `codebreaker`. Table schemas are defined in `table_setup.sql`.

The easiest way is to set up a local postgres server:

```
sudo service postgresql start
```

Next, do some admin to add the user codebreaker18 will run as to the database, with the appropriate permissions.

Run `sudo -u postgres psql` to enter psql with admin privileges. From within psql, run the following commands (replacing `$USER` as appropriate:
```
# Honestly, it's a bit weird that all this config isn't part of `table_setup.sql`.
# idk create an issue about it or something lol.
CREATE DATABASE codebreaker;
# Alternatively, you can run codebreaker18 as `postgres` and skip
# the rest of this config (you madman).
CREATE USER ${USER};
GRANT CONNECT ON DATABASE codebreaker TO ${USER};
GRANT USAGE ON SCHEMA public TO ${USER};
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO ${USER};
GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO ${USER};
```

Next, go into `src/database.py`/`setup.sh`/`start.sh` and muck about with the configuration so that codebreaker18 can
actually connect to your database. What's there probably will not work OOTB. Particularly, make sure that the main and
worker programs are run as the database user you created, and that they are connecting with the correct username (and
password, if you set one).

Once you're done, go ahead and set up the tables, and poke around in psql to see if it looks about right:

```
./setup.sh
```

### nginx (optional)

nginx is only used as a reverse proxy - feel free to use any other similar service, or none at all.

nginx forwards web requests to `src/server.py`, by default using port 3000.

Suggested configuration (generally, just replace contents of `/etc/nginx/conf.d/` with `server.conf`:
```
server_names_hash_bucket_size 128;

server {
  listen 80;
  listen [::]:80;

  server_name $URL;

  location / {
      proxy_pass http://localhost:3000/;
  }
}
```
replacing $URL with the server url or the local network address.

Run nginx with
```
sudo service nginx start
```

## Starting the server
Finally, run the start script: `./start.sh`.

This also opens a bunch of screens in `tmux` which I personally find annoying.
Feel free to putter about with the script as you please.
