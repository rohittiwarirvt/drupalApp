# Project Title

Drupal App to Create Contacts 

## Getting Started

This project is an attempt to create Contacts using Form Api and Simple database operations
I had planned to make this project a multiple ways to achieve the same functionality 
  1. **Version 1** (Done)
      * Create Contacts as simple CRUD operation using Table for Contacts and Form API for Create Update Delete operation
      * Have used Menu hooks, Db queries, hook_install and made it in drupal version 7
  2. **Version 2** (Done)
      * Create Contacts as an entity and have corresponding bundles (Leads, Official, etc)
      *  Use entity_info, Default Entity Controller and use fields api to let user add new fields or code one for then as started
     * Can use extra fields for some of the base table entries so that they could act as or interface with field api
      * to be made in Drupal 7
  3. **Version 3** (In Progress)
      * Similar to Version 1 , but to be done in drupal 8 (using controllers, menu.links, routes, permission.yrm, schema etc)
  4. **Version 4** ( To be done)
     * Similar to Version 2, but to be again done in drupal 8 (useing, entity api, and related context)
    
All the above things are to be dokerized and integrated with CI so that applicatoin can be deployed and changed as per your needs on any platform.

The project Has 3 services
1. Drupal runs on port 8989 so u can use http://localhost:8989 to connect to application
2. Phpmyadmin run on port 8686 u can use http://localhost:8906 to connect ot phpmyadmin and browser throug the tables
3. mysql runs on port 8906 u can use `mysql -h 0.0.0.0 -P 8906 -u root -p` root to connect the db
    

### Prerequisites
 ## Docker 
What is docker? 
[Answer](https://www.docker.com/what-docker)
Docker is a computer program that performs operating-system-level virtualization also known as containerization. It is developed by Docker, Inc. [Wikipedia](https://en.wikipedia.org/wiki/Docker_(software))

Installing docker 
[Docker install](https://docs.docker.com/install/)

Please follow the steps to install docker



### Installing

After you have successfully installed docker Please follow the steps to deploy app on local

Clone the repo
```
git clone git@github.com:rohittiwarirvt/drupalApp.git
```
Change to root directory where docker-compose is present
```
cd drupalApp/d7/
```
Make data directory where our volume for db will be mounted and give it write permission as the docker perconal-server will be used to mount on host system
```
sudo mkdir -p db/data/
sudo chmod -R 777 db/data/
```

Docker up the microservices
```
docker-compose up 
```

After this the console will up the images and then will install the evolent profile which enable the Version one of the development

```
rohit@rohit-laptop /media/data4/projects/drupal/RA/scratchpad/drupalApp/d7 (master=) $ docker-compose up

WARNING: The Docker Engine you're using is running in swarm mode.

Compose does not use swarm mode to deploy services to multiple nodes in a swarm. All containers will be scheduled on the current node.

To deploy your application across the swarm, use `docker stack deploy`.

Recreating d7_db_1 ... 
Recreating d7_db_1
WARNING: Service "db" is using volume "/var/lib/mysql" from the previous container. Host mapping "/media/webonise/data4/projects/drupal/RA/scratchRecreating d7_db_1 ... done
Recreating phpmyadmin_evolent ... 
Recreating d7_web_1 ... 
Recreating phpmyadmin_evolent
Recreating d7_web_1 ... done
Attaching to d7_db_1, phpmyadmin_evolent, d7_web_1
db_1          | 2018-05-21T05:37:02.326139Z 0 [Warning] 'NO_ZERO_DATE', 'NO_ZERO_IN_DATE' and 'ERROR_FOR_DIVISION_BY_ZERO' sql modes should be used with strict mode. They will be merged with strict mode in a future release.
db_1          | 2018-05-21T05:37:02.822711Z 0 [Warning] 'NO_AUTO_CREATE_USER' sql mode was not set.
db_1          | 2018-05-21T05:37:02.904323Z 0 [Note] mysqld (mysqld 5.7.19-17) starting as process 1 ...
db_1          | 2018-05-21T05:37:03.470240Z 0 [Warning] InnoDB: Using innodb_file_format is deprecated and the parameter may be removed in future releases. See http://dev.mysql.com/doc/refman/5.7/en/innodb-file-format.html
db_1          | 2018-05-21T05:37:03.609387Z 0 [Note] InnoDB: PUNCH HOLE support available
db_1          | 2018-05-21T05:37:03.609413Z 0 [Note] InnoDB: Mutexes and rw_locks use GCC atomic builtins
db_1          | 2018-05-21T05:37:03.609418Z 0 [Note] InnoDB: Uses event mutexes
db_1          | 2018-05-21T05:37:03.609421Z 0 [Note] InnoDB: GCC builtin __atomic_thread_fence() is used for memory barrier
db_1          | 2018-05-21T05:37:03.609425Z 0 [Note] InnoDB: Compressed tables use zlib 1.2.8
db_1          | 2018-05-21T05:37:03.609429Z 0 [Note] InnoDB: Using Linux native AIO
db_1          | 2018-05-21T05:37:03.688181Z 0 [Note] InnoDB: Number of pools: 1
db_1          | 2018-05-21T05:37:03.719826Z 0 [Note] InnoDB: Using CPU crc32 instructions
db_1          | 2018-05-21T05:37:03.887532Z 0 [Note] InnoDB: Initializing buffer pool, total size = 512M, instances = 1, chunk size = 128M
db_1          | 2018-05-21T05:37:04.300219Z 0 [Note] InnoDB: Completed initialization of buffer pool
db_1          | 2018-05-21T05:37:04.331152Z 0 [Note] InnoDB: If the mysqld execution user is authorized, page cleaner thread priority can be changed. See the man page of setpriority().
db_1          | 2018-05-21T05:37:05.161303Z 0 [Note] InnoDB: Crash recovery did not find the parallel doublewrite buffer at /var/lib/mysql/xb_doublewrite
db_1          | 2018-05-21T05:37:05.223391Z 0 [Note] InnoDB: Highest supported file format is Barracuda.
db_1          | 2018-05-21T05:37:05.724335Z 0 [Note] InnoDB: Created parallel doublewrite buffer at /var/lib/mysql/xb_doublewrite, size 3932160 bytes
db_1          | 2018-05-21T05:37:07.487303Z 0 [Note] InnoDB: Creating shared tablespace for temporary tables
db_1          | 2018-05-21T05:37:07.487381Z 0 [Note] InnoDB: Setting file './ibtmp1' size to 12 MB. Physically writing the file full; Please wait ...
db_1          | 2018-05-21T05:37:08.076756Z 0 [Note] InnoDB: File './ibtmp1' size is now 12 MB.
db_1          | 2018-05-21T05:37:08.077526Z 0 [Note] InnoDB: 96 redo rollback segment(s) found. 96 redo rollback segment(s) are active.
db_1          | 2018-05-21T05:37:08.077544Z 0 [Note] InnoDB: 32 non-redo rollback segment(s) are active.
db_1          | 2018-05-21T05:37:08.090239Z 0 [Note] InnoDB: Waiting for purge to start
db_1          | 2018-05-21T05:37:08.140335Z 0 [Note] InnoDB: Waiting for purge to start
db_1          | 2018-05-21T05:37:08.190443Z 0 [Note] InnoDB: Waiting for purge to start
db_1          | 2018-05-21T05:37:08.240552Z 0 [Note] InnoDB: Waiting for purge to start
db_1          | 2018-05-21T05:37:08.290683Z 0 [Note] InnoDB: Percona XtraDB (http://www.percona.com) 5.7.19-17 started; log sequence number 16328841
db_1          | 2018-05-21T05:37:08.375485Z 0 [Note] InnoDB: Loading buffer pool(s) from /var/lib/mysql/ib_buffer_pool
db_1          | 2018-05-21T05:37:08.421150Z 0 [Note] Plugin 'FEDERATED' is disabled.
db_1          | 2018-05-21T05:37:10.830894Z 0 [Note] Found ca.pem, server-cert.pem and server-key.pem in data directory. Trying to enable SSL support using them.
db_1          | 2018-05-21T05:37:10.830910Z 0 [Note] Skipping generation of SSL certificates as certificate files are present in data directory.
db_1          | 2018-05-21T05:37:10.832481Z 0 [Warning] CA certificate ca.pem is self signed.
db_1          | 2018-05-21T05:37:10.832543Z 0 [Note] Skipping generation of RSA key pair as key files are present in data directory.
db_1          | 2018-05-21T05:37:11.043834Z 0 [Note] Server hostname (bind-address): '*'; port: 3306
db_1          | 2018-05-21T05:37:11.047839Z 0 [Note] IPv6 is available.
db_1          | 2018-05-21T05:37:11.047871Z 0 [Note]   - '::' resolves to '::';
db_1          | 2018-05-21T05:37:11.047907Z 0 [Note] Server socket created on IP: '::'.
db_1          | 2018-05-21T05:37:12.017429Z 0 [Note] InnoDB: Buffer pool(s) load completed at 180521  5:37:12
db_1          | 2018-05-21T05:37:12.291908Z 0 [Warning] 'user' entry 'root@localhost' ignored in --skip-name-resolve mode.
db_1          | 2018-05-21T05:37:12.291990Z 0 [Warning] 'user' entry 'mysql.session@localhost' ignored in --skip-name-resolve mode.
db_1          | 2018-05-21T05:37:12.292002Z 0 [Warning] 'user' entry 'mysql.sys@localhost' ignored in --skip-name-resolve mode.
db_1          | 2018-05-21T05:37:12.292708Z 0 [Warning] 'db' entry 'performance_schema mysql.session@localhost' ignored in --skip-name-resolve mode.
db_1          | 2018-05-21T05:37:12.292716Z 0 [Warning] 'db' entry 'sys mysql.sys@localhost' ignored in --skip-name-resolve mode.
db_1          | 2018-05-21T05:37:12.293566Z 0 [Warning] 'proxies_priv' entry '@ root@localhost' ignored in --skip-name-resolve mode.
db_1          | 2018-05-21T05:37:13.062091Z 0 [Warning] 'tables_priv' entry 'user mysql.session@localhost' ignored in --skip-name-resolve mode.
db_1          | 2018-05-21T05:37:13.062117Z 0 [Warning] 'tables_priv' entry 'sys_config mysql.sys@localhost' ignored in --skip-name-resolve mode.
db_1          | 2018-05-21T05:37:13.260235Z 0 [Note] Event Scheduler: Loaded 0 events
db_1          | 2018-05-21T05:37:13.260432Z 0 [Note] mysqld: ready for connections.
db_1          | Version: '5.7.19-17'  socket: '/var/run/mysqld/mysqld.sock'  port: 3306  Percona Server (GPL), Release '17', Revision 'e19a6b7b73f'
db_1          | 2018-05-21T05:37:13.260447Z 0 [Note] Executing 'SELECT * FROM INFORMATION_SCHEMA.TABLES;' to get a list of tables using the deprecated partition engine. You may use the startup option '--disable-partition-engine-check' to skip this check. 
db_1          | 2018-05-21T05:37:13.260450Z 0 [Note] Beginning of list of non-natively partitioned tables
db_1          | 2018-05-21T05:37:15.750137Z 0 [Note] End of list of non-natively partitioned tables
phpmyadmin_evolent | 2018-05-21 05:37:18,254 CRIT Supervisor running as root (no user in config file)
phpmyadmin_evolent | 2018-05-21 05:37:18,254 WARN Included extra file "/etc/supervisor.d/nginx.ini" during parsing
phpmyadmin_evolent | 2018-05-21 05:37:18,254 WARN Included extra file "/etc/supervisor.d/php.ini" during parsing
phpmyadmin_evolent | 2018-05-21 05:37:18,376 INFO RPC interface 'supervisor' initialized
phpmyadmin_evolent | 2018-05-21 05:37:18,376 CRIT Server 'unix_http_server' running without any HTTP authentication checking
phpmyadmin_evolent | 2018-05-21 05:37:18,376 INFO supervisord started with pid 1
phpmyadmin_evolent | 2018-05-21 05:37:19,378 INFO spawned: 'php-fpm' with pid 21
phpmyadmin_evolent | 2018-05-21 05:37:19,380 INFO spawned: 'nginx' with pid 22
phpmyadmin_evolent | 2018-05-21 05:37:20,801 INFO success: php-fpm entered RUNNING state, process has stayed up for > than 1 seconds (startsecs)
phpmyadmin_evolent | 2018-05-21 05:37:20,801 INFO success: nginx entered RUNNING state, process has stayed up for > than 1 seconds (startsecs)
web_1         | Executing: mysql --defaults-extra-file=/tmp/drush_WGStNV --database=evolent --host=db --port=3306 --silent  < /tmp/drush_TSH7PB > /dev/null
web_1         | Sites directory /var/www/html/sites/default already exists -            [notice]
web_1         | proceeding.
web_1         | Executing: mysql --defaults-extra-file=/tmp/drush_8TKpLF --database=evolent --host=db --port=3306 --silent  < /tmp/drush_VDXqMi > /dev/null
web_1         | Executing: mysql --defaults-extra-file=/tmp/drush_rg7vNp --database=evolent --host=db --port=3306 --silent  < /tmp/drush_6a1rM2
web_1         | Executing: mysql --defaults-extra-file=/tmp/drush_AlbvR9 --database=evolent --host=db --port=3306 --silent  < /tmp/drush_MiTuPM
web_1         | You are about to DROP all tables in your 'evolent' database. Do you want to continue? (y/n): y
web_1         | Starting Drupal installation. This takes a while. Consider using the        [ok]
web_1         | --notify global option.
web_1         | WD system: user module installed.                                         [info]
web_1         | WD system: user module enabled.                                           [info]
web_1         | WD system: node module installed.                                         [info]
web_1         | WD system: node module enabled.                                           [info]
web_1         | WD system: filter module installed.                                       [info]
web_1         | WD system: filter module enabled.                                         [info]
web_1         | WD system: field_sql_storage module installed.                            [info]
web_1         | WD system: field_sql_storage module enabled.                              [info]
web_1         | WD system: field module installed.                                        [info]
web_1         | WD system: field module enabled.                                          [info]
web_1         | WD system: text module installed.                                         [info]
web_1         | WD system: text module enabled.                                           [info]
web_1         | WD system: admin_menu module installed.                                   [info]
web_1         | WD system: admin_menu module enabled.                                     [info]
web_1         | WD system: block module installed.                                        [info]
web_1         | WD system: block module enabled.                                          [info]
web_1         | WD system: color module installed.                                        [info]
web_1         | WD system: color module enabled.                                          [info]
web_1         | WD system: comment module installed.                                      [info]
web_1         | WD system: comment module enabled.                                        [info]
web_1         | WD system: contextual module installed.                                   [info]
web_1         | WD system: contextual module enabled.                                     [info]
web_1         | WD system: dashboard module installed.                                    [info]
web_1         | WD system: dashboard module enabled.                                      [info]
web_1         | WD system: dblog module installed.                                        [info]
web_1         | WD system: dblog module enabled.                                          [info]
web_1         | WD system: devel module installed.                                        [info]
web_1         | WD system: devel module enabled.                                          [info]
web_1         | WD system: menu module installed.                                         [info]
web_1         | WD system: menu module enabled.                                           [info]
web_1         | WD system: help module installed.                                         [info]
web_1         | WD system: help module enabled.                                           [info]
web_1         | WD system: file module installed.                                         [info]
web_1         | WD system: file module enabled.                                           [info]
web_1         | WD system: image module installed.                                        [info]
web_1         | WD system: image module enabled.                                          [info]
web_1         | WD system: options module installed.                                      [info]
web_1         | WD system: options module enabled.                                        [info]
web_1         | WD system: list module installed.                                         [info]
web_1         | WD system: list module enabled.                                           [info]
web_1         | WD system: number module installed.                                       [info]
web_1         | WD system: number module enabled.                                         [info]
web_1         | WD system: path module installed.                                         [info]
web_1         | WD system: path module enabled.                                           [info]
web_1         | WD system: taxonomy module installed.                                     [info]
web_1         | WD system: taxonomy module enabled.                                       [info]
web_1         | WD system: search module installed.                                       [info]
web_1         | WD system: search module enabled.                                         [info]
web_1         | WD system: shortcut module installed.                                     [info]
web_1         | WD system: shortcut module enabled.                                       [info]
web_1         | WD system: field_ui module installed.                                     [info]
web_1         | WD system: field_ui module enabled.                                       [info]
web_1         | WD system: rdf module installed.                                          [info]
web_1         | WD system: rdf module enabled.                                            [info]
web_1         | WD system: evolent_v1 module installed.                                   [info]
web_1         | WD system: evolent_v1 module enabled.                                     [info]
web_1         | WD system: evolent module installed.                                      [info]
web_1         | WD system: evolent module enabled.                                        [info]
web_1         | WD actions: Action 'Publish comment' added.                             [notice]
web_1         | WD actions: Action 'Unpublish comment' added.                           [notice]
web_1         | WD actions: Action 'Save comment' added.                                [notice]
web_1         | WD actions: Action 'Publish content' added.                             [notice]
web_1         | WD actions: Action 'Unpublish content' added.                           [notice]
web_1         | WD actions: Action 'Make content sticky' added.                         [notice]
web_1         | WD actions: Action 'Make content unsticky' added.                       [notice]
web_1         | WD actions: Action 'Promote content to front page' added.               [notice]
web_1         | WD actions: Action 'Remove content from front page' added.              [notice]
web_1         | WD actions: Action 'Save content' added.                                [notice]
web_1         | WD actions: Action 'Ban IP address of current user' added.              [notice]
web_1         | WD actions: Action 'Block current user' added.                          [notice]
db_1          | 2018-05-21T05:39:23.795547Z 0 [Note] InnoDB: page_cleaner: 1000ms intended loop took 5360ms. The settings might not be optimal. (flushed=201, during the time.)
web_1         | WD system: update module installed.                                       [info]
web_1         | WD system: update module enabled.                                         [info]
web_1         | WD user: Session opened for admin.                                      [notice]
web_1         | WD cron: Cron run completed.                                            [notice]
web_1         | Installation complete.                                                      [ok]
web_1         | Command dispatch complete                                               [notice]
web_1         | AH00558: apache2: Could not reliably determine the server's fully qualified domain name, using 172.26.0.3. Set the 'ServerName' directive globally to suppress this message
web_1         | AH00558: apache2: Could not reliably determine the server's fully qualified domain name, using 172.26.0.3. Set the 'ServerName' directive globally to suppress this message
web_1         | [Mon May 21 05:39:52.051986 2018] [mpm_prefork:notice] [pid 43] AH00163: Apache/2.4.10 (Debian) PHP/7.0.30 configured -- resuming normal operations
web_1         | [Mon May 21 05:39:52.052014 2018] [core:notice] [pid 43] AH00094: Command line: 'apache2 -D FOREGROUND'
```




## Running Application

After successfull installation of application the application can be accesssed at http://localhost:8989/
username - admin
password - admin

1. List contact [list](http://localhost:8989/evolent/v1/contact)
2. Add contact [add](http://localhost:8989/evolent/v1/contact/add)
3. Update contact [edit](http://localhost:8989/evolent/v1/contact/1/edit) supposed 1 is the contact id
4. Delete contact [delete](http://localhost:8989/evolent/v1/contact/1/delete)
5. View Contact [view](http://localhost:8989/evolent/v1/contact/1/view)


## Authors

* **Rohit Tiwari** -  - [rohittiwarirvt](https://github.com/rohittiwarirvt)



## Create issue for any help needed
