<?php
/**
 * @file
 * Code for dosomething_campaign admin functionality.
 */

/**
 * Form constructor for campaign admin config form.
 *
 * @see dosomething_campaign_menu()
 */
function dosomething_campaign_admin_config_form($form, &$form_state) {

  // Standard campaign variables.
  $form['campaign'] = array(
    '#type' => 'fieldset',
    '#title' => t('Standard Campaigns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Comma separated list of default Gallery File fid's.
  $var_name = 'dosomething_campaign_default_gallery_fids';
  $form['campaign'][$var_name] = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder Gallery Files'),
    '#description' => t("A comma separated list of !link to use for the Gallery if not enough Reportbacks exist.  Do not use spaces.<p>e.g. 3123,234,8929,100112", array(
      '!link' => l("File fid's", 'admin/content/files'),
    )),
    '#required' => TRUE,
    '#default_value' => variable_get($var_name),
  );

  // Reportback variables.
  $form['campaign']['reportback'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reportback'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  // Label for Number of participants form field.
  $var_name = 'dosomething_reportback_num_participants_label';
  $form['campaign']['reportback'][$var_name] = array(
    '#type' => 'textfield',
    '#title' => t('Number of Participants Form Label'),
    '#description' => t("If a Campaign is set to collect number of participants in the Reportback form, this label is displayed."),
    '#required' => TRUE,
    '#default_value' => t(variable_get($var_name)),
  );

  // Confirmation page:
  $form['campaign']['confirmation_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Confirmation Page'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['campaign']['confirmation_page']['dosomething_campaign_confirmation_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Confirmation Page Title'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_confirmation_page_title')),
  );
  $form['campaign']['confirmation_page']['dosomething_campaign_confirmation_page_button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Confirmation Page Button Text'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_confirmation_page_button_text')),
  );

  // Action page:
  $form['campaign']['action_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Action Page'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['campaign']['action_page']['dosomething_campaign_problem_share_prompt'] = array(
    '#type' => 'textfield',
    '#title' => t('Problem Fact Share Prompt'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_problem_share_prompt')),
  );

  $form['campaign']['action_page']['dosomething_campaign_enable_onboarding'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable onboarding'),
    '#default_value' => variable_get('dosomething_campaign_enable_onboarding'),
  );

  $form['campaign']['action_page']['dosomething_campaign_onboarding_developer_mode'] = [
    '#type' => 'checkbox',
    '#title' => t('Onboarding developer mode'),
    '#description' => t('"YOU BETTER TURN THIS OFF" -Jen. And obviously don\'t enable this on prod.'),
    '#default_value' => variable_get('dosomething_campaign_onboarding_developer_mode'),
  ];

  $form['campaign']['action_page']['dosomething_campaign_onboarding_context_slide'] = [
    '#type' => 'checkbox',
    '#title' => t('Display Context Slide'),
    '#default_value' => variable_get('dosomething_campaign_onboarding_context_slide'),
  ];

  $form['campaign']['action_page']['dosomething_campaign_onboarding_campaign_slide'] = [
    '#type' => 'checkbox',
    '#title' => t('Display Campaign Slide'),
    '#default_value' => variable_get('dosomething_campaign_onboarding_campaign_slide'),
  ];

  $form['campaign']['action_page']['dosomething_campaign_onboarding_instruction_slide'] = [
    '#type' => 'checkbox',
    '#title' => t('Display Instruction Slide'),
    '#default_value' => variable_get('dosomething_campaign_onboarding_instruction_slide'),
  ];

  $form['campaign']['action_page']['dosomething_campaign_onboarding_reportback_items_slide'] = [
    '#type' => 'checkbox',
    '#title' => t('Display Reportback Items Slide'),
    '#default_value' => variable_get('dosomething_campaign_onboarding_reportback_items_slide'),
  ];


  // SMS Game variables.
  $form['sms_game'] = array(
    '#type' => 'fieldset',
    '#title' => t('SMS Games'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['sms_game']['dosomething_campaign_sms_game_signup_friends_form_button_copy'] = array(
    '#type' => 'textfield',
    '#title' => t('Signup Friends Form Button Label'),
    '#description' => t("Text displayed on the Signup Friends Form. Defaults to <em>Share</em> if not set."),
    '#default_value' => t(variable_get('dosomething_campaign_sms_game_signup_friends_form_button_copy')),
  );
  $form['sms_game']['dosomething_campaign_sms_game_all_participants_copy'] = array(
    '#type' => 'textarea',
    '#required' => TRUE,
    '#title' => t('Total participants in all SMS Games copy'),
    '#description' => t("This copy is displayed in every SMS Game. e.g. <em>Join 250,000 people who have played since 2012!</em>"),
    '#default_value' => t(variable_get('dosomething_campaign_sms_game_all_participants_copy')),
  );
  $form['sms_game']['confirmation_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Confirmation Page'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['sms_game']['confirmation_page']['dosomething_campaign_sms_game_confirmation_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Confirmation Page Title'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_sms_game_confirmation_page_title')),
  );
  $form['sms_game']['confirmation_page']['dosomething_campaign_confirmation_page_anon_button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Anon User: Button Text'),
    '#description' => t('Button label if an anonymous user is viewing the confirmation page -- links to the login/register modal.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_confirmation_page_anon_button_text')),
  );
  $form['sms_game']['confirmation_page']['dosomething_campaign_confirmation_page_anon_cta_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Anon User: Call to Action'),
    '#description' => t('Appears above the button if an anonymous user is viewing the confirmation page.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_confirmation_page_anon_cta_text')),
  );
  // Closed variables.
  $form['closed'] = array(
    '#type' => 'fieldset',
    '#title' => t('Closed Campaign'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['closed']['dosomething_campaign_presignup_callout_copy'] = array(
    '#type' => 'textarea',
    '#title' => t('Presignup Form Callout Copy'),
    '#required' => TRUE,
    '#description' => t("Callout text displayed for the Presignup Form."),
    '#default_value' => t(variable_get('dosomething_campaign_presignup_callout_copy')),
  );
  // The pre-signup button text.
  $form['closed']['dosomething_campaign_run_signup_button_copy'] = array(
    '#type' => 'textfield',
    '#title' => t('Presignup Form Button Text'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_run_signup_button_copy')),
  );
  // If there are no total number of X collected.
  $form['closed']['dosomething_campaign_run_no_total_copy'] = array(
    '#type' => 'textarea',
    '#title' => t('Waiting for total copy'),
    '#description' => t('Place [label] where you would like the label to be replaced.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_run_no_total_copy')),
  );
   // No winners yet copy.
  $form['closed']['dosomething_campaign_run_no_winner_copy'] = array(
    '#type' => 'textarea',
    '#title' => t('Waiting for Winner Copy'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_run_no_winner_copy')),
  );
  // Permalink page.
  $form['permalink'] = array(
    '#type' => 'fieldset',
    '#title' => t('Permalink Page'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Permalink owners vars.
  $form['permalink']['owners'] = array(
    '#type' => 'fieldset',
    '#title' => t('Owners Permalink'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['permalink']['owners']['confirmation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Owners Permalink as confirmation page'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['permalink']['owners']['confirmation']['dosomething_campaign_permalink_confirmation_owners_page_subtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink confirmation page subtitle'),
    '#description' => t('Appears on the confirmation page above the reportback of the owner.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_confirmation_owners_page_subtitle')),
  );
  $form['permalink']['owners']['confirmation']['dosomething_campaign_permalink_confirmation_owners_scholarship'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink confirmation page scholarship addition'),
    '#description' => t('Displays scholarhship info if a campaign has it.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_confirmation_owners_scholarship')),
  );
  $form['permalink']['owners']['confirmation']['dosomething_campaign_permalink_confirmation_owners_important_to_you'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink confirmation page important to you header'),
    '#description' => t('Appears above the why is this important to you user copy.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_confirmation_owners_important_to_you')),
  );
  $form['permalink']['owners']['confirmation']['dosomething_campaign_permalink_confirmation_owners_social_cta'] = array(
    '#type' => 'textfield',
    '#title' => t('Social cta on reportback permalink page.'),
    '#description' => t('Appears above the social share on the reportback confirmation page.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_confirmation_owners_social_cta')),
  );
  $form['permalink']['owners']['confirmation']['dosomething_campaign_permalink_confirmation_owners_social_network_copy'] = array(
    '#type' => 'textfield',
    '#title' => t('Social network copy.'),
    '#description' => t('Appears after share on social network.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_confirmation_owners_social_network_copy')),
  );
  $form['permalink']['owners']['failure'] = array(
    '#type' => 'fieldset',
    '#title' => t('Owners Permalink Failure Page'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['permalink']['owners']['failure']['dosomething_campaign_permalink_failure_copy'] = array(
    '#type' => 'textarea',
    '#title' => t('Permalink failure page text'),
    '#description' => t('Appears on the failure page to the right side of the image.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_failure_copy')),
  );
  $form['permalink']['owners']['failure']['dosomething_campaign_permalink_failure_image_nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink failure page image'),
    '#description' => t('NID of the image that appears on the failure page in place of the reportback image.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_failure_image_nid')),
  );
  $form['permalink']['owners']['dosomething_campaign_permalink_owners_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink owners title'),
    '#description' => t('Appears above the reportback if the owner user is viewing the permalink page.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_owners_page_title')),
  );
  $form['permalink']['owners']['dosomething_campaign_permalink_owners_page_subtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink owners subtitle'),
    '#description' => t('Appears above the reportback if the owner user is viewing the permalink page.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_owners_page_subtitle')),
  );
    // Permalink owners vars.
  $form['permalink']['nonowners'] = array(
    '#type' => 'fieldset',
    '#title' => t('Non-owners Permalink'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['permalink']['nonowners']['dosomething_campaign_permalink_nonowners_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink non-owners page title'),
    '#description' => t('Appears above the reportback if an anonymous user (or a non-owner) is viewing the permalink page.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_nonowners_page_title')),
  );
  $form['permalink']['nonowners']['dosomething_campaign_permalink_nonowners_page_title_backup'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink non-owners page title backup'),
    '#description' => t('If the title contains sensitive user information this is used as a backup.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_nonowners_page_title_backup', 'Join DoSomething.org!')),
  );
  $form['permalink']['nonowners']['dosomething_campaign_permalink_nonowners_closed_cta'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink non-owners campaign closed CTA'),
    '#description' => t('Appears near the button that links to /campagins.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_nonowners_closed_cta')),
  );
  $form['permalink']['nonowners']['dosomething_campaign_permalink_nonowners_closed_button_copy'] = array(
    '#type' => 'textfield',
    '#title' => t('Permalink non-owners closed button copy'),
    '#description' => t('Appears in place of the sign up button when the campagin is closed.'),
    '#required' => TRUE,
    '#default_value' => t(variable_get('dosomething_campaign_permalink_nonowners_closed_button_copy')),
  );

  return system_settings_form($form);
}

/**
 * Page callback for campaign admin custom settings page.
 *
 * @param object $node
 *   A loaded node.
 */
function dosomething_campaign_admin_custom_settings_page($node) {
  $output = '';
  if (user_access('edit campaign overrides') || user_access('administer modules')) {
    $variable_form = drupal_get_form('dosomething_helpers_variable_form', $node);
    $output .= render($variable_form);
  }

  // Render third party form.
  $form_id = 'dosomething_helpers_third_party_variable_form';
  $third_party_form = drupal_get_form($form_id, $node);
  $output .= render($third_party_form);

  if (module_exists('dosomething_signup')) {
    $signup_data_config_form = drupal_get_form('dosomething_signup_node_signup_data_form', $node);
    $output .= render($signup_data_config_form);
  }
  if (module_exists('dosomething_organ_donation')) {
    $organ_donation_config_form = drupal_get_form('dosomething_organ_donation_config_form', $node);
    $output .= render($organ_donation_config_form);
  }
  if (module_exists('dosomething_helpers')) {
    $form_id = 'dosomething_campaign_reportback_config_form';
    $reportback_field_form = drupal_get_form($form_id, $node);
    $output .= render($reportback_field_form);
  }
  if (module_exists('dosomething_rogue')) {
    $rogue_config_form = drupal_get_form('dosomething_rogue_campaign_config_form', $node);
    $output .= render($rogue_config_form);
  }

  return $output;
}

/**
 * Page callback for campaign admin status page.
 */
function dosomething_campaign_admin_status_page() {
  $vars['header'] = array('Nid', 'Edit', 'Status', 'Char count');
  // Display campaigns with title values over recommended limit.
  foreach (dosomething_campaign_admin_status_title_query() as $record) {
    $vars['rows'][] = dosomething_campaign_admin_status_get_row_array($record);
  }
  $output = '<h2>Titles over 20 characters</h2>';
  $output .= theme('table', $vars);
  // Initialize rows as empty array.
  $vars['rows'] = array();
  // Display campaigns with field_call_to_action values over recommended limit.
  foreach (dosomething_campaign_admin_status_call_to_action_query() as $record) {
    $vars['rows'][] = dosomething_campaign_admin_status_get_row_array($record);
  }
  $output .= '<h2>Call to action over 65 characters</h2>';
  $output .= theme('table', $vars);
  return $output;
}

/**
 * Returns array for admin status table rows for given query result $record.
 *
 * @param object $record
 *   A query result record as returned by query->execute().
 *
 * @return array
 *   Array with expected values for a campaign admin status table.
 */
function dosomething_campaign_admin_status_get_row_array($record) {
  return array(
    $record->nid,
    l($record->title, 'node/' . $record->nid . '/edit', array(
      // Link back to admin status page for editor to verify char count is ok.
      'query' => array('destination' => 'admin/content/campaign-status'))
    ),
    $record->status ? 'Published' : 'Unpublished',
    $record->length,
  );
}

/**
 * Returns campaign nodes with titles having char_count greater than given
 * $char_count.
 *
 * @param int $char_count
 *   The number of characters to check for.
 *
 * @return array
 *   Result array of the query.
 */
function dosomething_campaign_admin_status_title_query($char_count = 20) {
  $query = db_select('node', 'n');
  $query->condition('type', 'campaign');
  $query->fields('n', array('nid', 'title', 'status'));
  $query->addExpression('CHAR_LENGTH(n.title)', 'length');
  $query->where('CHAR_LENGTH(n.title) > ' . $char_count);
  return $query->execute();
}

/**
 * Returns campaign nodes with call_to_action having char_count greater than given
 * $char_count.
 *
 * @param int $char_count
 *   The number of characters to check for.
 *
 * @return array
 *   Result array of the query.
 */
function dosomething_campaign_admin_status_call_to_action_query($char_count = 65) {
  $query = db_select('node', 'n');
  $query->condition('type', 'campaign');
  $query->join('field_data_field_call_to_action', 'cta', 'n.nid = cta.entity_id');
  $query->fields('n', array('nid', 'title', 'status'));
  $query->addExpression('CHAR_LENGTH(cta.field_call_to_action_value)', 'length');
  $query->where('CHAR_LENGTH(cta.field_call_to_action_value) > ' . $char_count);
  return $query->execute();
}

/**
 * Sets helpers variables related to Reportback functionality.
 */
function dosomething_campaign_reportback_config_form($form, &$form_state, $node) {
  // Load the node's helpers variables.
  $vars = dosomething_helpers_get_variables('node', $node->nid);
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['rb'] = array(
    '#type' => 'fieldset',
    '#title' => t("Reportbacks"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['rb']['collect_num_participants'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collect number of participants'),
    '#description' => t('If set, the Reportback form will include an additional question asking for number of participants.'),
    '#default_value' => $vars['collect_num_participants'],
    '#size' => 20,
  );
  $form['rb']['disable_reactions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable voting on the reportback items'),
    '#description' => t('If set, users will not be able to react to reportback items.'),
    '#default_value' => $vars['disable_reactions'],
    '#size' => 20,
  );
  $form['rb']['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => 'Save',
    ),
  );
  return $form;
}

/**
 * Submit callback for dosomething_campaign_reportback_config_form().
 */
function dosomething_campaign_reportback_config_form_submit(&$form, &$form_state) {
  $var_names = ['collect_num_participants', 'disable_reactions'];
  foreach($var_names as $var_name) {
    $values = $form_state['values'];
    dosomething_helpers_set_variable('node', $values['nid'], $var_name, $values[$var_name]);
  }
  drupal_set_message("Updated.");
}

/**
 * Form constructor for archiving Campaign activity to a Campaign Run.
 *
 * @param object $node
 *   A loaded campaign node.
 *
 * @ingroup forms
 */
function dosomething_campaign_archive_activity_form($form, &$form_state, $node) {
  $campaign_runs = dosomething_campaign_get_campaign_runs($node);
  // Should't happen, but just in case:
  if (empty($campaign_runs)) {
    $form['markup'] = array(
      '#markup' => t("There are no Campaign Run nodes associated with this campaign."),
    );
    return $form;
  }

  $form['source_nid'] = array(
    '#type' => 'hidden',
    '#default_value' => $node->nid,
  );
  $form['target_nid'] = array(
    '#type' => 'radios',
    '#required' => TRUE,
    '#title' => t("Archive all current Signups and Reportbacks to:"),
    '#options' => $campaign_runs,
    '#description' => t("Warning! This cannot be undone.  Do not do this unless you really, really mean it."),
  );
  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t("Archive"),
    ),
  );
  return $form;
}

/**
 * Submit callback for dosomething_campaign_reportback_config_form().
 */
function dosomething_campaign_archive_activity_form_submit(&$form, &$form_state) {
  $source_nid = $form_state['values']['source_nid'];
  $target_nid = $form_state['values']['target_nid'];

  //@todo Add batch processing for cases where there are large numbers of signups.

  // Update signups.
  $num_signups = db_update('dosomething_signup')
    ->fields(array(
      'nid' => $target_nid,
    ))
    ->condition('nid', $source_nid)
    ->execute();
  // Update reportbacks.
  $num_reportbacks = db_update('dosomething_reportback')
    ->fields(array(
      'nid' => $target_nid,
    ))
    ->condition('nid', $source_nid)
    ->execute();

  drupal_set_message(t("Archived @signups Signups and @reportbacks Reportbacks from @source to @target.", array(
    '@signups' => $num_signups,
    '@reportbacks' => $num_reportbacks,
    '@source' => $source_nid,
    '@target' => $target_nid,
  )));
}
