#!/usr/bin/env bash
fileWalker(){
    for f in $1/*; do
        if [[ -d "$f" ]]
        	then fileWalker $f
        elif [[ ! -e $f && -L $f && `stat --format=%Y $f` -le $(( `date +%s` - 604800 )) ]]
        	then echo "$f"
        fi
    done
}
fileWalker $1