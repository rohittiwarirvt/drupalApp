<?php

function contact_load_util($conditions = array()) {
  $query = db_select(CONTACT_V1_TABLE, 'cv1');
  $query->fields('cv1');

  foreach ($conditions as $field => $value) {
    $query->condition($field, $value);
  }

  return $query->execute()->fetchAll();
}
