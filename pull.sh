#!/bin/sh
git checkout master
git pull 
git remote add upstream https://github.com/starschema/virtdb-proto.git
git fetch origin -v
git fetch upstream -v
git merge upstream/master
git status
