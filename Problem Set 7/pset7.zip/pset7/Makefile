.PHONY: default permission 

default: permission

permission:
	find . -type d -exec chmod 755 {} \;
	find . -type f -exec chmod 644 {} \;

restart:
	-killall -9 server
	-apache50 stop
	-apache50 start ~/workspace/pset7/public
	-mysql50 restart

mysqli:
	mysql -u `username50` --password=`password50`
