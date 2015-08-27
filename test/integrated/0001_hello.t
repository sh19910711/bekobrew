source ./helper.sh

test_start "GNU Hello"

cp -r ${SCRIPTDIR}/0001/hello ${TMPDIR}
cd ${TMPDIR}/hello
${ROOTDIR}/build/bekobrew build 1>/dev/null 2>/dev/null

ok
