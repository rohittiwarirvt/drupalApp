<?php

/**
 * Menu Callback; List all contacts v2 types available
 */

function contacts_v2_overview_types() {
  foreach (contacts_v2_types() as $type => $info) {
    $type_url_str = str_replace('_', '-', $type);
    $label = t('View @type', array('@type' => $info->name));
    $items[] = l($label, 'admin/structure/artworks/manage/' . $type_url_str);
  }

  return theme('item_list', array('items' => $items));
}


/**
 * Menu call back; Get Contact type information
 * @param  object $contact_v2_type
 */

function contact_v2_information($contact_v2_type) {
  return $contact_v2_type->name . ':' . $contact_v2_type->description;
}
