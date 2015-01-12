#!/bin/bash
cd $WORKSPACE
git clone --recursive https://github.com/starschema/virtdb-proto virtdb-proto
cd virtdb-proto
git config user.name $GITHUB_USER
git config user.email $GITHUB_EMAIL
git config user.password $GITHUB_PASSWORD
VERSION=`npm version patch`
echo $VERSION
git add package.json
if [ $? -ne 0 ]; then echo "Failed to add package.json to patch"; exit 10; fi
git push
if [ $? -ne 0 ]; then echo "Failed to push to repo."; exit 10; fi
