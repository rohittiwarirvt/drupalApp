<?php
Use Aws\SecretsManager;

function get_aws_secret_manager_connection() {
  libraries_load('aws-sdk-php');
  $endpoint = variable_get('ur_d7_aws_secret_manager_aws_secret');
  $region  = variable_get('ur_d7_aws_secret_manager_aws_region');
  $test = new SecretsManager($endpoint, $region);
}
