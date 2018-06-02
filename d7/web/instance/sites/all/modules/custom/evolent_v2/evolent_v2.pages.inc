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

  $contacts_v2 = entity_get_controller('contacts_v2')-> create($type);

  drupal_set_title(t('Create @name'), array('@name' => $types[$type]->name), PASS_THROUGH);

  return drupal_get_form($type . '_contacts_v2_form', $contacts_v2);
}
