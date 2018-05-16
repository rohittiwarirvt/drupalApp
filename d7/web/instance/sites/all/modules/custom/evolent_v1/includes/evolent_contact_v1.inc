<?php


function evolent_add_contact_v1($form, &$form_state, $contact = array()) {
   $form['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#required' => TRUE,
    '#default_value' => isset($contact['first_name']) ? $contact['first_name']: "" ,
    '#description' => 'Please Insert First Name'
  );
  $form['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => isset($contact['last_name']) ? $contact['last_name']: "" ,
    '#required' => TRUE,
    '#description' => 'Please Insert Last Name'
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email '),
    '#default_value' => isset($contact['email']) ? $contact['email']: "" ,
    '#required' => TRUE,
    '#description' => 'Please Insert Email'
  );
  $form['phone_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone Number'),
    '#default_value' => isset($contact['phone_number']) ? $contact['phone_number']: "" ,

    '#required' => TRUE,
    '#description' => 'Please Insert Phone Number'
  );
  $form['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Is Active.'),
    '#default_value' => isset($contact['status']) ? $contact['status']: "" ,
    '#description' => 'Is this to be Published'
  );
  $form['action'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );


  if (isset($contact['cid'])) {

    $form['#submit'][] = 'evolent_edit_contact_v1_submit';
    $form['action']['#value'] = 'Update';

    $form['cid'] = array(
      '#type' => 'value',
      '#value' => $contact['cid']
    );

  }
  return $form;
}

function evolent_add_contact_v1_validate($forms, $form_state) {

}

function evolent_add_contact_v1_submit($form, &$form_state) {
  global $user;
  $transaction = db_transaction();
  try {
    $query = db_insert(CONTACT_V1_TABLE)
        ->fields( array(
          'first_name' => $form_state['values']['first_name'],
          'last_name' =>  $form_state['values']['last_name'],
          'phone_number' =>  $form_state['values']['phone_number'],
          'email'=> $form_state['values']['email'],
          'status' => $form_state['values']['status'],
           'uid' => $user->uid
           ))
        ->execute();


  } catch (Exception $e) {

    $transaction->rollback();
    drupal_set_message(t('contact insert failed. Message @message', array('@message' => $e->getMessage())), 'error');
  }
  $name = $form_state['values']['first_name'] .' ' . $form_state['values']['last_name'];
  drupal_set_message(t('Successfull inserted contact @name', array('@name' => $name)), 'status');
}

function evolent_edit_contact_v1($contact) {
  drupal_set_title(t('<em> Edit </em> @contact Id - @id ', array('@contact' => $contact->first_name . ' ' . $contact->last_name, '@id' => $contact->cid)), PASS_THROUGH);
  return drupal_get_form('evolent_add_contact_v1', (array)$contact);
}


function evolent_edit_contact_v1_submit($form, &$form_state) {
  $fields = array(
      'first_name' => $form_state['values']['first_name'],
      'last_name' =>  $form_state['values']['last_name'],
      'phone_number' =>  $form_state['values']['phone_number'],
      'email'=> $form_state['values']['email'],
      'status' => $form_state['values']['status'],
       );
  $cid = $form_state['values']['cid'];
  try {
    $count = db_update(CONTACT_V1_TABLE)
             -> fields($fields)
             ->condition('cid', $cid)
             ->execute();
   } catch( Exceptin $e) {
     drupal_set_message(t('contact update failed. Message @message', array('@message' => $e->getMessage())), 'error');
   }
}

function evolent_delete_contact_v1() {

}

function evolent_list_all_contact_v1() {
  $query = db_select(CONTACT_V1_TABLE, 'cv1')
            ->fields('cv1', array('cid', 'first_name','last_name'))
            ->addTag('node_access');

  $result = $query->execute()->fetchAll();


  $header = array(
    array( 'data' => t('Id'), 'field' => 'cv1.cid'),
    array( 'data' => t('First Name'), 'field' => 'cv1.first)name'),
    array( 'data' => t('Last name'), 'field' => 'cv1.last_name'),
    );
  $rows = array();
  foreach ($result as  $row) {
    $rows[] = array('data' =>  (array) $row);
  }
  $output = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    );
  return $output;
}


function evolent_show_contact_v1() {

}
