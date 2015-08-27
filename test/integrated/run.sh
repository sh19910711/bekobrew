CDUP=`git rev-parse --show-cdup`
ROOTDIR=`cd ${CDUP:-.} && pwd`
cd ${ROOTDIR}/test/integrated
prove --exec=/bin/sh ./