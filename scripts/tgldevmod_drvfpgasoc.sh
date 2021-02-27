#!/usr/bin/env bash

readonly -- driver_sys_path='/sys/module/fpgasoc/parameters/fpgasoc_isdbg'
readonly -- devmode_now="$(cat "${driver_sys_path}")"

if [[ "${devmode_now}" == 'N' ]]
then
	echo -n '1' > "${driver_sys_path}"
	echo "Switched mode from '${devmode_now}' to 'Y'"

elif [[ "${devmode_now}" == 'Y' ]]
then
	echo -n '0' > "${driver_sys_path}"
	echo "Switched mode from '${devmode_now}' to 'N'"

else
	echo 'DrvFpgasoc is not loaded.' >&2
fi

