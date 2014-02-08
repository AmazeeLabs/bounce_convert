<?php

define('BOUNCE_CONVERT_CONTENT_TYPE', 'bounce_convert_campaign');

/**
 * @return array A list of published webforms
 */
function bounce_convert_campaign_webforms() {
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
  //get role ids instead of role names
  $user_rids = array_keys($user_rids);

  // filter published nodes for campaign type and specific roles
  $query = new EntityFieldQuery;
  $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_bcc_active', 'value', 'Yes', '=')
//      ->fieldCondition('field_bcc_specific_user_roles', 'value', (array) $user_rids, 'IN')
      ->execute();

  $bounce_convert_show_moadal = FALSE;
  if (count($result)) {
    foreach ($result['node'] as $obj_node) {
      $node = node_load($obj_node->nid);
      // (1) only bellow listed pages  (0) except bellow listed pages
      $bounce_convert_pages_option = field_get_items('node', $node, 'field_bcc_pages_option');

      //show only on user given paths/pages
      if (count($bounce_convert_pages_option)) {
        $bounce_convert_field_visibility_settings = field_get_items('node', $node, 'field_bcc_pages_list');
        $bounce_convert_field_visibility_settings = $bounce_convert_field_visibility_settings[0]['value'];
        $bounce_convert_field_visibility_settings = preg_replace('#\s+#', ',', trim($bounce_convert_field_visibility_settings));
        $bounce_convert_field_visibility_settings = explode(',', $bounce_convert_field_visibility_settings);

        $bounce_convert_pages_option = $bounce_convert_pages_option[0]['value'];
        //atleast one path is set/givin 
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
        //show modal on all pages
        $bounce_convert_show_moadal = TRUE;
      }
    }
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
function bounce_convert_campaign_add_fields() {
  foreach (bounce_convert_campaign_field_default_field_bases() as $field) {
    field_create_field($field);
  }
  foreach (bounce_convert_campaign_field_default_field_instances() as $fieldinstance) {
    $fieldinstance['entity_type'] = 'node';
    $fieldinstance['bundle'] = BOUNCE_CONVERT_CONTENT_TYPE;
    field_create_instance($fieldinstance);
  }
}

/**
 * Delete custom fields for content type
 */
function bounce_convert_campaign_delete_fields() {
  foreach (array_keys(bounce_convert_campaign_field_default_field_bases()) as $field) {
    field_delete_field($field);
  }
  $instances = field_info_instances('node', BOUNCE_CONVERT_CONTENT_TYPE);
  foreach ($instances as $instance_name => $fieldinstance) {
    field_delete_instance($fieldinstance);
  }
}
