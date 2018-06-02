<?php


/**
 * Menu callback; Render a page to add a contacts v2
 */


function contacts_v2_add_page() {
  $item = menu_get_item();
  $links = system_admin_menu_block($item);

  foreach ($links as $link) {
    $items[] = l($link['title'], $link['href'], $item['localized_options']) . ': ' . filter_xss_admin($link['description']);
  }

  return theme('item_list', array('items' => $items));

}


/**
 * Menu callback; Add contacts
 *
 * @param $type
 */

function contacts_v2_add($type) {
  global $user;

  $types = contacts_v2_types();

  $type = isset($type) ? str_replace('-', '_', $type) : NULL;

  if (empty($types[$type])) {
    return MENU_NOT_FOUND;
  }

  $contacts_v2 = entity_get_controller('contact_v2')-> create($type);
  drupal_set_title(t('Create @name', array('@name' => $types[$type]->name)), PASS_THROUGH);

  return drupal_get_form($type . '_contacts_v2_form', $contacts_v2);
}


/**
 * Menu callback: View a contacts v2
 *
 * @param $contact_v1
 *   the contact object we want to display
 *
 * @param $view_mode
 *  The view mode we want to display.
 *
 */

function contacts_v2_page_view($contact_v2, $view_mode = 'full') {
  // Remove previously built content, if exists.
  $contact_v2->content = array();

  if ($view_mode == 'teaser') {
    $contact_v2->content['title'] = array(
      '#markup' => filter_xss($contact_v2->title) . '<br/>',
      '#weight' => -5,
    );
  }

  field_attach_prepare_view('contact_v2', array($contact_v2->cid => $contact_v2), $view_mode);
  entity_prepare_view('contact_v2', array($contact_v2->cid => $contact_v2));
  $contact_v2->content += field_attach_view('contact_v2', $contact_v2, $view_mode);

  $extra_fields = evolent_v2_field_extra_fields();

  if (empty($extra_fields['contact_v2'][$contact_v2->type]['display'])) {
    return ;
  }

  $config = field_bundle_settings('contact_v2', $contact_v2->type);
  foreach ($extra_fields['contact_v2'][$contact_v2->type]['display'] as $field_name => $field_info) {
    if (empty($config['extra_fields']['display'][$field_name][$view_mode]['visible'])) {
      continue;
    }
    $element = array(
      '#tag' => 'span',
      '#value' => $contact_v2->$field_name . '<br/>',
    );
    $attributes= array();
    $attributes['class'] = $field_name;
    $element['#attributes'] = $attributes;
    $variables['element'] = $element;
    $contact_v2->content[$field_name]['#markup'] = theme('html_tag', $variables);
  }
  return $contact_v2->content;
}




/**
 * Menu callback; presents the contact_v2 editing form, or redirects to delete confirmation.
 *
 * @param $contact_v2
 *   The contact_v2 object to edit.
 */

function contact_v2_page_edit($contact_v2) {
  $types = contacts_v2_types();
  drupal_set_title(t('<em>Edit @type</em> @title', array('@type' => $types[$contact_v2->type]->name, '@title' => $contact_v2->title)), PASS_THROUGH);

  return drupal_get_form($contact_v2->type . '_contacts_v2_form', $contact_v2);
}



/**
 * Form bulder; Asks for confirmation of contacts_v2 deletion.
 */
function contacts_v2_delete_confirm($form, &$form_state, $contacts_v2) {
  $form['#contacts_v2'] = $contacts_v2;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['cid'] = array('#type' => 'value', '#value' => $contacts_v2->cid);
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $contacts_v2->title)),
    'contacts_v2/' . $contacts_v2->cid,
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}


/**
 * Executes contacts_v2 deletion.
 */
function contacts_v2_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $contacts_v2 = contacts_v2_load($form_state['values']['cid']);
    contact_v2_delete($form_state['values']['cid']);
    watchdog('contacts_v2', '@type: deleted %title.', array('@type' => $contacts_v2->type, '%title' => $contacts_v2->title));

    $types = contacts_v2_types();
    drupal_set_message(t('@type %title has been deleted.', array('@type' => $types[$contacts_v2->type]->name, '%title' => $contacts_v2->title)));
  }

  $form_state['redirect'] = '<front>';
}


/**
 * Menu callback; Displays a listing of recent contact_v2s.
 *
 * This doesn't really work yet because our presentation code doesn't show
 * the title.
 */
function contact_v2_page_list_recent() {
  $content = array();

  $query = new EntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'contact_v2')
    ->propertyOrderBy('created', 'DESC');
  $result = $query->execute();

  $contact_v2s = contact_v2_load_multiple(array_keys($result['contact_v2']));
  foreach ($contact_v2s as $contact_v2) {
    $content[$contact_v2->cid] = contacts_v2_page_view($contact_v2, 'teaser');
  }

  return $content;
}


/**
 * Form builder; Displays the contact_v2 add/edit form.
 *
 * @param $form
 * @param $form_state
 * @param $contact_v2
 *   The contact_v2 object to edit, which may be brand new.
 */
function contact_v2_form($form, &$form_state, $contact_v2) {

  // Set the id and identify this as an contact_v2 edit form.
  $form['#id'] = 'contact-v2-form';

  // Save the contact_v2 for later, in case we need it.
  $form['#contact_v2'] = $contact_v2;
  $form_state['contact_v2'] = $contact_v2;

  // Common fields. We don't have many.
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $contact_v2->title,
    '#weight' => -5,
    '#required' => TRUE,
  );
  $form['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#default_value' => $contact_v2->first_name,
    '#weight' => -4,
    '#required' => TRUE,
  );

  $form['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => $contact_v2->last_name,
    '#weight' => -3,
    '#required' => TRUE,
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => $contact_v2->email,
    '#weight' => -5,
    '#required' => TRUE,
  );
  $form['revision'] = array(
    '#access' => user_access('administer contact_v2s'),
    '#type' => 'checkbox',
    '#title' => t('Create new revision'),
    '#default_value' => 0,
  );

  // Add the buttons.
  $form['buttons'] = array();
  $form['buttons']['#weight'] = 100;
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('contact_v2_form_submit'),
  );
  if (!empty($contact_v2->cid)) {
    $form['buttons']['delete'] = array(
      '#access' => user_access('delete contact_v2s'),
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('contact_v2_form_delete_submit'),
    );
  }

  $form['#validate'][] = 'contact_v2_form_validate';

  field_attach_form('contact_v2', $contact_v2, $form, $form_state);

  return $form;
}

function contact_v2_form_validate($form, &$form_state) {
  $contact_v2 = $form_state['contact_v2'];

  // Field validation.
  field_attach_form_validate('contact_v2', $contact_v2, $form, $form_state);
}


function contact_v2_form_submit($form, &$form_state) {
  global $user;

  $contact_v2 = &$form_state['contact_v2'];

  // Set the contact_v2's uid if it's being created at this time.
  if (empty($contact_v2->uid)) {
    $contact_v2->uid = $user->uid;
  }

  $contact_v2->title = $form_state['values']['title'];
  $contact_v2->first_name = $form_state['values']['first_name'];
  $contact_v2->last_name = $form_state['values']['last_name'];
  $contact_v2->email = $form_state['values']['email'];

  $contact_v2->revision = $form_state['values']['revision'];

  // Notify field widgets.
  field_attach_submit('contact_v2', $contact_v2, $form, $form_state);

  // Save the contact_v2.
  contact_v2_save($contact_v2);

  // Notify the user.
  drupal_set_message(t('Contact saved.'));

  $form_state['redirect'] = 'contact_v2/' . $contact_v2->cid;
}


function contact_v2_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $contact_v2 = $form['#contact_v2'];
  $form_state['redirect'] = array('contact_v2/' . $contact_v2->cid . '/delete', array('query' => $destination));
}
