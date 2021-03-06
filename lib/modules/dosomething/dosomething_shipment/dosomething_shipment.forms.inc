<?php
/**
 * @file
 * Provides form constructors for the DoSomething Shipment module.
 */

/**
 * Form constructor for a Shipment form.
 *
 * @param array $config
 *   Array of helper configuration values to output in the form.
 *
 * @ingroup forms
 */
function dosomething_shipment_form($form, &$form_state, $config) {
  $form['entity_type'] = array(
    '#type' => 'hidden',
    '#default_value' => $config['entity_type'],
    '#access' => FALSE,
  );
  $form['entity_id'] = array(
    '#type' => 'hidden',
    '#default_value' => $config['entity_id'],
    '#access' => FALSE,
  );
  $form['confirm_msg'] = array(
    '#type' => 'hidden',
    '#default_value' => $config['shipment_form_confirm_msg'],
    '#access' => FALSE,
  );
  $form['shipment_item'] = array(
    '#type' => 'hidden',
    '#default_value' => $config['shipment_item'],
    '#access' => FALSE,
  );
  $form['header'] = array(
    '#prefix' => '<h2 class="heading -banner">',
    '#markup' => $config['shipment_form_header'],
    '#suffix' => '</h2>',
  );
  // If old people can't submit form and logged user is an old person:
  if ($config['shipment_form_prevent_old_people_submit'] && dosomething_user_is_old_person()) {
    $form['copy'] = array(
      '#prefix' => '<div class="modal__block"><p>',
      '#markup' => $config['shipment_form_old_people_copy'],
      '#suffix' => '</p></div>',
    );
    // Return form without a submit button.
    return $form;
  }
  // If shipment exists already:
  $shipment = dosomething_shipment_get_shipment_id_by_entity($config['entity_type'], $config['entity_id']);
  if ($shipment) {
    // Store submitted copy.
    $copy = $config['shipment_form_submitted_copy'];
    // Check for [submitted] token.
    $copy = dosomething_signup_filter_form_submitted_copy($copy, $shipment->created);
    $form['copy'] = array(
      '#prefix' => '<div class="modal__block"><p>',
      '#markup' => $copy,
      '#suffix' => '</p></div>',
    );
    // Return form without a submit button.
    return $form;
  }
  $form['copy'] = array(
    '#prefix' => '<div class="modal__block"><p>',
    '#markup' => $config['shipment_form_copy'],
    '#suffix' => '</p></div>',
  );

  // Container for form elements
  $form['elements'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('modal__block'),
    ),
  );

  // Add Address form fields.
  dosomething_user_address_form_element($form['elements'], $form_state);

  if ($config['shipment_item'] == 'shirt') {
    // Add Shirt form fields.
    dosomething_shipment_shirt_form_element($form['elements'], $form_state);
  }

  $form['elements']['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => $config['shipment_form_submit_label'],
      '#attributes' => array(
        'class' => array('button'),
      ),
    ),
  );

  return $form;
}

/**
 * Submit callback for dosomething_reportback_form().
 */
function dosomething_shipment_form_submit($form, &$form_state) {
  global $user;
  // If user session no longer exists:
  if (!user_is_logged_in()) {
    // Tell them that.
    drupal_set_message(t("You are no longer logged in. Please log in."), 'error');
  }

  $values = $form_state['values'];

  // Save User address.
  dosomething_user_save_address_values($values);

  $shipment = entity_create('shipment', array(
    'uid' => $user->uid,
    'created' => REQUEST_TIME,
    'entity_type' => $values['entity_type'],
    'entity_id' => $values['entity_id'],
    'item' => $values['shipment_item'],
  ));
  // @todo: If Shipment Item is shirt, add option / additional item values.
  $shipment->save();

  drupal_set_message(t($values['confirm_msg']));
}
