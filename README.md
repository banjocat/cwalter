#### In development

# C practice project

Like all my practice projects I setup goals that I try to reach.

## Requirements to build
* cmake
* https://www.libssh.org/

## Goals
* ~~Use cmake~~
* It should actually work
* Create a simple SSH client
* ~~Take an array of ip addresses~~
* Use green threads to parallelize ssh commands
* Send results to channel that returns an array
* Sequential SSH commands should stop on IPs that had previous failures but continue on successful ones
* Output results of every SSH command to console.
* Use .ssh directory for default private keys but allow option to specify
* ~~Have functional tests~~
