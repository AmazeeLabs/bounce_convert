<?php

define('BOUNCE_CONVERT_CONTENT_TYPE', 'bounce_convert_campaign');

/**
 * @return array A list of published webforms
 */
function bounce_convert_webforms() {
  $nodes = node_load_multiple(array(), array(
    'type' => 'webform',
    'status' => 1,
  ));
  $webforms = array();
  $webforms[0] = 'Select a value';
  foreach ($nodes as $nid => $node) {
    $webforms[$nid] = check_plain($node->title);
  }
  return $webforms;
}

/**
 * @return array A list of published campaign matching user role ids
 */
function bounce_convert_check_campaigns($user_rids) {
  //Default value to not show the modal
  $bounce_convert_show_moadal = FALSE;

  //get role ids instead of role names
  $user_rids = array_keys($user_rids);

  /* fetch only published and active campagins (ie: status = 1 and active = yes) */
  $query = new EntityFieldQuery;
  $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_bcc_active', 'value', 'Yes', '=')
      ->execute();

  /*
   * Check if campaign exists
   */
  if (!empty($result)) {
    foreach ($result['node'] as $obj_node) {
      $node = node_load($obj_node->nid);

      /*
       * Filter campaigns by user role
       * If user role matches with campaign role THEN show modal ELSE don't show
       */
      if (!bounce_convert_check_user_role($node, $user_rids)) {
        continue;
      }

      /*
       * If one of two option is selected from (bellow listed pages / except bellow listed pages)
       */
      $bounce_convert_pages_option = field_get_items('node', $node, 'field_bcc_pages_option');


      // show only on user given paths/pages
      if (!empty($bounce_convert_pages_option)) {

        /*
         * Weather show modal on all pages except bellow (0)
         * or
         * show modal only bellow listed pages (1)
         */
        $bounce_convert_pages_option = $bounce_convert_pages_option[0]['value'];


        /*
         * List of pages by using their paths. Entered one path per line by admin.
         * Creating array of path by preg_replace and explode.
         */
        $bounce_convert_field_visibility_settings = field_get_items('node', $node, 'field_bcc_pages_list');
        $bounce_convert_field_visibility_settings = $bounce_convert_field_visibility_settings[0]['value'];
        $bounce_convert_field_visibility_settings = preg_replace('#\s+#', ',', trim($bounce_convert_field_visibility_settings));
        $bounce_convert_field_visibility_settings = explode(',', $bounce_convert_field_visibility_settings);


//        //atleast one path is set/givin 
        if ($bounce_convert_field_visibility_settings[0]) {
          $bounce_convert_show_moadal = bounce_convert_check_page_path($bounce_convert_field_visibility_settings);
          if ($bounce_convert_show_moadal) {
            $bounce_convert_webfrom_nid = field_get_items('node', $node, 'field_bcc_select_webform');
            $bounce_convert_webfrom_nid = $bounce_convert_webfrom_nid[0]['value'];

            $bounce_convert_cookie_expiration = field_get_items('node', $node, 'field_bcc_cookie_expiration');
            $bounce_convert_cookie_expiration = $bounce_convert_cookie_expiration[0]['value'];

            return array($bounce_convert_webfrom_nid, $bounce_convert_cookie_expiration);
          }
          else {
            return FALSE;
          }
        }
      }
      else {
        //show modal on all pages if no specific paths given
        $bounce_convert_webfrom_nid = field_get_items('node', $node, 'field_bcc_select_webform');
        $bounce_convert_webfrom_nid = $bounce_convert_webfrom_nid[0]['value'];

        $bounce_convert_cookie_expiration = field_get_items('node', $node, 'field_bcc_cookie_expiration');
        $bounce_convert_cookie_expiration = $bounce_convert_cookie_expiration[0]['value'];
        return array($bounce_convert_webfrom_nid, $bounce_convert_cookie_expiration);
      }
    }
  }
}

function bounce_convert_check_user_role($node, $user_rids) {
  // show to specific user
  if (!empty($node->field_bcc_specific_user_roles)) {
    foreach ($node->field_bcc_specific_user_roles['und'] as $role) {
      $campaign_roles[] = $role['value'];
    }

    // if user role matches campaign role 
    $result = array_intersect($campaign_roles, $user_rids);
    if (!empty($result)) {
      return TRUE;
    }
    else {
      // if user role DOESN'T matches campaign role 
      return FALSE;
    }
  }
  else {
    //show to all users
    return TRUE;
  }
}

/**
 * @return boolean, show modal on current page/path or not
 */
function bounce_convert_check_page_path($bounce_convert_field_visibility_settings) {
  if (in_array(current_path(), $bounce_convert_field_visibility_settings)) {
    //exact match eg. admin/modules
    return TRUE;
  }
  else {
    // wild card character path eg. admin/* 
    foreach ($bounce_convert_field_visibility_settings as $key => $path) {
      $path = $bounce_convert_field_visibility_settings[$key] = str_replace('*', '', $path);

      $pos = strpos(current_path(), $path);
      if ($pos !== false) {
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
  }
}

/**
 * Add custom fields for content type
 */
function bounce_convert_add_fields() {
  foreach (bounce_convert_field_default_field_bases() as $field) {
    field_create_field($field);
  }
  foreach (bounce_convert_field_default_field_instances() as $fieldinstance) {
    $fieldinstance['entity_type'] = 'node';
    $fieldinstance['bundle'] = BOUNCE_CONVERT_CONTENT_TYPE;
    field_create_instance($fieldinstance);
  }
}

/**
 * Delete custom fields for content type
 */
function bounce_convert_delete_fields() {
  foreach (array_keys(bounce_convert_field_default_field_bases()) as $field) {
    field_delete_field($field);
  }
  $instances = field_info_instances('node', BOUNCE_CONVERT_CONTENT_TYPE);
  foreach ($instances as $instance_name => $fieldinstance) {
    field_delete_instance($fieldinstance);
  }
}

/**
 * Insert user conversion data to table
 */
function bounce_convert_user_conversion() {
  drupal_set_message("Yahooooooooooooooooooooooo !");
}
