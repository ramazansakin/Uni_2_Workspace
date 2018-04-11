ifconfig eth0 | grep 'inet addr:' | cut -d: -f2 | awk '{ print $1}'
ifconfig eth0 | grep 'inet addr:' | cut -d: -f2
