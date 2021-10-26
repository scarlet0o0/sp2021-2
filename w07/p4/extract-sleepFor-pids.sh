#!/bin/bash

ps -ef | awk '$8 == "./sleepFor" {print $2}' > pids.txt
