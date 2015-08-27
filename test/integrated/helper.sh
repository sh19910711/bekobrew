TEST=
CDUP=`git rev-parse --show-cdup`
ROOTDIR=`cd ${CDUP:-.} && pwd`
SCRIPTDIR=`dirname $0`
TMPDIR=`mktemp -d`

test_start() {
  TEST=$@
  echo "1..1"
  trap "echo not ok 1 - ${TEST}" ERR
}

ok() {
  echo ok - ${TEST}
}
