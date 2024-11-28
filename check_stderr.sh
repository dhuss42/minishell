#!/bin/bash

check_stderr() {
  if { "$@" 2>&1 >&3 3>&- | grep '^' >&2; } 3>&1; then
    echo "There was some output on stderr"
    return 1
  else
    echo "No stderr output detected"
    return 0
  fi
}

# Run the command you want to check
"$@"

# Check for stderr
check_stderr "$@"
