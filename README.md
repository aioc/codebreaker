# codebreaker18
_by jimjam, and original design and server by dxsmiley_

This is a new implementation of codebreaker to replace the current setup, a modified version of CMS. It is much more lightweight, generally faster to setup, administer and judge, and easier to use for students and tutors.

## Setup

codebreaker18 is designed to run on a basic AWS E2 instance, but can also be run on a local computer, and connected to via LAN.

The following instructions will assume you are running on the AWS free tier Ubuntu 18.04 offering, but should not be hard to adapt to whatever you are trying to run this on (with a little Google-Fu).

You can clone this repo anywhwere.

### Install required dependencies

```
sudo apt-get update && sudo apt-get install $(cat yum-requirements.txt)
```

### Python3 dependencies

This server was developed using Python 3.6, so install that for the least hassle. It will probably work with Python 3.anything though.

Install the python dependencies (inside a virtualenv, ideally):

```
virtualenv cb -p `which python3`
source cb/bin/activate
pip3 install -r requirements.txt
# If you get weird errors you may want to revisit the requirements
# listed here, which weren't frozen :(
#
# Look up the packages on PyPi and try downgrading to get it to work
```

### Postgres Database

codebreaker18 expects a Postgres database named `codebreaker`.
The easiest way is to set up a local postgres server:

```
sudo service postgresql start
```

Next, we will set up the database with the table schemas defined in `table_setup.sql`.
This script can also give permissions for the user that codebreaker18 will run as.
Use `who` to find the user you are logged in as and change the variable `run_user` in
the `table_setup.sql` script to it (or whoever you intend to run codebraker18 as).
Then, simply run the `./setup.sh` script.

```
# Assume run user is "ubuntu" which is fine for Ubunutu AMIs
sudo -u postgres ./setup.sh
```

If you get permission issues, it may because the postgres user does not have permission to access wherever you cloned the codebreaker repo. This can be fixed with, for example
```
chmod o+x /home/ubuntu
chmod o+rx /home/ubuntu/codebreaker
```
This gives permission for other uses to access ubuntu's home directory, so only do this if you are running on a dedicated codebreaker-only server without other users. 

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


## Problems

You can check past contests to see the format expected by codebreaker18.
`src/problems.py` is where you configure which (relative) directory codebreaker18 should look for to find problems.

Interactive tasks should have 'graders' and/or 'headers' defined in problems.json.
Each of these fields are a list of files.
For interactive tasks, students do not submit a correct output, but otherwise they are judged the same as any other task.

## Contest admin

### Adding users

The script `reset.sql` that confusingly does two things:

* Resets the database, deleting all user and submission data.
* Adds users to the database.

You can additional `INSERT` commands to add extra contestants to the table.
Make sure to set visible = TRUE and admin = FALSE, so that the contestants are visible on the scoreboard and do not have admin rights.

Warning: Do not commit student passwords to the git repo.

Once done, you can run it as:

```
# Make sure you have DB access (remember what we said before about the "ubuntu" default user?)
psql -f reset.sql codebreaker
```

### Starting/ending the contest

Initially, codebreaker is configured to allow contestants to log in and see what the problems are, but not the code they are trying to break. To start the contest, you will need to update the settings table in the database, then restart `src/server.py`.

The setting has 4 modes:
```
0 = No access. Contestants can't see code and cannot submit.
1 = Contest mode. Contestants can now see and submit problems
2 = No more submissions. Contestants can no longer submit (but can still see problems).
3 = Contestants can now submit post-contest. The scoreboard is frozen.
```

You can update the database directly to change the settings, or you can use the provided script in `scripts/`.
