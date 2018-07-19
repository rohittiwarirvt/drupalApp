<?php

/**
 * form array
 */

function ur_d7_aws_secret_manager_form($form, &$form_state) {
  $form['ur_d7_aws_secret_manager_aws_key'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('ur_d7_aws_secret_manager_aws_key'),
      '#title' => t('AWS Key '),
      '#size' => 40,
      '#maxlength' => 120,
      '#required' => TRUE,
      '#description' => t('AWS Key'),
    );

  $form['ur_d7_aws_secret_manager_aws_secret'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('ur_d7_aws_secret_manager_aws_secret'),
    '#title' => t('AWS Secret'),
    '#size' => 40,
    '#maxlength' => 120,
    '#required' => TRUE,
    '#description' => t('AWS Secret .'),
  );

  $form['ur_d7_aws_secret_manager_aws_region'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('ur_d7_aws_secret_manager_aws_region'),
      '#title' => t('AWS Region '),
      '#size' => 40,
      '#maxlength' => 120,
      '#required' => TRUE,
      '#description' => t('The region which contains the KMS key(s)'),
    );

  $form['ur_d7_aws_secret_manager_secret_prefix'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('ur_d7_aws_secret_manager_secret_prefix'),
    '#title' => t('Secret Prefix'),
    '#size' => 40,
    '#maxlength' => 120,
    '#description' => t('A string to prefix the key name with. Secret name can contain alphanumeric characters and the characters /_+=,.@-.'),
  );

  $form['ur_d7_aws_secret_manager_secret_enable'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('ur_d7_aws_secret_manager_secret_enable', 0),
    '#title'=> t('Enable Database Switch')
    );
  $form['#submit'][] = 'ur_d7_aws_secret_manager_form_submit';
  return system_settings_form($form);
}

function ur_d7_aws_secret_manager_form_submit($form, $form_state) {
  module_load_include('inc', 'ur_d7_aws_secret_manager', 'includes/ur_d7_aws_secret_manager_utils');
  get_aws_secret_manager_connection($form_state);
}
