#!/bin/sh

rmddir="/openrmd"
checkdir="/checkproc"
ip=
db_ip=
db_user=
db_pwd=
db_name=

function configure {
	# network interface
	echo -e "network interface [eth0]: \c"
	read interface
	if [ "$interface" == "" ] ; then
		interface="eth0"
	fi

	# mysql database
	echo -e "database IP [127.0.0.1]: \c"
	read db_ip
	if [ "$db_ip" == "" ] ; then
		db_ip="127.0.0.1"
	fi

	echo -e "database user [vfs]: \c"
	read db_user
	if [ "$db_user" == "" ] ; then
		db_user="vfs"
	fi

	echo -e "database password [vfman706]: \c"
	read db_pwd
	if [ "$db_pwd" == "" ] ; then
		db_pwd="vfman706"
	fi

	echo -e "database name [zcgcdb]: \c"
	read db_name
	if [ "$db_name" == "" ] ; then
		db_name="zcgcdb"
	fi

	ip=`ifconfig $interface | grep 'inet addr' | awk '{print $2}' | \
		awk -F: '{printf $2}'`
	echo "------------------------------"
	echo "interface    : $ip"
	echo "database IP  : $db_ip"
	echo "database user: $db_user"
	echo "database pwd : $db_pwd"
	echo "database name: $db_name"
	echo "------------------------------"

	echo -e "The above information is correct [y/n]: \c"
	read c
	if [ "$c" != "y" ] ; then
		echo "Installation was abandoned!"
		exit 1
	fi
}

function install {
	if [ -d ${rmddir} ] ; then
		rm -rf $rmddir
	fi

	tar -xf openrmd-zc.tar.bz2 -C /

	sed -i '/^interface=/ c interface='$interface $rmddir/rmd.conf
	sed -i '/^db_mysql_ip=/ c db_mysql_ip='$db_ip $rmddir/rmd.conf
	sed -i '/^db_mysql_user=/ c db_mysql_user='$db_user $rmddir/rmd.conf
	sed -i '/^db_mysql_pwd=/ c db_mysql_pwd='$db_pwd $rmddir/rmd.conf
	sed -i '/^db_mysql=/ c db_mysql='$db_name $rmddir/rmd.conf
}

function autorun {
	if [ ! -d ${checkdir} ] ; then
		tar -xf checkproc.tar.bz2 -C /
	fi

	n=`cat ${checkdir}/checkproc.lst | grep '^/openrmd/openrmd$' | wc -l`
	if [ $n -eq 0 ] ; then
		sed -i '2 a /openrmd/openrmd' ${checkdir}/checkproc.lst
	fi

	# If checkproc not running, run it.
	pcount=`ps -eo comm | grep "^checkproc$" | wc -l`
	if [ $pcount -lt 1 ]; then
		pushd .
		cd $checkdir
		nohup ./checkproc 10 &
		popd
	fi

	# If checkproc not in boot script, add it.
	n=`cat /etc/init.d/boot.local | grep '^/checkproc/checkproc' | wc -l`
	if [ $n -eq 0 ] ; then
		echo "/checkproc/checkproc 10 &" >> /etc/init.d/boot.local
	fi
}

configure
install
autorun

echo 'Installation successful!'
