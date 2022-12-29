#!/usr/bin/env bash
UNAME=$(uname)
PREFIX=${1}
echo -e "${0} was runned on ${UNAME}\n\n"
if [ "$(uname)" = "Darwin" ]; then
echo "Cache location $(brew --cache)"
ls $PREFIX
else
echo "This system is not MacOS"
fi
####
makeUniversal() {    
mimetype=$(file -b --mime-type $1)
noPrefixPath="${1#arm64/}"
#echo -e "==> Copying file ${1}\n   as ${mimetype}"
if [ "${mimetype}" = "application/x-mach-binary" ]; then
    lipo "x86_64/${noPrefixPath}" "arm64/${noPrefixPath}" -create -output "universal/${noPrefixPath}"
    echo "==> Mach-O binary merged: ${noPrefixPath}"
else
    cp "arm64/${noPrefixPath}" "universal/${noPrefixPath}"
fi
}
####

FILES=$(find arm64)

echo "Creating directory structure"
for i in $FILES
do
mimetype=$(file -b --mime-type $1)
noPrefixPath="${1#arm64/}"
if [ "${mimetype}" = "inode/directory" ]; then
    mkdir -vp "universal/${noPrefixPath}"
fi
done

for i in $FILES
do 
makeUniversal $i
done
