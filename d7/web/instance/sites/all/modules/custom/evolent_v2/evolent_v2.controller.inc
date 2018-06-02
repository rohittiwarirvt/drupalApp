<?php

/**
 * Controller for loading, creating, and saving contact_v2s.
 *
 * The default loader, which we extend, handles load() already. We only
 * need to add saving and creating.
 */

class ContactController extends DrupalDefaultEntityController {


  public function save($contact_v2) {
    $transaction = db_transaction();

    try {
      global $user;

       // Determine if we will be inserting a new contact_v2.
      $contact_v2->is_new = empty($contact_v2->cid);

            // Set the timestamp fields.
      if (empty($contact_v2->created)) {
        $contact_v2->created = REQUEST_TIME;
      }

      $contact_v2->changed = REQUEST_TIME;
      $contact_v2->revision_timestamp = REQUEST_TIME;
      $update_contact_v2 = TRUE;

      // Give modules the opportunity to prepare field data for saving.
      field_attach_presave('contact_v2', $contact_v2);
      // When saving a new contact_v2 revision, unset any existing $contact_v2->vid
      // to ensure a new revision will actually be created and store the old
      // revision ID in a separate property for contact_v2 hook implementations.
      if (!$contact_v2->is_new && !empty($contact_v2->revision) && $contact_v2->vid) {
        $contact_v2->old_vid = $contact_v2->vid;
        unset($contact_v2->vid);
      }

      // If this is a new contact_v2...
      if ($contact_v2->is_new) {
        // Save the new contact_v2.
        drupal_write_record('contact_v2', $contact_v2);

        // Save the initial revision.
        $this->saveRevision($contact_v2, $user->uid);

        $op = 'insert';
      }
      else {
        // Save the updated contact_v2.
        drupal_write_record('contact_v2', $contact_v2, 'cid');

        // If a new contact_v2 revision was requested, save a new record for that;
        // otherwise, update the contact_v2 revision record that matches the value
        // of $contact_v2->vid.
        if (!empty($contact_v2->revision)) {
          $this->saveRevision($contact_v2, $user->uid);
        }
        else {
          $this->saveRevision($contact_v2, $user->uid, TRUE);
          $update_contact_v2 = FALSE;
        }

        $op = 'update';
      }

      // If the revision ID is new or updated, save it to the contact_v2.
      if ($update_contact_v2) {
        db_update('contact_v2')
          ->fields(array('vid' => $contact_v2->vid))
          ->condition('cid', $contact_v2->cid)
          ->execute();
      }

      // Save fields.
      $function = 'field_attach_' . $op;
      $function('contact_v2', $contact_v2);

      module_invoke_all('entity_' . $op, $contact_v2, 'contact_v2');

      // Clear internal properties.
      unset($contact_v2->is_new);

      // Ignore slave server temporarily to give time for the saved order to be
      // propagated to the slave.
      db_ignore_slave();

      return $contact_v2;
    }
    catch( Exception $e) {
      $transaction->rollback();
      watchdog('evolent_v2', '$e', NULL(), WATCHDOG_ERROR);
      return FALSE;
    }
  }

  /**
   * Saves an contact_v2 revision with the uid of the current user.
   *
   * @param $contact_v2
   *   The fully loaded contact_v2 object.
   * @param $uid
   *   The user's uid for the current revision.
   * @param $update
   *   TRUE or FALSE indicating whether or not the existing revision should be
   *     updated instead of a new one created.
   */

  function saveRevision($contact_v2, $uid, $update = FALSE) {
    // Hold on to the contact_v2's original creator_uid but swap in the revision's
    // creator_uid for the momentary write.
    $temp_uid = $contact_v2->uid;
    $contact_v2->uid = $uid;

    // Update the existing revision if specified.
    if ($update) {
      drupal_write_record('contact_v2_revision', $contact_v2, 'vid');
    }
    else {
      // Otherwise insert a new revision. This will automatically update $contact_v2
      // to include the vid.
      drupal_write_record('contact_v2_revision', $contact_v2);
    }

    // Reset the order's creator_uid to the original value.
    $contact_v2->uid = $temp_uid;
 }


  /**
   * Deletes multiple contact_v2s by ID.
   *
   * @param $cids
   *   An array of contact_v2 IDs to delete.
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($cids) {
    if (!empty($cids)) {
      $contact_v2s = $this->load($cids, array());

      $transaction = db_transaction();

      try {
        db_delete('contact_v2')
          ->condition('cid', $cids, 'IN')
          ->execute();

        db_delete('contact_v2_revision')
          ->condition('cid', $cids, 'IN')
          ->execute();

        foreach ($contact_v2s as $contact_v2_id => $contact_v2) {
          field_attach_delete('contact_v2', $contact_v2);
        }

        // Ignore slave server temporarily to give time for the
        // saved contact_v2 to be propagated to the slave.
        db_ignore_slave();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('contact_v2', $e, NULL, WATCHDOG_ERROR);
        return FALSE;
      }

      module_invoke_all('entity_delete', $contact_v2, 'contact_v2');

      // Clear the page and block and contact_v2 caches.
      cache_clear_all();
      $this->resetCache();
    }

    return TRUE;
  }

  /**
   *  Create a default contact
   *
   *  @param $type
   *    The machine readable type of contacts
   *
   *  @return
   *
   *    An contact_v2 with all the default value initialized
   *
   */

  public function create($type = '') {
    return (object) array(
      'cid' => '',
      'type' => $type,
      'title' => '',
      'first_name' => '',
      'last_name' => '',
      'email' => '',

    );
  }
}
