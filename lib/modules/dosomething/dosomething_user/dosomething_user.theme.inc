<?php
/**
 * @file
 * Preprocess functions for the dosomething_user module.
 */

/**
 * Returns markup for link to sign up for a campaign.
 *
 * @param string $label - The text to display on the button.
 * @param string $nid - The campaign node ID
 * @param string $title - The campaign title
 * @return string
 */
function dosomething_user_get_sign_up_link_markup($label, $nid, $title) {
  $openid_connect_enabled = variable_get('dosomething_user_openid_oauth_login_enabled');
  $openid_connect_link_style = $openid_connect_enabled ? '' : 'display: none';

  $openid_connect_link = l(t($label), 'user/authorize', [
    'query' => ['action' => 'signup', 'node' => $nid, 'title' => $title],
    'attributes' => [
      'id' => 'link--openid-connect-campaign-signup-login',
      'class' => ['button'],
      'data-track-category' => 'Link',
      'data-track-action' => 'Click',
      'data-track-label' => 'Signup (Unauthenticated)',
      'style' => $openid_connect_link_style,
    ]]);

  $legacy_link = l(t($label), '#', [
     'attributes' => [
       'id' => 'link--campaign-signup-login',
       'data-modal-href' => '#modal--login',
       'data-track-category' => 'Link',
       'data-track-action' => 'Click',
       'data-track-label' => 'Signup (Unauthenticated)',
       'class' => ['button'],
     ]
  ]);

  if (module_exists('dosomething_northstar') && $openid_connect_enabled) {
    return $openid_connect_link;
  }

  return $legacy_link . ' ' . $openid_connect_link;
}

/**
 * Returns markup for a link to login.
 *
 * @param string $label
 * @param array $class
 * @return string
 */
function dosomething_user_get_login_link($label, array $class = []) {
  $openid_connect_enabled = variable_get('dosomething_user_openid_oauth_login_enabled');
  $openid_connect_link_style = $openid_connect_enabled ? '' : 'display: none';

  $openid_connect_link = l(t($label), 'user/authorize', [
    'attributes' => [
      'id' => 'link--openid-connect-login',
      'data-track-category' => 'Link',
      'data-track-action' => 'Click',
      'data-track-label' => 'Login',
      'class' => $class,
      'style' => $openid_connect_link_style,
    ]
  ]);

  $legacy_link = l(t($label), 'user/login', [
    'attributes' => [
      'id' => 'link--login',
      'data-modal-href' => '#modal--login',
      'data-track-category' => 'Link',
      'data-track-action' => 'Click',
      'data-track-label' => 'Login',
      'class' => $class,
    ]
  ]);

  if (module_exists('dosomething_northstar') && $openid_connect_enabled) {
    return $openid_connect_link;
  }

  return $legacy_link . ' ' . $openid_connect_link;
}

/**
 * Returns markup for a link to register.
 *
 * @param string $label
 * @param array $class
 * @return string
 */
function dosomething_user_get_register_link($label, array $class = []) {
  $openid_connect_enabled = variable_get('dosomething_user_openid_oauth_login_enabled');
  $openid_connect_link_style = $openid_connect_enabled ? '' : 'display: none';

  $openid_connect_link = l(t($label), 'user/authorize', [
    'query' => ['mode' => 'register'],
    'attributes' => [
      'id' => 'link--openid-connect-register',
      'data-track-category' => 'Link',
      'data-track-action' => 'Click',
      'data-track-label' => 'Register',
      'class' => $class,
      'style' => $openid_connect_link_style,
    ]
  ]);

  $legacy_link = l(t($label), 'user/register', [
    'attributes' => [
      'id' => 'link--register',
      'data-modal-href' => '#modal--register',
      'data-track-category' => 'Link',
      'data-track-action' => 'Click',
      'data-track-label' => 'Register',
      'class' => $class
    ]
  ]);

  if (module_exists('dosomething_northstar') && $openid_connect_enabled) {
    return $openid_connect_link;
  }

  return $legacy_link . ' ' . $openid_connect_link;
}

/**
 * Implements template_preprocess_user_profile().
 */
function dosomething_user_preprocess_user_profile(&$variables) {
  // Collect User Account data.
  $uid = $variables['elements']['#account']->uid;
  $user = user_load($uid);
  $variables['first_name'] = dosomething_user_get_field('field_first_name', $user, 'ucwords');
  $variables['last_name'] = dosomething_user_get_field('field_last_name', $user, 'ucwords');
  $variables['edit_link'] = 'user/' . $uid . '/edit';
  $variables['email'] = $user->mail;
  $variables['mobile'] = dosomething_user_get_field('field_mobile', $user);

  // Collect Campaigns Doing.
  $variables['doing'] = array();
  $doing = dosomething_campaign_get_campaigns_doing($user->uid);
  // If user isn't doing anything:
  if (empty($doing)) {
    // Set No Signups Header.
    $variables['no_signups_header'] = t(variable_get('dosomething_user_profile_no_signups_header'));
    if (empty($variables['no_signups_header'])) {
      $variables['no_signups_header'] = t("There's nothing here!");
    }
    // Set No Signups Copy.
    $variables['no_signups_copy'] = t(variable_get('dosomething_user_profile_no_signups_copy'));
    if (empty($variables['no_signups_copy'])) {
      $variables['no_signups_copy'] = t("(Yet.) Sign up for a campaign to make the world suck less. Then send pics of you in action for the chance at scholarship money and swag.");
    }
  }
  else {
    foreach ($doing as $nid) {
      $variables['doing'][] = dosomething_campaign_get_campaign_block_vars($nid);
    }
  }

  // Collect User Reportbacks.
  $variables['reportbacks'] = dosomething_reportback_get_reportbacks($uid);

  $variables['title'] = t("Hey, @name!", array("@name" => $variables['first_name']));
  $variables['subtitle'] = t(variable_get('dosomething_user_profile_subtitle', NULL));
}
