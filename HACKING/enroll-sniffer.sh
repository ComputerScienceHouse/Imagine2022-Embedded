#!/bin/bash

# PARSING SHIT (holy hell)
function help () {
    echo "
Options:
    -u|--unenroll
    -m|--mac
    -y|--latitude|--lat
    -x|--longitude|--lon
    -p|--password|--pass"
}

# https://gis.stackexchange.com/questions/11626/does-y-mean-latitude-and-x-mean-longitude-in-every-gis-software

# More safety, by turning some bugs into errors.
# Without `errexit` you don’t need ! and can replace
# ${PIPESTATUS[0]} with a simple $?, but I prefer safety.
set -o errexit -o pipefail -o noclobber -o nounset

# -allow a command to fail with !’s side effect on errexit
# -use return value from ${PIPESTATUS[0]}, because ! hosed $?
! getopt --test > /dev/null
if [[ ${PIPESTATUS[0]} -ne 4 ]]; then
    echo 'I’m sorry, `getopt --test` failed in this environment.'
    exit 1
fi

# option --output/-o requires 1 argument
LONGOPTS=unenroll,latitude:,lat:,longitude:,lon:,pass:,mac:,password:
OPTIONS=uy:x:p:m:

# -regarding ! and PIPESTATUS see above
# -temporarily store output to be able to check for errors
# -activate quoting/enhanced mode (e.g. by writing out “--options”)
# -pass arguments only via   -- "$@"   to separate them correctly
! PARSED=$(getopt --options=$OPTIONS --longoptions=$LONGOPTS --name "$0" -- "$@")
if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
    # e.g. return value is 1
    #  then getopt has complained about wrong arguments to stdout
    exit 2
fi
# read getopt’s output this way to handle the quoting right:
eval set -- "$PARSED"

UNENROLL=n
MAC=
LATITUDE=
LONGITUDE=
PASSWORD=
# now enjoy the options in order and nicely split until we see --
while true; do
    case "$1" in
        -u|--unenroll)
            UNENROLL='true'
            shift
            ;;
        -m|--mac)
            MAC=$2
            shift 2
            ;;
        -y|--latitude|--lat)
            LATITUDE=$2
            shift 2
            ;;
        -x|--longitude|--lon)
            LONGITUDE=$2
            shift 2
            ;;
        -p|--password|--pass)
            PASSWORD=$2
            shift 2
            ;;
        --)
            shift
            break
            ;;
        *)
            echo $1
            echo "Programming error"
            exit 3
            ;;
    esac
done

# if [[ -z "$PASSWORD" || -z "$MAC" || -z "$LATITUDE" || -z "$LONGITUDE" ]]; then
if [[ -z "$PASSWORD" ]]; then
    echo "Missing password!"
    help
    exit 1
fi

if [[ -z "$MAC" ]]; then
    echo "Missing MAC!"
    help
    exit 1
fi

if [[ -z "$LATITUDE" ]] && [[ -z "$UNENROLL" ]]; then
    echo "Missing latitude!"
    help
    exit 1
fi

if [[ -z "$LONGITUDE" ]] && [[ -z "$UNENROLL" ]]; then
    echo "Missing longitude!"
    help
    exit 1
fi
# fi

if [[ "$UNENROLL" == 'true' ]]; then
    echo "Unenrolling sniffer..."
    curl -X POST -H "Authorization: Bearer $PASSWORD" 'https://imagine2022-backend.csh.rit.edu/remove/esp?id='$MAC
    exit 0
fi

echo "Enrolling sniffer..."
curl -X POST -H "Authorization: Bearer $PASSWORD" 'https://imagine2022-backend.csh.rit.edu/esp?id='$MAC'&lat='$LATITUDE'&lon='$LONGITUDE

