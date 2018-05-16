<?php

$databases = array (
  'default' =>
  array (
    'default' =>
    array (
      'database' => getenv("CONTAINER_DB_ENV_MYSQL_DATABASE"),
      'username' => getenv("CONTAINER_DB_ENV_MYSQL_USER"),
      'password' => getenv("CONTAINER_DB_ENV_MYSQL_PASSWORD"),
      'host' => getenv("CONTAINER_DB_PORT_3306_TCP_ADDR"),
      'port' => getenv("CONTAINER_DB_PORT_3306_TCP_PORT"),
      'driver' => 'mysql',
      'prefix' => '',
    ),
  ),
);

$conf['theme_debug'] = TRUE;
