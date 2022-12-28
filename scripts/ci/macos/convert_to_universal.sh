#!/usr/bin/env bash
UNAME=$(uname)
echo "${0} was runned on ${UNAME}\n\n
"
if [ "$(uname)" = Linux ]; then
echo "Linux"
alias brew=/home/linuxbrew/.linuxbrew/bin/brew
else
echo "Non Linux"
fi
####
makeUniversal() {
mimetype=$(file -b --mime-type $1)
noPrefixPath="${1#arm64/}"
if [ "${mimetype}" = "application/x-mach-binary" ]; then
    lipo x86_64/${noPrefixPath} arm64/${noPrefixPath} -create universal/${noPrefixPath}
elif [ "${mimetype}" = "inode/directory" ]; then
    mkdir -p universal/${noPrefixPath}
else
    cp arm64/${noPrefixPath} universal/${noPrefixPath}
fi
}
####

FILES=$(find arm64)

for i in $FILES
do 
makeUniversal $i
done
