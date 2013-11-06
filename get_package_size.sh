#!/bin/bash
# get_package_size.sh -- get the size of all packages
# Copyright (c) 2013 liaods <dongsheng.liao@gmail.com>
# 
#cd `dirname $0`
result=./pkg.list
pkgs=`dpkg --list | cut -b 5- | cut -d' ' -f1`
count=`dpkg --list | wc -l`

rm $result 2>/dev/null
touch $result || exit 0
n=0

echo "Getting the size of all packages, please wait ..."
for i in $pkgs; do
	n=`expr $n + 1`
	echo -n -e "\r$n/$count "
	dpkg -s $i >/dev/null 2>&1
	if [ $? -ne 0 ]; then
		continue;
	fi
	size=`dpkg -s $i | grep "Installed-Size:" | cut -d':' -f2`
	echo "$size KB:$i" >> $result
done

cat $result | sort -nr > tmp.log
mv tmp.log $result
echo -e "\n\nTop 20 packages(Please see file $result for more details)"
echo "====================================================================="
cat $result | head -n 20
