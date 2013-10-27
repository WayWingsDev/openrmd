#!/bin/sh

thirdlib=/programs/thirdlib
driver_path=/programs/openrmd/driver
finc_so_path=/programs/finc

# system
ln -sv /usr/lib/libcrypto.so.0.9.8
ln -sv /usr/lib/libssl.so.0.9.8
ln -sv /usr/lib/libmysqlclient.so.16

# hik
if [ $# -eq 1 -a "$1" = "arch_x64" ] ; then
	# arch_x64
	for file in ${thirdlib}/hik/lib64/{libStreamTransClient.so,libSystemTransform.so,libhcnetsdk.so,libhpr.so,libMPCtrl.so,libPlayCtrl.so}; do \
		ln -sv $file
	done
else
	# arch_x32
	for file in ${thirdlib}/hik/lib/{libStreamTransClient.so,libSystemTransform.so,libhcnetsdk.so,libhpr.so,libMPCtrl.so,libPlayCtrl.so}; do \
		ln -sv $file
	done
fi

# dahua
for file in ${thirdlib}/dahua/lib/{libdhconfig.so,libdhdvr.so,libdhnetsdk.so,libdhplay.so,libstdc++.so.5}; do \
	ln -sv $file
done

# zxw
for file in ${thirdlib}/zxw/{libmodel.so,librtspApp.so}; do \
	ln -sv $file
done

# hbang
ln -sv ${thirdlib}/hbang/libhbnetsdk.so

# HSN
ln -sv ${thirdlib}/hsn/libhsnnetsdk.so

# Yaan
ln -sv ${thirdlib}/yaan/libynnet.so

# Yaan DVR
ln -sv ${thirdlib}/yaandvr/libyndvr.so

# librmd_*
except_dir="specialipc|proxy|rtspcam|mynvr"
for file in `ls -F \${driver_path} | grep -Ev \${except_dir} | grep /`; do \
	driver_file=${driver_path}/${file}librmd_`basename $file`.so
	ln -sv ${driver_file}
done
ln -sv ${driver_path}/specialipc/libspecialipc.so

# librtsp.so librtp.so
ln -sv ${finc_so_path}/librtsp.so
ln -sv ${finc_so_path}/librtp.so

# sip
ln -sv ${finc_so_path}/sip/libsipua.so

# brainaire
if [ $# -eq 1 -a "$1" = "arch_x64" ] ; then
	# arch_x64
	ln -sv ${thirdlib}/brainaire/lib/suse64bit/libNVRCLIENTAPI.so
else
	# arch_x32
	ln -sv ${thirdlib}/brainaire/lib/trustix32bit/libNVRCLIENTAPI.so
fi

# aeronvr
ln -sv ${thirdlib}/aeronvr/libaeronvr.so
