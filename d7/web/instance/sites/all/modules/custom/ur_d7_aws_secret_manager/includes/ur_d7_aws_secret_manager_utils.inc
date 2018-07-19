<?php
Use Aws\SecretsManager\SecretsManagerClient;

function get_aws_secret_manager_connection($form_state) {
  libraries_load('aws-sdk-php');
  $endpoint = variable_get('ur_d7_aws_secret_manager_aws_secret');
  $region  = variable_get('ur_d7_aws_secret_manager_aws_region');

  $migration_options['ur_d7_aws_secret_manager_aws_key'] = variable_get('ur_d7_aws_secret_manager_aws_key');

  $migration_options['ur_d7_aws_secret_manager_aws_secret'] = variable_get('ur_d7_aws_secret_manager_aws_secret');

  $migration_options['ur_d7_aws_secret_manager_aws_region'] = variable_get('ur_d7_aws_secret_manager_aws_region');

  $migration_options['ur_d7_aws_secret_manager_secret_prefix'] = variable_get('ur_d7_aws_secret_manager_secret_prefix');
  $migration_options['ur_d7_aws_secret_manager_secret_enable'] = variable_get('ur_d7_aws_secret_manager_secret_enable');


  $version = 'latest';
  $settings = array('version' => 'latest','endpoint' => $endpoint, 'region' => $region);
  //dsm($settings,"test");
  // will work on this as i get hte aws keys and acces id
  //$test = new SecretsManagerClient($settings);
  //dsm($test->getSecretValue(array('SecretId' => $secretName)));
  _aws_settings_php_file_creation();

  $db_name ="evolent_v1";
  $db_username ="root";
  $db_password = "root";
  $db_host = !empty(getenv("CONTAINER_DB_PORT_3306_TCP_ADDR")) ? getenv("CONTAINER_DB_PORT_3306_TCP_ADDR") : 'localhost';
  $db_port = !empty(getenv("CONTAINER_DB_PORT_3306_TCP_PORT")) ? getenv("CONTAINER_DB_PORT_3306_TCP_PORT"): '3306';

 // response from client secret manager
  $database_options = array(
    'database' => $db_name,
    'username' => $db_username,
    'password' => $db_password,
    'host' => $db_host,
    'port' => $db_port,
    'driver' => 'mysql',
    'prefix' => '',
  );

  Database::addConnectionInfo('aws_secret_database', 'default', $database_options);
  db_set_active("aws_secret_database");


  _set_default_installation($migration_options);

}

function _aws_settings_php_file_creation($options) {
  $db_name ="evolent_v1";
  $db_username ="root";
  $db_password = "root";
  $db_host = getenv("CONTAINER_DB_PORT_3306_TCP_ADDR");
  $db_port = getenv("CONTAINER_DB_PORT_3306_TCP_PORT");
  $string = '
  <?php

    db_set_active("aws_secret_manager");

    $databases["aws_secret_database"]["default"] = array (
         "database" => "'. $options['db_name'] .'",
          "username" => "' . $options['db_username'] . '",
          "password" => "'. $options['db_password'] .'",
          "host" => "' . $options['db_host'] . '",
          "port" => "'. $options['db_port'] .'",
          "driver" => "mysql",
          "prefix" => "",
        ),
      ),
    )';

  file_unmanaged_save_data($string, 'sites/default/site-php/settings-aws.php', FILE_EXISTS_REPLACE);
}


function _set_default_installation($options) {
  module_enable('ur_d7_aws_secret_manager');

  foreach ($options as $key => $value) {
    variable_set($key, $value);
  }

}
