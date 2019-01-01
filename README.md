# codebreaker18
by jimjam, and original design and server by dxsmiley

This is a new implementation of codebreaker to replace the current setup, a modified version of CMS. It is much more lightweight, generally faster to setup, administer and judge, and easier to use for students and tutors.

## Setup (tested on E2 Free-tier server)

codebreaker18 is designed to run on a basic AWS E2 instance, but can also be run on a local computer, and connected to via LAN.

On E2, run
```
sudo yum -y install $(cat yum-requirements.txt)
```
to install all dependencies.

### Python 3.6 setup (tested on Ubuntu on Windows)
This server is written in Python 3.6. You may need do some poking around to get Python 3.6 to work on your machine.

Install the python dependencies (inside a virtualenv, ideally) using `sudo pip3 install -r requirements.txt`.

### nginx

nginx is only used as a reverse proxy - feel free to use any other similar service. 

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

### postgresql

codebreaker18 expects a Postgres database named `codebreaker` and a local postgres server, connecting using username `codebreaker` and no password (this generally makes it a good idea to ban all external connections).

To create this, start by running postgresql with
```
sudo service postgresql start
```

Run `sudo -u postgres psql` to enter psql

Within psql:
```
CREATE DATABASE codebreaker;
CREATE USER codebreaker;
```
Depending on how you set up your postgresql instance, you may need to go mucking about in the configuration. Of note,
you probably want to look at `setup.sh` and `src/database.py`.

## Starting the server
Simply run the start script: `./start.sh`.
